/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/

public class Page {
  int pgFrameNum;//-1 is on disk
  int present;
  int m;
  int r;
  int size;
  int adress;
  int where;//1 = disk, 2 = memvirtual, 3 = mem physic;
  byte count;

  public Page (int pgFrameNum, int prop, int adress, int size) {
    this.r = (2&prop)/2;
    this.m = (4&prop)/4;
    this.present = 1&prop;
    this.adress = adress;
    this.size = size;
    this.pgFrameNum = pgFrameNum;
    this.where = 2;
    count = 0;
  }
  public int getpgNum () {
    return pgFrameNum;
  }
  public void setpgNum (int i) {
    pgFrameNum = i;
  }
  public boolean isOnDisk () {
    if (pgFrameNum == -1) return true;
    else return false;
  }
  public void setBitR (int i) {
     r = i;
  }
  public int getBitR () {
    return r;
  }
  public void setBitPres (int i) {
     present = i;
  }
  public int getBitPres () {
    return present;
  }

  public byte getCount () {
      return count;
  }

  public void setCount (byte c) {
      count = c;
  }

  public boolean isPresent () {
    if (present == 1) return true;
    else return false;
  }
  public int getAdress () {
    return adress;
  }
  public void setAdress (int adr) {
    adress = adr;
  }
  public boolean isInMem () {
    if (where == 3) return true;
    else return false;
  }
  public void setWhere (int i) {
    where = i;
  }

}
