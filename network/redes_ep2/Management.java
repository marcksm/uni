import java.lang.*;
import java.util.Random;
import java.util.Hashtable;
import java.util.Enumeration;

public class Management {
  int n; // number of PCS connecteds
  int cONSTANT = 10000;
  InetAddress leader; //Peer.getInstance().getInetLeader();
  InetAddress myAddress; //P
  int myrand;
  Hashtable<Integer, InetAddress> hashtable = new Hashtable<Integer, InetAddress>();
  Hashtable<Long, InetAddress> primeInfo = new Hashtable<Long, InetAddress>();
  ArrayList<Long> primes = new ArrayList();
  Prime p;
  private static Management instance;

  public static Management getInstance () {
    if (instance == null) {
      instance = new Management();
    }
    return instance
  }

  private Management () {
    init();
  }

  public void currentNumber(long num) {
    p = new Prime(num, 10000000);

  }
  public void task(HandlePackage h) {
    Range r = h.r;
    if (h.isnewTask() && !p.isworkingBlock(r.id)) {
      Task.computeRange(r);
    }
  }

  public void requestBlock() {
    HandlePackage h = new HandlePackage();
    h.setrequestRange();//boleano que avisa que quer range para todos, mas somente o lider repsonde
    h.setsenderID(myAddress);
    Package p = h.ready();
    Network.broadcast (p);
  }
  public void sendBlock(Range r, InetAddress address) {
    HandlePackage h = new HandlePackage();
    h.setRange(r);
    h.setsenderID(myAddress);
    Package p = h.ready();
    //IMPLEMENTAR MANDAR PARA UM INET ESPECIFICO
    HandlePackage h = new HandlePackage();
    h.setsenderID(myAddress);
    h.setworkingBlock(r.id);
    Package p = h.ready();
    Network.broadcast (p);
  }
  public boolean iamLeader() {
    if (leader.equals(myAddress)) return true;
    return false;
  }

  //enviar pacote que terminou bloco tal pra todos
  public void endBlock (Range r) {
    HandlePackage h = new HandlePackage();
    h.setfinishedBlock (r.id);
    h.setsenderID(myAddress);
    p.finishBlock(r.id);
    Package p = h.ready();
    Network.broadcast (p);
  }

  public void block (HandlePackage h) {
    if (h.isrequestRange() && iamLeader()){
      Range r = p.getrange();
      sendBlock(r, h.getsenderID());
    }
    if (h.isworkingBlock()) p.workingBlock(h.getBlock());
    if (h.isfinishBlock()) p.finishBlock(h.getBlock());

  }
  public void notPrime () {
    HandlePackage h = new HandlePackage();
    h.setfinishedPrime();
    h.setwhoDiscoreved(myAddress);
    Package p = h.ready();
    Network.broadcast (p);
  }

  public void event (Package p) {
    HandlePackage h = new HandlePackage(p);

    task(h);
    election(h);
    block(h);//ok
    prime(h);
  }
  public void election (HandlePackage h) {

  }

  public int getrandomNum() {
    int rand, min = 1, max = n*cONSTANT;
    Random r = new Random();
    rand = r.nextInt(max - min + 1) + min;
    return rand;
  }

  public void init () {
    count = 0;
    myrand = -1;
    n = 0;
    myAddress = InetAddress.getLocalHost();
    id = myAddress.hashCode();
    List<InetAddress> hosts = getLocalHosts();
    for (InetAddress host: hosts) {
      n++;
      hashtable.put (host.hashCode(), host);
    }
  }
}
