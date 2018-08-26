/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/

import java.util.TreeMap;

public class Event {

    static final int PROC_ARRIVE = 0;
    static final int PROC_FINISH = 1;
    static final int MEM_REF = 2;

    int type;
    int pid;
    int ext;

    public Event (int type, int pid) {
        this.type = type;
        this.pid = pid;
    }

    public Event (int type, int pid, int ext) {
        this.type = type;
        this.pid = pid;
        this.ext = ext;
    }

    public static Event specialEvent (int time, int pid, int pos) {
        return new Event (time, pid, pos);
    }

}
