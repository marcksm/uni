class Step {
   int x;
   int y;
   int n;
   int highest;
}
public class RandomWalker {

   public static double dist (int x, int y) {
      return Math.sqrt (x*x + y*y);
   }
   public static void steps (Step s1, int N, int T, int[][] grid, double[] dist) {
      int[][] v = {{1,-1, 0, 0}, {0, 0, 1, -1}};      
      s1.n = 0;
      while (s1.n < N) {
         int i = StdRandom.uniform (0, 4);
         int xi = v[0][i];
         int yi = v[1][i];
         if (xi + s1.x < T && xi + s1.x >= 0) {
            if (yi + s1.y < T && yi + s1.y >= 0) {
               s1.x = s1.x + xi;
               s1.y = s1.y + yi;
               grid[s1.x][s1.y]++;
               if (grid[s1.x][s1.y] > s1.highest) s1.highest =
               grid[s1.x][s1.y];
               s1.n++;
              // dist[s1.n] = dist (s1.x, s1.y);
            }
         }
      }
   }
   public static int Walk (int[][] grid, int N, int T, double[] dist) {
      Step s1 = new Step();
      s1.x = T/2;
      s1.y = T/2;
      steps (s1, N, T, grid, dist);
      /*for (int i = 0; i < T; i++) {
         for (int j = 0; j < T; j++) {
            StdOut.print(grid[i][j] + "  ");
         }
         StdOut.println();
      }*/
      return s1.highest;
   }
   public static void main (String[] args) {
      int N = Integer.parseInt(args[0]);
      int T = Integer.parseInt(args[1]);
      int[][] grid = new int[T][T];
      double[] dist = new double[N+1];
      int j = Walk (grid, N, T, dist);
      StdOut.println (j);
      StdOut.println();
      StdOut.printf("N = Dist\n");
      for (int i = 0; i <= N; i++)
         StdOut.printf("%d = %.2f\n ", i, dist[i]);
   }

}



















