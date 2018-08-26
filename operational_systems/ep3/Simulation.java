/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/

import java.io.File;
import java.io.RandomAccessFile;
import java.util.Vector;
import java.util.Scanner;
import java.util.ArrayList;

public class Simulation {

    static boolean testMode;

    static int spType;
    static int pgType;
    static int interval;

    static int total;
    static int virtual;
    static int s;
    static int p;

    static File trace;
    static RandomAccessFile vir;
    static RandomAccessFile mem;
    static Scanner in;

    static EventsList events;
    static ProcTable procTable;
    static BitMap vBitMap;
    static BitMap mBitMap;

    static PagTable pagTable;

    static int nextFitPos;

    static ArrayList<Long> freeSpaceTime;

    public static void prepare () {
        File virFile = new File ("/tmp/ep3.vir");
        File memFile = new File ("/tmp/ep3.mem");
        boolean existsVir = virFile.exists ();
        boolean existsMem = memFile.exists ();

        if ((existsVir && !virFile.delete()) ||
            (existsMem && !memFile.delete())) {
            System.out.println ("Erro com arquivos temporários.");
            System.exit (1);
        }

        freeSpaceTime = new ArrayList<Long> ();

        try {
            Scanner in = new Scanner (trace);
            String l = new String ("");

            while (l.replaceAll ("[ ]+", "").isEmpty ())
                l = in.nextLine ();

            l = l.replaceAll ("[ ]+", " ");
            String[] line = l.replaceAll ("^[ ]", "").split (" ");
            total = Integer.parseInt (line[0]);
            virtual = Integer.parseInt (line[1]);
            s = Integer.parseInt (line[2]);
            p = Integer.parseInt (line[3]);

            mem = new RandomAccessFile (virFile, "rw");
            vir = new RandomAccessFile (memFile, "rw");
            events = new EventsList ();
            procTable = new ProcTable ();
            vBitMap = new BitMap (virtual);
            mBitMap = new BitMap (total);
            pagTable = new PagTable (total, virtual, p);


            ArrayList<Event> memRefs = new ArrayList<Event> ();

            while (in.hasNextLine ()) {
                l = in.nextLine ();
                if (l.replaceAll ("[ ]+", "").isEmpty ()) continue;
                l = l.replaceAll ("[ ]+", " ");
                line = l.replaceAll ("^[ ]", "").split (" ");
                int t0 = Integer.parseInt (line[0]);
                int tf = Integer.parseInt (line[2]);
                int b = Integer.parseInt (line[3]);
                procTable.add (line[1]);
                int pid = procTable.getLastAddedPid ();
                events.add (Event.PROC_ARRIVE, pid, t0, b);
                events.add (Event.PROC_FINISH, pid, tf);
                for (int i = 4; i + 1 < line.length; i += 2) {
                    int time = Integer.parseInt (line[i+1]);
                    int pos = Integer.parseInt (line[i]);
                    events.add (Event.MEM_REF, pid, time, pos);
                    if (pgType == 1) {
                        Event e = Event.specialEvent (time, pid, pos);
                        int k;
                        boolean founded = false;
                        for (k = 0; k < memRefs.size (); k++) {
                            if (memRefs.get(k).type == time) founded = true;
                            else if (founded) break;
                        }

                        memRefs.add (k, e);
                    }
                }
            }
            for (int i = 0; i < virtual; i++)
                vir.writeInt (-1);
            for (int i = 0; i < total; i++)
                mem.writeInt (-1);

            if (pgType == 1)
                PageManagement.initialize (pgType, mem, total, mBitMap, p,
                                       pagTable, procTable, s, memRefs, vir);
            else
                PageManagement.initialize (pgType, mem, total, mBitMap, p,
                                       pagTable, procTable, s, null, null);

            if (spType == 2) nextFitPos = 0;
        }
        catch (Exception e) {
            System.out.printf ("Exeption in prepare: %s\n", e.toString ());
            System.exit (1);
        }
    }

