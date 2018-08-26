
import com.esotericsoftware.kryonet.*;
import com.esotericsoftware.kryo.*;
import java.io.IOException;

public class Servidor {
    
    public static void main(String[] args) throws IOException {
        int porta = Integer.parseInt(args[0]);
        Server server = new Server();
        Kryo kryo = server.getKryo();
        kryo.register(SomeRequest.class);
        kryo.register(SomeResponse.class);        
        server.start();        
        server.bind(porta, porta);
        server.addListener(new Listener() {
            public void connected(Connection connection) {
                System.out.println(connection.getID() + "conectou");
                //connection.setKeepAliveTCP(100);
            
            }
            public void received (Connection connection, Object object) {
                System.out.println("Recebi objeto: " + object.getClass().getName());
                if (object instanceof SomeRequest) {
                    SomeRequest request = (SomeRequest)object;
                    System.out.println(request.text);
    
                    SomeResponse response = new SomeResponse();
                    response.text = "Thanks";
                    connection.sendTCP(response);
                }
            }
            public void disconnected(Connection connection){                
                System.out.println(connection.getID() + " desconectou");
            }
        });
        System.out.println("Servidor no ar");
    }

}
