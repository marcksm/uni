import com.esotericsoftware.kryonet.*;
import com.esotericsoftware.kryo.*;
import java.io.IOException;
import java.util.List;
import java.net.*;

public class Cliente {
    
    public static void main(String[] args) throws IOException {
        String ip = args[0];
        int porta = Integer.parseInt(args[1]);
        
        Client client = new Client();
        Kryo kryo = client.getKryo();
        kryo.register(SomeRequest.class);
        kryo.register(SomeResponse.class);
        client.start();
        client.setName("BLa 1");
        List<InetAddress> list = client.discoverHosts(porta, 100);
        for (InetAddress host : list) {
            if (!host.isLoopbackAddress()) {
                //System.out.println(host);
                client.start();
                client.addListener(new Listener() {
                    public void connected(Connection connection) {
                        System.out.println(connection.getRemoteAddressTCP() + " conectado " + connection.toString());
                    }
                    public void disconnected (Connection connection) {
                        System.out.println("Desconectou");
                    }            
                    public void received (Connection connection, Object object) {
                        System.out.println("Recebi objeto: " + object.getClass().getName());
                        
                        if (object instanceof SomeResponse) {
                            SomeResponse response = (SomeResponse)object;
                            System.out.println(response.text);
                        }
                    }   
                });
                
                
                
                client.connect(5000, host, porta, porta);
                SomeRequest request = new SomeRequest();
                request.text = "Here is the request";
                client.sendTCP(request);
                
                try {
                    Thread.sleep(10000);
                } catch (Exception e) {
                    System.exit(1);
                }
                client.sendTCP(request);
                
                //while(true){} 
                //client.close();
                
            }
        }
        
        /*client.connect(5000, ip, porta);
        
        SomeRequest request = new SomeRequest();
        request.text = "Here is the request";
        client.sendTCP(request);
        
        client.addListener(new Listener() {            
            public void received (Connection connection, Object object) {
                if (object instanceof SomeResponse) {
                    SomeResponse response = (SomeResponse)object;
                    System.out.println(response.text);
                }
            }   
        });
        
        while(true){}*/
              
        
    
    }


}
