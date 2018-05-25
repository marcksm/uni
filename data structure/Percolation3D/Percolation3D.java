/******************************************************************************
 * Name: Marcos Vinicius do Carmo Sousa
 * NUSP: 9298274
 *
 *  Compilation:  javac-algs4 Percolation3D.java
 *  Execution:    java-algs4 Percolation3D
 *  Dependencies: StdArrayIO.java StdDraw.java StdOut.java
 *  A program that generate a random a path in a 3D cube with N sides and M tests
 *  calculates the probability to percolate it.
 *  The input is N and M. 
 *  Careful high number N can occour overflow 
 *  The output is a graph.
 *
 ******************************************************************************/
//import edu.princeton.cs.algs4.*;

public class Percolation3D {

    // given an N-by-N matrix of open sites, return an N-by-N matrix
    // of sites reachable from the top
    public static int flow(boolean[][][] open) {
        int N = open.length;
        boolean[][][] full = new boolean[N][N][N];
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++)
               if (flow(open, full, i, j, 0) == 1) return 1;
        }
        return 0;
    }


    // determine set of full sites using depth first search
    public static int flow(boolean[][][] open, boolean[][][] full, int i, int j,
    int k) {
        int N = open.length;

        // base cases
        if (i < 0 || i >= N) return 0;    // invalid row
        if (j < 0 || j >= N) return 0;    // invalid column
        if (k < 0 || k >= N) return 0;
        if (!open[i][j][k]) return 0;        // not an open site
        if (full[i][j][k]) return 0;         // already marked as full

        // mark i-j as full
        full[i][j][k] = true;
        if (k == N-1) return 1;
        if ((flow(open, full, i+1, j, k) == 1)) return 1;   // down
        if (flow(open, full, i, j+1, k) == 1) return 1;  
        if (flow(open, full, i, j, k+1) == 1) return 1;
        if (flow(open, full, i, j-1, k) == 1) return 1;   // left
        if (flow(open, full, i-1, j, k) == 1) return 1;   // up
        if (flow(open, full, i, j, k-1) == 1) return 1; 
        return 0;
    }
/*    public static void flow(boolean[][][] open, boolean[][][] full, int i, int j,
    int k) {
        int N = open.length;

        // base cases
        if (i < 0 || i >= N) return;    // invalid row
        if (j < 0 || j >= N) return;    // invalid column
        if (k < 0 || k >= N) return;
        if (!open[i][j][k]) return;        // not an open site
        if (full[i][j][k]) return;         // already marked as full

        // mark i-j as full
        full[i][j][k] = true;

        flow(open, full, i+1, j, k);   // down
        flow(open, full, i, j+1, k);  
        flow(open, full, i, j, k+1);
        flow(open, full, i, j-1, k);   // left
        flow(open, full, i-1, j, k);   // up
        flow(open, full, i, j, k-1); 
    }*/


    // does the system percolate?
    public static boolean percolates(boolean[][][] open) {
        int N = open.length;
  /*      boolean[][][] full = */if (flow(open) == 1) return true;
         return false;
       /* for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++)
               if (full[i][j][N-1]) return true;
        }
        return false;*/
    }

    // draw the N-by-N boolean matrix to standard draw
/*    public static void show(boolean[][][] a, boolean which) {
        int N = a.length;
        StdDraw.setXscale(-1, N);
        StdDraw.setYscale(-1, N);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (a[i][j][k] == which)
                    StdDraw.filledSquare(j, N-i-1, .5);
    }*/

    // return a random N-by-N boolean matrix, where each entry is
    // true with probability p
    public static boolean[][][] random(int N, double p) {
        boolean[][][] a = new boolean[N][N][N];
        for (int k = 0; k < N; k++)
            for (int i = 0; i < N; i++)
               for (int j = 0; j < N; j++)
                  a[i][j][k] = StdRandom.bernoulli(p);
        return a;
    }
 
   public static void main(String[] args) {
        int N = Integer.parseInt (args[0]);
        int M = Integer.parseInt (args[1]);
          PercPlot.curve (N, M, 0.0, 0.0, 1.0, 1.0);
   }

}