    public static void run () {
        prepare ();
        if (!testMode) procTable.printTable ();
        Vector<Event> nextEvents = events.getNextEvents ();
        int nextPrintTime = 0;

        while (true) {
            if (nextEvents.isEmpty ()) {
                // printLog (nextPrintTime);
                break;
            }
            if (nextPrintTime < events.getCurrentEventTime ()) {
                if (!testMode) printLog (nextPrintTime);
                pagTable.resetAllbitR ();
                nextPrintTime += interval;
            }
            else {
                PageManagement.clearDontRemoveList ();
                if (nextPrintTime == events.getCurrentEventTime ())
                    pagTable.resetAllbitR ();
                for (Event e : nextEvents) {
                    switch (e.type) {
                        case Event.PROC_ARRIVE:
                            putProcessInVirtual (e.pid, e.ext);
                            break;
                        case Event.PROC_FINISH:
                            removeProcessFromVirtual (e.pid);
                            removeProcessFromPhysical (e.pid);
                            procTable.remove (e.pid);
                            break;
                        case Event.MEM_REF:
                            PageManagement.memRef (e.pid, e.ext);
                            break;
                        default:
                            break;
                    }
                }
                if (nextPrintTime == events.getCurrentEventTime ()) {
                    if (!testMode)printLog (nextPrintTime);
                    nextPrintTime += interval;
                }
                nextEvents = events.getNextEvents ();
            }
        }
        if (testMode) {
            System.out.printf ("\nTotal de pagefaults = %d\n", PageManagement.getPageFaults ());
            System.out.printf ("Tempo para encontrar espaço livre para cada processo:\n");
            System.out.printf ("(por ordem de chegada dos processos)\n");
            for (long l : freeSpaceTime)
                System.out.printf ("%d ", l);
            System.out.println ();
        }
    }

    public static void printLog (int time) {
        try {
            vir.seek (0);
            mem.seek (0);
            System.out.printf ("\n--------- Instante de tempo: %ds\n", time);
            System.out.printf ("   Posição    BitMap da    Memoria    BitMap da    Memoria\n");
            System.out.printf ("   (bytes)     memoria     virtual     memoria      fisica\n");
            System.out.printf ("               virtual                 fisica\n");
            int i = 0;
            int j = 0;
            while (i < virtual && i < total) {
                int vb = vBitMap.isFree (i)? 0 : 1;
                int mb = mBitMap.isFree (i)? 0 : 1;
                System.out.printf ("%10d %12d %10d %12d %10d\n", i, vb,
                                   vir.readInt (), mb, mem.readInt ());
                i++;
            }
            while (i < virtual) {
                int vb = vBitMap.isFree (i)? 0 : 1;
                System.out.printf ("%10d %12d %10d\n", i, vb, vir.readInt ());
                i++;
            }
            while (i < total) {
                int mb = mBitMap.isFree (i)? 0 : 1;
                System.out.printf ("%10d %36d %10d\n", i, mb, mem.readInt ());
                i++;
            }

        }
        catch (Exception e) {
            System.out.printf ("Exeption in printLog: %s\n", e);
            e.printStackTrace ();
            System.exit (1);
        }
    }

    public static void putProcessInVirtual (int pid, int b) {
        int space = ((int)Math.ceil (((double) b / p))) * (p/s) * s;
        long init = System.currentTimeMillis ();
        switch (spType) {
            case 1:
                firstFit (pid, space);
                break;
            case 2:
                nextFit (pid, space);
                break;
            case 3:
                bestFit (pid, space);
                break;
            case 4:
                worstFit (pid, space);
                break;
            default:
                break;
        }
        long end = System.currentTimeMillis ();
        freeSpaceTime.add (end - init);
    }

    public static void removeProcessFromPhysical (int pid) {
        int base = procTable.getProcBase (pid);
        int lim = procTable.getProcLim (pid);
        try {
            for (int i = base; i < lim; i += p) {
                // System.out.printf ("%d %d %d\n", i, pagTable.getphysAdress (i), pagTable.getBitPres (i));
                if (pagTable.getBitPres (i) == 1) {
                    int phyAdress = pagTable.getphysAdress (i);
                    mem.seek (4 * phyAdress);
                    for (int j = 0; j < p; j++) {
                        mBitMap.setFree (phyAdress + j);
                        mem.writeInt (-1);
                    }
                }
            }
        }
        catch (Exception e) {
            System.out.printf ("Exception in removeProcessFromPhysical: %s\n",
                                e.toString ());
            e.printStackTrace ();
            System.exit (1);
        }
    }

    public static void removeProcessFromVirtual (int pid) {
        int base = procTable.getProcBase (pid);
        int lim = procTable.getProcLim (pid);
        try {
            vir.seek (4 * base);
            for (int i = base; i < lim + 1; i++) {
                vBitMap.setFree (i);
                vir.writeInt (-1);
            }
        }
        catch (Exception e) {
            System.out.printf ("Exception in removeProcessFromVirtual: %s\n",
                                e.toString ());
            System.exit (1);
        }
    }

    public static void writeVirMem (int pid, int init, int size) {
        try {
            vir.seek (4 * init);
            for (int i = init; i < size + init; i++) {
                vBitMap.setOcupied (i);
                vir.writeInt (pid);
            }
            procTable.setProcBase (pid, init);
            procTable.setProcLim (pid, init + size - 1);
        }
        catch (Exception e) {
            System.out.printf ("Exeption in writeVirMem: %s\n", e.toString ());
            e.printStackTrace ();
            System.exit (1);
        }
    }

