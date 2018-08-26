/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/

import java.util.TreeMap;

public class ProcTable {


    private class Info {
        int base;
        int lim;
        String name;

        public Info (int base, int lim, String name) {
            this.base = base;
            this.lim = lim;
            this.name = name;
        }
    }


    private TreeMap<String,Integer> si;
    private TreeMap<Integer,Info> iif;
    private int lastAddPID;

    public ProcTable () {
        lastAddPID = -1;
        si = new TreeMap<String,Integer> ();
        iif = new TreeMap<Integer,Info> ();
    }

    public void add (String name) {
        lastAddPID++;
        si.put (name, lastAddPID);
        iif.put (lastAddPID, new Info (-1, -1, name));
    }

    public int getPID (String name) {
        return si.get (name);
    }

    public int getLastAddedPid () {
        return lastAddPID;
    }

    public String getName (int pid) {
        return iif.get (pid).name;
    }

    public int total () {
        return lastAddPID + 1;
    }

    public void setProcBase (int pid, int base) {
        iif.get (pid).base = base;
    }

    public int getProcBase (int pid) {
        return iif.get (pid).base;
    }

    public boolean isThere (int pid) {
        if (iif.get (pid) == null) return false;
        return true;
    }

    public void setProcLim (int pid, int lim) {
        iif.get (pid).lim = lim;
    }

    public int getProcLim (int pid) {
        return iif.get (pid).lim;
    }

    public void remove (String name) {
        iif.remove (si.get(name));
        si.remove (name);
    }

    public void remove (int pid) {
        si.remove (iif.get(pid).name);
        iif.remove (pid);
    }

    public void printTable () {
        System.out.println ("\n============Tabela de Processos:");
        System.out.println ("      PID:    Nome:");
        for (int pid : iif.keySet ()) {
            System.out.printf ("%10d    %s\n", pid, iif.get (pid).name);
        }
    }



}
