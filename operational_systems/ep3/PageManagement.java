/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/

import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.Vector;

public class PageManagement {

    private static int ptr;
    private static ArrayList<Integer> fifo;
    private static int changeType;
    private static BitMap bitMap;
    private static int memSize;
    private static RandomAccessFile mem;
    private static RandomAccessFile vir;
    private static int pageSize;
    private static PagTable pagTable;
    private static ProcTable procTable;
    private static int unidAloc;
    private static int pageFaults;
    private static ArrayList<Event> memRefsList;
    private static ArrayList<Integer> dontRemovePages;
    private static int time;

    public static void initialize (int type, RandomAccessFile memFile, int size,
                              BitMap memBitMap, int pgSize, PagTable pat,
                              ProcTable prt, int s, ArrayList<Event> mrl,
                              RandomAccessFile v) {
        changeType = type;
        mem = memFile;
        memSize = size;
        bitMap = memBitMap;
        pageSize = pgSize;
        pagTable = pat;
        procTable = prt;
        unidAloc = s;
        pageFaults = 0;
        dontRemovePages = new ArrayList<Integer> ();
        switch (changeType) {
            case 1:
                vir = v;
                time = 0;
                memRefsList = mrl;
                break;
            case 2:
                fifo = new ArrayList<Integer> ();
                break;
            case 3:
                fifo = new ArrayList<Integer> ();
                ptr = 0;
                break;
            case 4: // Não há variaveis especiais para o algoritmo lru
                break;
            default:
                break;
        }
    }

    public static void writePhyMem (int pid, int init) {
        try {
            mem.seek (4 * init);
            for (int i = init; i < pageSize + init; i++) {
                bitMap.setOcupied (i);
                mem.writeInt (pid);
            }
        }
        catch (Exception e) {
            System.out.printf ("Exeption in writePhyMem: %s\n", e.toString ());
            System.exit (1);
        }
    }



    public static boolean firstFit (int pid, int pageVirtualAdress) {
        int space = 0;
        int i = 0;
        int i0 = 0;

        while (i < memSize) {
            if (bitMap.isFree (i)) {
                if (space == 0) i0 = i;
                space++;
                if (space == pageSize) {
                    writePhyMem (pid, i0);
                    pagTable.setVPtoPP (pageVirtualAdress, i0);
                    if (changeType == 2 || changeType == 3) {
                        fifo.add (pageVirtualAdress);
                    }
                    return true;
                }
            }
            else space = 0;
            i++;
        }
        return false;
    }

    public static int getPageFaults () {
        return pageFaults;
    }

    public static void clearDontRemoveList () {
        dontRemovePages.clear ();
    }

    public static void memRef (int pid, int pos) {
        int pageVirtualAdress = ((procTable.getProcBase (pid) + pos) / pageSize)
                                 * pageSize;
        dontRemovePages.add (pageVirtualAdress);
        if (changeType == 1) {
            time = memRefsList.get (0).type;
            memRefsList.remove (0);
        }
        pagTable.setBitR (pageVirtualAdress, 1);
        if (pagTable.getBitPres (pageVirtualAdress) == 0) {
            pageFaults++;
            if (!firstFit (pid, pageVirtualAdress))
                substitute (pid, pageVirtualAdress);
        }
    }

    public static void substitute (int pid, int virtualAdress) {
        switch (changeType) {
            case 1:
                optimal (pid, virtualAdress);
                break;
            case 2:
                secondChance (pid, virtualAdress);
                break;
            case 3:
                clock (pid, virtualAdress);
                break;
            case 4:
                lru (pid, virtualAdress);
                break;
            default:
                break;
        }
    }

    /*Retorna 1 se a é maior que b, -1 se b é maior que a e 0 caso a seja igual
     * a b. a e b são tratados como ints unsigned, com range entre 0 e
     * 4294967295*/
    private static int compareInts (int a, int b) {
        if (a == b) return 0;
        if ((a < 0 && b < 0) || (a >= 0 && b >= 0)) return a > b ? 1 : -1;
        return a < 0 ? 1 : -1;
    }

    /* Recebe um inteiro pid e um inteiro virtualAdress
    * e coloca a pagina que contem o virtualAdress na memoria fisica
    * utilizando o método lru
    */
    public static void lru (int pid, int virtualAdress) {
        int phyAdress = -1;
        int smallest = 0;
        int oldPageVirAdress = -1;
        boolean first = true;
        for (int adr : pagTable.allPresent ()) {
            if (!dontRemovePages.contains (adr) && first) {
                smallest = pagTable.getCount (adr);
                oldPageVirAdress = adr;
                phyAdress = pagTable.getphysAdress (adr);
            }
            else if (compareInts (pagTable.getCount (adr), smallest) == -1 &&
                !dontRemovePages.contains (adr)) {
                phyAdress = pagTable.getphysAdress (adr);
                oldPageVirAdress = adr;
                smallest = pagTable.getCount (adr);
            }
        }
        if (oldPageVirAdress == -1) {
            System.out.printf ("Página não cabe na memória fisíca\n");
            System.exit (1);
        }
        writePhyMem (pid, phyAdress);
        pagTable.setVPtoPP (virtualAdress, phyAdress);
        pagTable.setBitPres (oldPageVirAdress, 0);
    }