    /* Recebe um inteiro pid e um inteiro b representando o tamanho do processo
    * e o coloca na memoria virtual utilizando o método firstFit.
    */
    public static void firstFit (int pid, int b) {
        int space = 0;
        int i = 0;
        int i0 = 0;

        while (i < virtual) {
            if (vBitMap.isFree (i)) {
                if (space == 0) i0 = i;
                space++;
                if (space == b) { writeVirMem (pid, i0, b); return; }
            }
            else space = 0;
            i++;
        }
        System.out.printf ("Processo não cabe na memória virtual!");
        System.out.printf (" Abortando...\n");
        System.exit (1);
    }

    /* Recebe um inteiro pid e um inteiro b representando o tamanho do processo
    * e o coloca na memoria virtual utilizando o método bestFit.
    */
    public static void bestFit (int pid, int b) {
        int space = 0;
        int smallestSize = virtual;
        int i = 0, i0 = 0, i0f = 0;
        boolean founded = false;

        while (i < virtual) {
            if (vBitMap.isFree (i)) {
                if (space == 0) i0 = i;
                space++;
                if (space == b && space < smallestSize) {
                  smallestSize = space;
                  space = 0;
                  i0f = i0;
                  founded = true;
                }
            }
            else space = 0;
            i++;
        }
        if (founded) writeVirMem (pid, i0f, b);
        else {
            System.out.printf ("Processo não cabe na memória virtual!");
            System.out.printf (" Abortando...\n");
            System.exit (1);
        }
    }



    public static void worstFit (int pid, int b) {
        int biggestSize = 0;
        int init = 0;
        int i = 0;
        while (i < virtual) {
            if (vBitMap.isFree (i)) {
                int j = i + 1;
                int size = 1;
                while (j < virtual && vBitMap.isFree (j)) {
                    size++;
                    j++;
                }
                if (size > biggestSize) {
                    biggestSize = size;
                    init = i;
                }
                i = j + 1;
            }
            else i++;
        }
        if (biggestSize < b) {
            System.out.printf ("Processo não cabe na memória virtual!");
            System.out.printf (" Abortando...\n");
            System.exit (1);
        }
        writeVirMem (pid, init, b);
    }

    public static void nextFit (int pid, int b) {
        int i = nextFitPos;

        while (i < virtual) {
            if (vBitMap.isFree (i)) {
                int j = i + 1;
                int size = 1;
                while (j < virtual && vBitMap.isFree (j) && size < b) {
                    size++;
                    j++;
                }
                if (size == b) {
                    writeVirMem (pid, i, b);
                    nextFitPos = i + b;
                    return;
                }
                else i = j + 1;
            }
            else i++;
        }
        i = 0;
        while (i < nextFitPos) {
            if (vBitMap.isFree (i)) {
                int j = i + 1;
                int size = 1;
                while (j < nextFitPos && vBitMap.isFree (j) && size < b) {
                    size++;
                    j++;
                }
                if (size == b) {
                    writeVirMem (pid, i, b);
                    nextFitPos = i + b;
                    return;
                }
                else i = j + 1;
            }
            else i++;
        }
        System.out.printf ("Processo não cabe na memória virtual!");
        System.out.printf (" Abortando...\n");
        System.exit (1);
    }
    //
    // public static void nextFit (int pid, int b) {
    //     int space = 0;
    //     int i = nextFitPos;
    //     int i0 = 0;
    //
    //     while (i < virtual) {
    //         if (vBitMap.isFree (i)) {
    //             if (space == 0) i0 = i;
    //             space++;
    //             if (space == b) {
    //                 nextFitPos = i0 + b;
    //                 writeVirMem (pid, i0, b);
    //                 return;
    //             }
    //         }
    //         else space = 0;
    //         i++;
    //     }
    //     i = 0;
    //     while (i < nextFitPos) {
    //         if (vBitMap.isFree (i)) {
    //             if (space == 0) i0 = i;
    //             space++;
    //             if (space == b) {
    //                 nextFitPos = i0 + b;
    //                 writeVirMem (pid, i0, b);
    //                 return;
    //             }
    //         }
    //         else space = 0;
    //         i++;
    //     }
    //     System.out.printf ("Processo de tamanho superior ao ");
    //     System.out.printf ("tamanho da memória virtual.Impossível");
    //     System.out.printf (" aloca-lo!\nAbortando...");
    //     System.exit (1);
    // }


}
