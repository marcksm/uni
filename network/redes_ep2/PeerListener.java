

public void PeerListener extends Listener {

    public PeerClientListener () {
        super();
    }
    
    public void connected(Connection connection) {
        Peer.getInstance().addConnection(connection);
        // Logger.conectou()
    }
    
    public void received(Connection connection, Object object) {
        if (object instanceof Package) {
            Package p = (Package) object;
            //Management.getInstance().event(p);
            
        }
    
    }
    
    public void disconnected(Connection connection) {
        //Logger.desconectou
    }           

}
