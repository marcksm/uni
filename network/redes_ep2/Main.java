import java.net.InetAddress;
import com.esotericsoftware.kryonet.*;
import com.esotericsoftware.kyro.*;


public class Main {
  static int port;
  static long prime;

  /*Recebe a lista de argumentos e verifica se está correto*/
  //java EP2 [porta] [numero primo | vazio se for ajudar apenas]
  public static boolean inputCheck (String[] args) {
    port = 0;
    prime = -1;
    if (args.length > 0) {
      port = Integer.parseInt (args[0]);
      if (args.length > 1 && args.length < 3) {
        prime = Long.parseLong (args[1]);
      }
      else if (args.length > 2) {
        System.out.println("Too much arguments.");
        System.out.println("Run java EP2 [port] [<empty> | number to check if its prime]");
        return false;
      }
    }
    else {
      System.out.println("Insufficients arguments.");
      System.out.println("Run java EP2 [port] [<empty> | number to check if its prime]");
      return false;
    }
    return true;
  }


  public static void main(String[] args) {
    if (!inputCheck (args)) return;
    Network.createListenSocket(port);
    Network.connectPeersLocalNetwork(port);

  }

}
