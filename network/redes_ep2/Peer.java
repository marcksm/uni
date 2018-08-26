

public class Peer {
    
    private String leader;
    private List<Connection> connections;
    private Server listen;
    private Range[] blocs;        
    private List<long> numbers;
    private static Peer instance;
    
    public static void instance() {
        instance = new Peer();
    }
    
    public static Peer getInstance() {
        if (instance == null)
            instance = new Peer();
        return instance;
    }
    
    private Peer() {
        leader = null;
        connfds = new ArrayList();
        server = new Server();
        listaNumeros = new List();  
        blocs = null;      
    }
    
    private void setNameConnection(Connection conn) {
        InetSocketAddress add = connection.getRemoteAddressTCP();
        connection.setName(add.getHostName() + add.getPort());
    }
    
    public void addConnection(Connection conn) {
        synchronized (connections) {
            setNameConnection(conn);                       
            connections.add(conn);
        }
    }
    
    public void removeConnection(Connection conn) {
        synchronized (connections) {
            connections.remove(conn);
        }
    }
    
    public Connection[] getConnections() {
        synchronized (connections) {
            return connfds.toArray(); 
        }
    }
    
    public Server getListenSocket() {
        return listen;
    }
    
    public void setLeader(String leader) {
        this.leader = leader;
    }
    
    public void addNumber(long number) {
        synchronized (numbers) {
            numbers.add(number);
        }
    }
    
    public boolean isDone(int i) {
        synchronized (blocs) {
            return blocs[i].done;
        }
    }
    
}
