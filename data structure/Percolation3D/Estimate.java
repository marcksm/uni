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

public class Estimate {

    // do M trials and return fraction that percolate
    public static double eval(int N, double p, int M) {
        int count = 0;
        for (int k = 0; k < M; k++) {
            boolean[][][] open = Percolation3D.random(N, p);
            if (Percolation3D.percolates(open))
                count++;
        }
        return (double) count / M;
    }
}
