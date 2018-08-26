public class Distribution {
   public static void main (String[] args) {
      int N = Integer.parseInt (args[0]);
      int M = Integer.parseInt (args[1]);
      int L = Integer.parseInt (args[2]);
      int high;
      int[][] grid = new int[2*L][2*L]; 
      double[] dist = new double[N+1];
      while (M>0) {
         RandomWalker.steps (N, 2*L, grid, dist);
         M--;
      }
      high = RandomWalker.s1.highest;
      for (int i = 0; i < 2*L; i++) {
         for (int j = 0; j < 2*L; j++) {
            StdOut.print(grid[i][j] + "  ");
         }
         StdOut.println();
      }
   }
}








































