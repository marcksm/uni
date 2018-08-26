public class Network {


    /* Esse método devolve todos computadores rodando na rede
        local com porta UDP aberta */
    private static List<InetAddress> getLocalHosts(int port) {
        Client client = new Client();
        List<InetAddress> result = new List();
        List<InetAddress> hosts = client.discoverHosts(port, 300);
        for (InetAddress host : hosts) {
            if (!host.isLoopbackAddress)
                result.add(host);
        }
        return result;
    }

    public static void createListenSocket(int port) {
        Server server = Peer.server;
        registerClasses(server.getKyro());
        server.start();
        server.bind(port, port);
        server.addListener(new PeerListener());
    }

    private static boolean createConnection(InetAddress host, int port) {
        Client client = new Client();
        registerClasses(client.getKyro());
        new Thread (client).start();
        try {
            client.connect(300, host, port, port);
        } catch (IOException e) {
            client.close();
            return false;
        }
        client.addListener(new PeerListener);
        Peer.getInstance().addConnection(client);
        return true;
    }
    
    public static void send(InetAddress add, Object object) {
        conn.sendTCP(object);
    }

    public static void broadcast(Object object) {
        Peer peer = Peer.getInstance();
        for (Connection conn : peer.getConnections())
            conn.sendTCP(object); 
        
    }

    public static int connectPeersLocalNetwork(int port) {
        List<InetAddress> hosts = getLocalHosts();
        int cnt = 0;
        for (InetAddress host: hosts) {
            if (createConnection(host, port))
                cnt++;
        }
        return cnt;
    }

    private static void registerClasses(Kyro kyro) {
        // Lista de classes a ser registrada

    }
}
