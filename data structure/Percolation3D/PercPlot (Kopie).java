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

public class PercPlot {

    // recursive curve plotting
    public static void curve(int N, int M, double x0, double y0, double x1, double y1) {
        double gap = .001;
        double err = .0025;
//        double xm = (x0 + x1) / 2;
        double xm = 0;
        double ym = (y0 + y1) / 2;
       // if (xm == 1) return;
        do {
        double fxm = Estimate.eval(N, xm, M);
        if (fxm >= 0.5) break;
        xm = xm + gap;
        }while (xm <= 1);
        StdOut.println (xm); 
/*       if (x1 - x0 < gap || Math.abs(ym - fxm) < err) {
//            StdDraw.line(x0, y0, x1, y1);
            return;
        }
        curve(N, M, x0, y0, xm, fxm);
        if (fxm == 0.5) StdOut.println (xm);
      //StdDraw.filledCircle(xm, fxm, .005);
        curve(N, M, xm, fxm, x1, y1);*/
    }
}