    /* Recebe um inteiro pid e um inteiro virtualAdress
    * e coloca a pagina que contem o virtualAdress na memoria fisica
    * utilizando o método ótimo
    */
    public static void optimal (int pid, int virtualAdress) {
        int biggestLable = -1;
        int virAdrToRemove = 0;
        for (int virAdr : pagTable.allPresent ()) {
            if (dontRemovePages.contains (virAdr)) continue;
            int thisLable = 0;
            int tppid = 0;
            try {
                vir.seek (4 * virAdr);
                tppid = vir.readInt ();
            }
            catch (Exception e) {
                System.out.printf ("Exception in optimal: %s\n", e.toString ());
                System.exit (1);
            }
            for (Event e : memRefsList) {
                if (e.type == time) continue;
                if (!procTable.isThere (e.pid)) continue;
                int base = procTable.getProcBase (e.pid);
                if (base == -1) continue;
                if (e.pid == tppid && (((base + e.ext) / pageSize) * pageSize)
                    == virAdr) {
                        break;
                }
                thisLable++;
            }
            // System.out.printf ("Pag %d lable %d\n", virAdr, thisLable);
            if (thisLable > biggestLable) {
                biggestLable = thisLable;
                virAdrToRemove = virAdr;
            }
        }
        // System.out.println ();
        if (biggestLable == -1) {
            System.out.printf ("Página não cabe na memória fisíca\n");
            System.exit (1);
        }
        int phyAdress = pagTable.getphysAdress (virAdrToRemove);
        writePhyMem (pid, phyAdress);
        pagTable.setVPtoPP (virtualAdress, phyAdress);
        pagTable.setBitPres (virAdrToRemove, 0);
    }

    /* Recebe um inteiro pid e um inteiro virtualAdress
    * e coloca a pagina que contem o virtualAdress na memoria fisica
    * utilizando o método second chance
    */
    public static void secondChance (int pid, int virtualAdress) {
        int oldPageVirAdress;
        while (true) {
            oldPageVirAdress = fifo.get (0);
            fifo.remove (0);
            if (pagTable.getBitR (oldPageVirAdress) == 1) {
                pagTable.setBitR (oldPageVirAdress, 0);
                fifo.add (oldPageVirAdress);
            }
            else if (!dontRemovePages.contains (oldPageVirAdress)) break;
        }
        int physicalAdress = pagTable.getphysAdress (oldPageVirAdress);
        pagTable.setBitPres (oldPageVirAdress, 0);
        writePhyMem (pid, physicalAdress);
        fifo.add (virtualAdress);
        pagTable.setVPtoPP (virtualAdress, physicalAdress);
    }

   //  public static void clock (int pid, int virtualAdress) {
   //    int p = 0;
   //    int adressToremove = 0;
   //    p = fifo.get (ptr);
   //    while (pagTable.getBitR (p) == 1) {
   //      pagTable.setBitR (p, 0);
   //      ptr = (ptr + 1)%fifo.size();
   //      p = fifo.get (ptr);
   //    }
   //    adressToremove = p;
   //    fifo.remove (ptr);
   //    fifo.add (ptr, virtualAdress);
   //    ptr = (ptr + 1)%fifo.size();
   //    int physicalAdress = pagTable.getphysAdress (adressToremove);
   //    pagTable.setBitPres (adressToremove, 0);
   //    writePhyMem (pid, physicalAdress);
   //    pagTable.setVPtoPP (virtualAdress, physicalAdress);
   // }

   /* Recebe um inteiro pid e um inteiro virtualAdress
   * e coloca a pagina que contem o virtualAdress na memoria fisica
   * utilizando o método Relógio
   */
   public static void clock (int pid, int virtualAdress) {
     int p = 0;
     int adressToremove = 0;
     p = fifo.get (ptr);
     while (pagTable.getBitR (p) == 1 || dontRemovePages.contains (p)) {
       pagTable.setBitR (p, 0);
       ptr = (ptr + 1)%fifo.size();
       p = fifo.get (ptr);
     }
     adressToremove = p;
     fifo.remove (ptr);
     fifo.add (ptr, virtualAdress);
     ptr = (ptr + 1)%fifo.size();
     int physicalAdress = pagTable.getphysAdress (adressToremove);
     pagTable.setBitPres (adressToremove, 0);
     writePhyMem (pid, physicalAdress);
     pagTable.setVPtoPP (virtualAdress, physicalAdress);
   }



}
