class RandomQueue  {
   static int s, e, N;
   static int[] queue;
   public static String toString(int item) {
      int rank = item % 13;
      int suit = item / 13;
      String ranks = "23456789TJQKA";
      String suits = "CDHS";
      return ranks.charAt(rank) + "" + suits.charAt(suit);
   }
   static void RandomQueue() {
      N = 2;
      queue = new int[N];
      s = 0;
      e = 0;
   }
   static int sample () {
      int x = StdRandom.uniform (s, e);
      return x;
   }
   static void enqueue (int card) {
      if (e == queue.length) resize (2*N);
      queue[e++] = card;
   }
   static int dequeue () {
      int x = StdRandom.uniform (s, e);
      int aux = queue[e-1];
      queue[e-1] = queue[x];
      queue[x] = aux;
      aux = queue[e-1];
      e--;
      return aux;
   }
   static boolean isEmpty () {
      if (s == e) return true;
      else return false;

   }
   static void resize (int cap) {
      int i = 0;
      int[] buffer = new int[cap];
      for (i = s; i < N; i++) buffer[i-s] = queue[i];
      s = 0;
      e = i;
      queue = buffer;
      N = 2*N;
   }
}

public class Bridge {
   public static void main (String[] args) {
      RandomQueue.RandomQueue();
      for (int i = 0; i < 52; i++) 
         RandomQueue.enqueue (i);
      for (int i = 0; i < 13; i++) 
         StdOut.println(RandomQueue.toString (RandomQueue.dequeue()));
   }
}













































