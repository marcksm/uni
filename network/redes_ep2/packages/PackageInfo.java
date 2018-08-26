public class PackageInfo {
  //pode fazer um hash do IP nas duas pontas e passar o hash como id
  public int senderIp; //id do computador de quem enviou o pacote
  public int receiverIp; //sid do computador de quem recebeu o pacote
  public long time; // tempo no pc de origem de criação do pacote

  public PackageInfo () {
  }

}
