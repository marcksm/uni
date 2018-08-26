/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/

import java.util.TreeMap;
import java.util.Vector;
import java.util.Collection;

public class EventsList {

    private TreeMap<Integer,Vector<Event>> list;
    private int curTime;

    public EventsList () {
        list = new TreeMap<Integer,Vector<Event>> ();
        curTime = -1;
    }

    public void add (int type, int pid, int time) {
        if (!list.containsKey (time)) list.put (time, new Vector<Event> ());
        if (type == Event.PROC_FINISH) list.get (time).add (0, new Event (type, pid));
        else list.get (time).add (new Event (type, pid));
    }

    public void add (int type, int pid, int time, int ext) {
        if (!list.containsKey (time)) list.put (time, new Vector<Event> ());
        list.get (time).add (new Event (type, pid, ext));
    }

    public Vector<Event> getNextEvents () {
        Vector<Event> events;
        if (list.isEmpty ()) {
            curTime = -1;
            events = new Vector<Event> ();
        }
        else {
            curTime = list.firstKey ();
            events = list.get (curTime);
            list.remove (curTime);
        }
        return events;
    }

    public int getCurrentEventTime () {
        return curTime;
    }

    public Collection<Vector<Event>> allEvents () {
        return list.values ();
    }

}
