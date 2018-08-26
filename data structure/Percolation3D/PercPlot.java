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
        double err = 0.01;
        double xe = x0;
        double xd = x1;
        double m;
        while (xe <= xd)  {
           m = (xe+xd)/2;
           if (Estimate.eval(N, m, M)==(0.5+err) || Estimate.eval(N, m, M)==(0.5-err)) {
              StdOut.println(m);
              break;
           }
           if (Estimate.eval(N, m, M)<(0.5)) xe = m;
           else xd = m;
       }
    }
}
