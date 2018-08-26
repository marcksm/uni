
public class Task {

    private static boolean running = true;
    
    Thread computerRange;
    Thread checkerTask;
    Thread checkerDisconnected;
    Thread leaderThread;
    
    public static void start() {
        checkerDisconnected = new Thread(new CheckerDisconnected());
        checkerDisconnected.start();
        checkerTask = new Thread(new CheckerTask());
        checkerTask.start();
        computerRange = new Thread();
        computerRange.start();
        leaderThread = new Thread();
        leaderThread.start();
    }
    
    public static void close() {
        this.running = false;
    }
    
    public static void startComputeRange(int bloc) {
        if (!computerRange.isAlive()) {
            computerRange = new Thread(new ComputerRange(r));
            computerRange.start();
        }
    }
    
    private static void sleep(long time) {
        try {
            Thread.sleep(time);
        } catch (Exception e) {
            return; 
        }
    }
    
    private static class CheckerTask implements Runnable {
    
        public void run() {
            while (running) {
                if (!computerRange.isAlive()) {
                    Request.bloc();
                    sleep(500);
                } else {
                    computerRange.join();
                }
            }
        }
    }
    
    private static class ComputerRange implements Runnable {        
        private Range r;
                
        public ComputerRange(Range r) {
            this.r = r;
        }
        
        public void run() {
            for (int i = r.low; i <= r.high; i++) {
                if (r.number % i == 0) {
                    Management.getInstance().notPrime();
                    return;
                }
            }     
        }
    }
    
    private static class CheckerDisconnected implements Runnable {    
        public void run() {
            while(running) {                
                Connected[] conns = Peer.getConnections();
                for (Connection conn : conns) {
                    if (!conn.isConnected()) {
                        conn.close();
                        Peer.getInstance().removeConnection(conn);
                    }
                }
                sleep(400);
            }
        }
    }
    
    private static class CheckerBloc implements Runnable {
        private int bloc;
        
        public CheckerBloc(int bloc) {
            this.bloc = bloc;
        }
        public void run() {
            sleep(4000);
            if (!Peer.getInstance().isDone(this.bloc))
                Leader.addAvaliableBloc(this.bloc);                
        }
    
    }
    
    
}
