import java.util.*;
import java.net.*;
public class Prime {
  class Range {
    long high;
    long low;
    int id;
    int num;
  }
  public long prime;
  public long consst;
  public long range;
  public ArrayList<Long> lower;
  public ArrayList<Long> higher;
  public ArrayList<Boolean> done;
  public ArrayList<Boolean> working;

  public Prime (long p, long r) {
    range = r;
    prime = p;
    consst = p/range;
    lower = new ArrayList<Long>();
    higher = new ArrayList<Long>();
    done = new ArrayList<Boolean>();
    working = new ArrayList<Boolean>();
    build();
  }

  public Range getrange () {
    Range r = new Range();
    for (int i = 0; i < done.size(); i++) {
      if (done.get(i) == false && working.get(i) == false) {
        r.low = lower.get(i);
        r.high = higher.get(i);
        r.id = i;
        working.set(i,true);
        return r;
      }
    }
    return null;
  }
  public boolean isworkingBlock (int id) {
    if (working.get(id) == true) return true;
    return false;
  }
  public void workingBlock (int id) {
    working.set(id, true);
  }
  public void finishBlock(int id) {
    done.set(id, true);
  }

  public long interval () {
    int i = 0;
    long temp = 1, k = 0, high = prime;
    for (i = 1; i <= prime; i++) {
      k = prime/i;
      if (k < consst) break;
      if (k <= high)  {high = k; temp = i;}
    }
    return temp;
  }
  public void build () {
    long gap = 0;
    long x= 0, y = 0;
    gap = interval();
    for (long i = 0; i  <= prime; i = i + gap) {
      x = y;
      y = i + gap;
      if (x >= prime) break;
      if (y >= prime) {

        lower.add(x);
        higher.add(prime);
        done.add(false);
        working.add(false);
        //System.out.println ("["+ x+","+prime+"]");
        break;
      }
      //System.out.println ("["+ x+","+y+"]");
      lower.add(x);
      higher.add(y);
      done.add(false);
      working.add(false);

    }
  }

  public static void main (String[] args) {
    Prime p = new Prime (517, 1);
    Range r = p.getrange();
    System.out.println(r.high);
  //  p.build();
  }
}
