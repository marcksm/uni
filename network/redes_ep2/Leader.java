public class Leader {

    private static PriorityQueue<Integer> avaliableBlocs = new PriorityQueue<Integer>();
    
    public static addAvaliableBlocs(Range[] blocs) {         
        for (int i = 0; i < n; i++) 
            if (!blocs[i].done)
                addAvaliableBloc(i);
        
    }
    
    public static int getAvaliableBloc() {
        synchronized (avaliableBlocs) {
            if (avaliableBlocs.length() > 0)
                return avaliableBlocs.poll();
            return -1;
        }
    }
    
    public void addAvaliableBloc(int bloc) {
        synchronized (avaliableBlocs) {
            avaliableBlocs.add(bloc);
        }
    }
    public static Range[] generateBlocs(long number) {
        
    }

    

}
