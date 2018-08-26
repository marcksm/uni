import java.util.*;

public class HandlePackage {
  public Object obj;
  PackageNewPC npc;
  PackagePrime p;
  PackageOffPC ofpc;
  PackageLeader l;
  PackageNetStat ns;
  PackageBlock b;
  PackageInfo i;
  List<Object> list;

  public HandlePackage () {
  }

  public HandlePackage (Package x) {

    List<Object> list = x.list;
    for (Object obj : list) {
      if (obj.getClass().getName() == "PackageBlock"){
        b = PackageBlock.class.cast(obj);
      }
      if (obj.getClass().getName() == "PackageNetStat"){
        ns = PackageNetStat.class.cast(obj);
      }
      if (obj.getClass().getName() == "PackageNewPC"){
        npc = PackageNewPC.class.cast(obj);
      }
      if (obj.getClass().getName() == "PackagePrime"){
        p = PackagePrime.class.cast(obj);
      }
      if (obj.getClass().getName() == "PackageOffPC"){
        ofpc = PackageOffPC.class.cast(obj);
      }
      if (obj.getClass().getName() == "PackageLeader"){
        l = PackageLeader.class.cast(obj);
      }
      if (obj.getClass().getName() == "PackageInfo"){
        i = PackageInfo.class.cast(obj);
      }
    }
  }

  //Devolve o id do Leader
  public int getLeader () {
    if (l != null){ return l.leader;}
    return -1;
  }
  public int getrandNum () {
    if (l != null){ return l.myrandNum;}
    return -1;
  }
  public boolean newLeader() {
    if (l != null) { return l.newLeader;}
    return false;
  }
  public boolean isElection() {
    if (l != null){ return l.election;}
    return false;
  }
  public boolean isElectionResponse() {
    if (l != null){ return l.election;}
    return false;
  }
  public void setElectionResponse() {
    if (l == null){ l = new PackageLeader();}
    l.electionResponse = true;
  }
  public void setLeader (int lead) {
    if (l == null) {
      l = new PackageLeader();
    }
    l.newLeader = true;
    l.leader = lead;
  }
  public void setrandNum (int num) {
    if (l == null) {
      l = new PackageLeader();
    }
    l.myrandNum = num;
  }
  public void newElection () {
    if (l == null) {
      l = new PackageLeader();
    }
    l.election = true;
  }
  public Range getRange () {
    if (b != null){ return b.r;}
    return null;
  }
  public boolean isnewTask () {
    if (b != null){ return b.newTask;}
    return false;
  }
  public boolean isfinishBlock () {
    if (b != null){ return b.finishBlock;}
    return false;
  }
  public int getfinishedBlock () {
    if (b != null){ return b.block;}
    return -1;
  }
  public int getBlock () {
    if (b != null){ return b.block;}
    return -1;
  }
  public void setfinishedBlock (int block) {
    if (b == null){ b = new PackageBlock();}
    b.block = block;
    b.finishBlock = true;
  }
  public void setRange (Range r) {
    if (b == null){ b = new PackageBlock();}
    b.r = r;
    b.newTask = true;
  }
  public int getconnectedPCs () {
    if (ns != null) { return ns.howmanyPCs;}
    return -1;
  }
  public void setnumberconnectedPCs (int num) {
    if (ns == null) { ns = new PackageNetStat ();}
    ns.howmanyPCs = num;
  }
  public boolean isnewPC () {
    if (npc != null) {return npc.newPC;}
    return false;
  }
  public InetAddress getnewPCid () {
    if (npc != null) { return npc.address;}
    return -1;
  }
  public void setnewPCid (InetAddress address) {
    if (npc == null) { npc = new PackageNewPC();}
    npc.address = address;
    npc.newPC = true;
  }

  public boolean isoffPC () {
    if (ofpc != null) {return ofpc.offPC;}
    return false;
  }
  public int getoffPCid () {
    if (ofpc != null) { return ofpc.offpcIp;}
    return -1;
  }
  public void setoffPCid (int id) {
    if (ofpc == null) { ofpc = new PackageOffPC();}
    ofpc.offpcIp = id;
    ofpc.offPC = true;
  }

  public boolean isfinishPrime (){
    if (p != null) {return p.finishPrime;}
    return false;
  }
  public boolean isPrime (){
    if (p != null) {return p.isPrime;}
    return false;
  }

  public int whoDiscovered (){
    if (p!= null) {return p.resultDiscovery;}
    return -1;
  }

  public long getPrime (){
    if (p != null) {return p.prime;}
    return -1;
  }
  public void setfinishPrime (){
    if (p == null) { p = new PackagePrime();}
    p.finishPrime = true;
  }
  public void setwhoDiscoreved (InetAddress id) {
    if (p == null) { p = new PackagePrime();}
    p.resultDiscovery = id;
  }
  public void setPrime (long prime) {
    if (p == null) { p = new PackagePrime ();}
    p.prime = prime;
  }
  public int getsenderID (){
    if (i != null) { return i.senderIp;}
    return -1;
  }
  public int getreceiverID () {
    if (i != null) { return i.receiverIp;}
    return -1;
  }
  public long gettimeTransfer () {
    if (i != null) { return i.time;}
    return -1;
  }
  public void setsenderID (int id) {
    if (i == null) { i = new PackageInfo();}
    i.senderIp = id;
  }
  public void setreceiverID (int id) {
    if (i == null) { i = new PackageInfo();}
    i.receiverIp = id;
  }
  public void settimeTransfer (long time) {
    if (i == null) { i = new PackageInfo();}
    i.time = time;
  }
  public void setworkingBlock (int id) {
    if (b == null){ b = new PackageBlock();}
    b.working = true;
    b.block = id;
  }
  public boolean isworkingBlock (){
    if (b!= null) {b = new PackageBlock(); return b.working;}
    return false;
  }

  public Package ready () {
    list = new ArrayList();
    if (i != null) {list.add(i);}
    if (b != null) {list.add(b);}
    if (ns != null) {list.add(ns);}
    if (l != null) {list.add(l);}
    if (ofpc != null) {list.add(ofpc);}
    if (p != null) {list.add(p);}
    if (npc != null) {list.add(npc);}
    Package p = new Package (list);
    return p;
  }
  public static void main(String[] args) {

    //PC 1 - simulaç~ao de uma eleicao e um bloco finalizado
    HandlePackage envio = new HandlePackage();
    envio.newElection ();
    envio.setLeader(30);
    envio.setfinishedBlock (4);
    envio.setsenderID(0);
    envio.setreceiverID(1);
    Package pacote = envio.ready();

    //PC 2 - recebe o pacote e visualiza os dados dele
    HandlePackage recebido = new HandlePackage (pacote);
    System.out.println ("Enviado por PC id: " + recebido.getsenderID());
    System.out.println ("Quem eh o leader " + recebido.getLeader());
    System.out.println ("Bloco terminado " + recebido.getfinishedBlock());

  }
}
