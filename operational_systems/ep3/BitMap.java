/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/

import java.util.TreeMap;
import java.lang.Math;

public class BitMap {
  int sizeMem;
  private byte[] bt;

    /* Recebe um inteiro size representando o tamanho do BitMap em bytes.
    * e cria um objeto do tipo BitMap
    */
    public BitMap (int size) {
      sizeMem = (int)Math.ceil (((float)size)/8);
      bt = new byte[sizeMem];
      for (int i = 0; i < sizeMem; i++) bt[i] = 0;
    }
    /*Recebe um inteiro i representando a posição do BitMap em bytes e
    * devolve se true há um bit ocupando e false caso não há
    */
    public boolean isFree (int i) {
      long j = i % 8;
      int pos = i / 8;
      byte b = bt[pos];
      if ((b & (byte)Math.pow (2, 7 - j))   != 0) return false;
      else return true;
    }

    /*Recebe um inteiro i representando a posição do BitMap em bytes e altera
    * para 1 a representação desse bit no BitMap
    */
    public void setOcupied (int i) {
      int j = i % 8;
      int pos = i / 8;
      byte b = bt[pos];
      bt[pos] = (byte)(b | (byte)Math.pow (2, 7 - j));
    }

    /*Recebe um inteiro i representando a posição do BitMap em bytes e altera
    * para 0 a representação desse bit no BitMap
    */
    public void setFree (int i) {
      long j = i % 8;
      int pos = i / 8;
      byte b = bt[pos];

      bt[pos] = (byte)(b & (byte)Math.abs((255 - Math.pow (2, 7 - j))));
    }

    /* Função auxiliar para debug */
    private void printbyteMem () {
      for (int i = 0; i < sizeMem; i++)
         System.out.print (bt[i] + " ");
      System.out.println ();
    }

    /* Função auxiliar para debug */
    private void printbitMem () {
      for (int i = 0; i < sizeMem; i++) {
         System.out.print (byteTobit(Integer.toString(bt[i],2)) + " ");
       }
      System.out.println ();
    }

    /* Função auxiliar para debug */
    private String byteTobit (String b) {
      int size = b.length();
      if (size > 8) return b.substring(1);
      int total = 8 - size;
      String r = new String ();
      for (int i = 0; i < total; i++) r = r + "0";
      r = r + b;
      return r;
    }

}
