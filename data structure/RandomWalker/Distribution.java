
import java.awt.Color;
public class Distribution {
   public static void main (String[] args) {
      int N = Integer.parseInt (args[0]);
      int M = Integer.parseInt (args[1]);
      int L = Integer.parseInt (args[2]);
      int high = 0, p= 0;
      int[][] grid = new int[2*L][2*L]; 
      double[] dist = new double[N+1];
      while (M > 0) {
         p = RandomWalker.Walk (grid, N, 2*L, dist);
         if (p > high) high = p;
         M--;
      }
      StdOut.println (high);
      StdDraw.setXscale (0, 2*L);
      Picture pic = new Picture (2*L, 2*L);
      StdDraw.setYscale (0, 2*L);
//    pic.show();
      for (int i = 0; i < 2*L; i++) {
         for (int j = 0; j < 2*L; j++) {
            float xi = (float)(0.7-(0.7*((float)grid[i][j])/(float)high));
          //  int float = (int)(xi*255);
           // Color color = new  Color (x, 0, 0);
//            Color.HSBtoRGB (xi, 1, 1);
            Color color = new Color (Color.HSBtoRGB (xi, 1, 1));
 //           StdDraw.setPenColor (color);
            pic.set (i, j, color);
//            StdDraw.filledSquare ((double)i, (double)j, 2);

         }
      }
  //    StdDraw.show(20);
      pic.show();
   }
}








































