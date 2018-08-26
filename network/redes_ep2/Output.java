public class Output {
  public static void order (long prime, String computer) {
    System.out.println("@" + computer + " ordered to check whether " + prime + " is prime number");
  }
  public static void check (long prime, String computer) {
    System.out.println("Checking " + prime + " if it is prime number, ordered by: @" + computer);
  }
  public static void itsprime (long prime) {
    System.out.println (prime + " it's a prime!");
  }
  public static void itsprime (long prime, String computer) {
    System.out.println (prime + " it's a prime! discovered by: @" + computer);
  }
  public static void itsprime (long prime, String computer, int time) {
    System.out.println (prime + " it's a prime! discovered by: @" + computer + " in " + time(time));
  }
  public static void itsnotprime (long prime) {
    System.out.println (prime + " it's NOT a prime!");
  }
  public static void itsnotprime (long prime, String computer) {
    System.out.println (prime + " it's NOT a prime! discovered by: @" + computer);
  }
  public static void itsnotprime (long prime, String computer, int time) {
    System.out.println (prime + " it's NOT a prime! discovered by: @" + computer + " in " + time(time));
  }
  public static String time (int time) {
    int h = 0;
    int m = 0;
    int d = 0;
    while (time >= 60) {
      if (m >= 60) { h++; m = 0;}
      if (h >= 24) { d++; h = 0;}
      m++;
      time -= 60;
    }

    //"0days:14hrs:56min:34sec"
    String time1 = Integer.toString(d) + "days:" + Integer.toString(h) + "hrs:" + Integer.toString(m) + "min:"+ Integer.toString(time) + "sec";
    return time1;
  }
  
}
