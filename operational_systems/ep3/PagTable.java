/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/
 import java.util.ArrayList;

public class PagTable {
  int memVirt;
  int memPhysic;
  int pageSize;
  int adressVirtsize;
  int adressPhysize;
  int nBits;
  int k;
  int[][] mv;

  /* Recebe os inteiro total representando o tamanho da memoria
  * fisica, virtual representando tamanho da memoria virtual e p
  * representando o tamanho da pagina. Todos em bytes e criando
  * um objeto do tipo PagTable.
  */
  public PagTable (int total, int virtual, int p){
      this.memVirt = virtual;
      this.memPhysic = total;
      this.pageSize = p;
      this.adressVirtsize = (int)Math.ceil(log2 (virtual));
      this.adressPhysize = (int)Math.ceil(log2 (total));
      this.k = (int)Math.ceil(virtual/p);
      this.nBits = (int)Math.ceil(log2(k));
      mv = new int[k][5];
      for (int i = 0; i < k; i++) {
          mv[i][0] = i * pageSize;
          mv[i][1] = 0;
          mv[i][2] = 0;
          mv[i][3] = 0;
          mv[i][4] = 0;
      }

  }

  /* Recebe um double x e devolve o log na base 2 de x
  */
  private double log2 (double x) {
    return Math.log (x)/Math.log (2);
  }

  /* Devolve um arraylist de inteiros com os endereços virtuais
  * das paginas que estão na memória fisica (com o Bit present 1).
  */
  public ArrayList<Integer> allPresent () {
    ArrayList<Integer> pres = new ArrayList<Integer>();
    for (int i = 0; i < k; i++) {
      if (mv[i][2] == 1) pres.add(mv[i][0]);
    }
    return pres;
  }

/* Coloca todos os bit R para 0
*/
  public void resetAllbitR () {
    for (int i = 0; i < k; i++) {
      if (mv[i][2] == 1) {
          int count = mv[i][4];
          mv[i][4] = (count >>> 1) | (mv[i][3] == 1 ? -2147483648 : 0);
      }
      mv[i][3] = 0;
    }
  }

  /* Recebe um indereço virtual e devolve o endereço fisico
  * respectivo
  */
  public int getphysAdress (int adressVirt) {
    int index = getTableIndex (adressVirt);
    int newlfbits = bitsPhys (adressVirt);
    int rtbits = ((1<<(adressVirtsize-nBits))-1)&adressVirt;
    int physicalAdress =  newlfbits|rtbits;
    return physicalAdress;
  }

  /* Recebe o endereço virtual e devolve os nBits a esquerda
  * Os nbits são nBits = (int)Math.ceil(log2(virtual/p));
  */
  private int bitsPhys (int adressVirt) {
    int index = getTableIndex (adressVirt);
    return mv[index][1];
  }

  /* Recebe um endereço virtual adressVirt, e um inteiro representando
  * um bit i, e altera o bit R para o valor de i da pagina do respectivo
  * adressVirt.
  */
  public void setBitR (int adressVirt, int i) {
    int index = getTableIndex (adressVirt);
    mv[index][3] = i;
  }

  /* Recebe um endereço virtual adressVirt, e um inteiro representando
  * um bit i, e altera o bit de presente para o valor de i da pagina do
  * respectivo adressVirt.
  */
  public void setBitPres (int adressVirt, int i) {
    int index = getTableIndex (adressVirt);
    mv[index][2] = i;
  }

  /* Recebe um inteiro adressVirt e devolve o bit R da pagina do respectivo
  * endereço virtual.
  */
  public int getBitR (int adressVirt) {
    int index = getTableIndex (adressVirt);
    return mv[index][3];
  }

  /* Recebe um inteiro adressVirt e devolve o contador da pagina do respectivo
  * endereço virtual.
  */
  public int getCount (int adressVirt) {
      int index = getTableIndex (adressVirt);
      return mv[index][4];
  }

  /* Recebe um inteiro adressVirt e devolve o bit presente da pagina do
  * respectivo endereço virtual.
  */
  public int getBitPres (int adressVirt) {
    int index = getTableIndex (adressVirt);
    return mv[index][2];
  }

  /* Recebe um inteiro adressVirt e devolve o
  * endereço fisico da pagina.
  */
  public int getPageAdress (int adressVirt) {
    return getphysAdress(adressVirt/pageSize);
  }

  /* Recebe um inteiro adressVirt e devolve o indice da pagina do
  * respectivo endereço virtual.
  */
  private int getTableIndex (int adressVirt) {
    int lfnbits = 0;
    lfnbits = adressVirt>>>(adressVirtsize-nBits);
    return lfnbits;
  }

  /* Recebe um inteiro adressVirt e um inteiro posPhysical, e copia
  * a pagina virtual para a memoria fisica na posição posPhysical
  */
  public void setVPtoPP (int adressVirt, int posPhysical) {
    int index = getTableIndex (adressVirt);
    mv[index][1] = posPhysical;
    mv[index][2] = 1;
  }
}
