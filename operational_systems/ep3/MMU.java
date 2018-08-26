/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/
 import java.util.ArrayList;
 import java.util.Arrays;
 import java.util.List;

public class MMU {
  int memVirt;
  int memPhysic;
  int pageSize;
  int adressVirtsize;
  int adressPhysize;
  int nBits;
  ArrayList<Integer> mmuAdress;
  ArrayList<Integer> mmuIndex;

  public MMU (int total, int virtual, int p){
      this.memVirt = virtual;
      this.memPhysic = total;
      this.pageSize = p;
      this.adressVirtsize = (int)Math.ceil(log2 (virtual));
      this.adressPhysize = (int)Math.ceil(log2 (total));
      int i = (int)Math.ceil(virtual/p);
      this.nBits = (int)Math.ceil(log2(i));
      mmuAdress = new ArrayList<Integer>();
      mmuIndex = new ArrayList<Integer>();
      System.out.printf ("virt size = %d\n", adressVirtsize);
      System.out.printf ("phys size = %d\n", adressPhysize);
      System.out.printf ("vect size = %d\n", i);
      System.out.printf ("nBits = %d\n", nBits);
      for (int x = 0; x < i; x++) { mmuAdress.add(x,6); mmuIndex.add(x,0);}
  }
  public double log2 (double x) {
    return Math.log (x)/Math.log (2);
  }
  public int getMMUphysAdress (int adressVirt) {
    int index = getMMUindex (adressVirt);
    System.out.println(index);
    int newlfbits = mmuAdress.get (index);
    int present = mmuIndex.get (index);
    int rtbits = ((1<<(adressVirtsize-nBits))-1)&adressVirt;
    int physicalAdress =  newlfbits<<(adressVirtsize-nBits)|rtbits;
    return physicalAdress;

  }


  private int getMMUindex (int adressVirt) {
    int lfnbits = 0;
    lfnbits = adressVirt>>>(adressVirtsize-nBits);
    return lfnbits;
  }

  public static void main (String[] args) {
    MMU a = new MMU(32*1024,64*1024,4*1024);
    System.out.println(a.getMMUphysAdress(8196));
  }

}
