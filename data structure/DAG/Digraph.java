/******************************************************************************
 *  Compilation:  javac Digraph.java
 *  Execution:    java Digraph filename.txt
 *  Dependencies: Bag.java In.java StdOut.java
 *  Data files:   http://algs4.cs.princeton.edu/42digraph/tinyDG.txt
 *
 *  A graph, implemented using an array of lists.
 *  Parallel edges and self-loops are permitted.
 *
 *  % java Digraph tinyDG.txt
 *  13 vertices, 22 edges
 *  0: 5 1 
 *  1: 
 *  2: 0 3 
 *  3: 5 2 
 *  4: 3 2 
 *  5: 4 
 *  6: 9 4 8 0 
 *  7: 6 9
 *  8: 6 
 *  9: 11 10 
 *  10: 12 
 *  11: 4 12 
 *  12: 9 
 *  
 ******************************************************************************/

import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Comparator;
import java.util.Collections;
/**
 *  The <tt>Digraph</tt> class represents a directed graph of vertices
 *  named 0 through <em>V</em> - 1.
 *  It supports the following two primary operations: add an edge to the digraph,
 *  iterate over all of the vertices adjacent from a given vertex.
 *  Parallel edges and self-loops are permitted.
 *  <p>
 *  This implementation uses an adjacency-lists representation, which 
 *  is a vertex-indexed array of {@link Bag} objects.
 *  All operations take constant time (in the worst case) except
 *  iterating over the vertices adjacent from a given vertex, which takes
 *  time proportional to the number of such vertices.
 *  <p>
 *  For additional documentation,
 *  see <a href="http://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */

class WordDAG {
    private int max;
    ST<String, Integer> si = new ST<String, Integer>();
    ST<Integer, String> is = new ST<Integer, String>();
    ST<String, Integer> si2 = new ST<String, Integer>();
    ArrayList<String> tmp = new ArrayList<>();
    Out out = new Out("saida.txt");
    Digraph G;
    public class comparator implements Comparator<String>{
        @Override
            public int compare(String a, String b) {  
                if (a.length() > b.length()) {
                    return 1;
                } else if (a.length() < b.length()) {
                    return -1;
                }
                return a.compareTo(b);
            }
    }
    public boolean isNeighbor(String a, String b) {
        int x = b.length() - a.length();
        int min;
        if (a.length() <= b.length()) min = a.length();
        else return false;
        if (x > 1 || x < -1) {
            return false;
        }
        int differ = 0;
        for (int i = 0; i < min; i++) {
            if (a.charAt(i) != b.charAt(i)) differ++;
            if (differ > 1 && x == 0) return false;
            if (x != 0 && differ > 0) return false;
        }
        return true;
    }
    public WordDAG(String[] strings) {
        int quit = 0;
        int size = 0;
        int shift = 0;
        int f = 0;
        max = strings.length;
        for (int i = 0; i < strings.length; i++) {
            size = strings[i].length();
            if (size > shift) shift = size;
            si.put(strings[i], i);
            si2.put(strings[i], i);
            is.put(i, strings[i]);
        }
        G = new Digraph(strings.length);
        for (int k = 0; k < shift; k++) {
            for (int i = 0; i < strings.length; i++) {
                for (f = i+1; (f < strings.length) && strings[i].compareTo(strings[f]) < 0 && isNeighbor(strings[i], strings[f]); f++) {
                    int w1 = si.get(strings[i]);
                    int w2 = si.get(strings[f]);
                    for (int w : G.adj(w2)) {
                        if (w == w1) quit = 1;
                    }
                    if (quit==1) break;
                    G.addEdge(w2, w1);
                }
                quit = 0;
            }
            for (int t = 0; t < strings.length; t++) {
                int wa = si.get(strings[t]); //Manter o indice original na ST para palavra shiftada
                strings[t] = strings[t].charAt(strings[t].length() - 1) + strings[t].substring(0, strings[t].length() - 1);//Shift para direita
                si.put(strings[t], wa); //Manter o indice original na ST para palavra shiftada
            }
            tmp = new ArrayList<String>(Arrays.asList(strings));
            Collections.sort(tmp, new comparator());
            strings = tmp.toArray(new String[0]);
        }
    } 
    public void PrintDag(){
 
        for (int v = 0; v < max; v++) {
             for (int w : G.adj(v)) {
               out.println(is.get(v) + " "+ is.get(w));
            }
        }

        
    }
    public void PrintPathCount(String a, String b){
       int a1 = si2.get(a);
       int b1 = si2.get(b);
       Stack<Integer> s = new Stack<Integer>();
       s.push(a1);
       int path = 0;
       while (!s.isEmpty()){
          int last = s.pop();
          for (int w : G.adj(last)){
              s.push(w);
              if (w==b1) {int x = s.pop(); path++;}
              
          }
       }
       out.println(path);
    }


}
public class Digraph {
    private static final String NEWLINE = System.getProperty("line.separator");

    private final int V;           // number of vertices in this digraph
    private int E;                 // number of edges in this digraph
    public Bag<Integer>[] adj;    // adj[v] = adjacency list for vertex v
    private int[] indegree;        // indegree[v] = indegree of vertex v

    /**
     * Initializes an empty digraph with <em>V</em> vertices.
     *
     * @param  V the number of vertices
     * @throws IllegalArgumentException if V < 0
     */
    public Digraph(int V) {
        if (V < 0) throw new IllegalArgumentException("Number of vertices in a Digraph must be nonnegative");
        this.V = V;
        this.E = 0;
        indegree = new int[V];
        adj = (Bag<Integer>[]) new Bag[V];
        for (int v = 0; v < V; v++) {
            adj[v] = new Bag<Integer>();
        }
    }

    /**  
     * Initializes a digraph from the specified input stream.
     * The format is the number of vertices <em>V</em>,
     * followed by the number of edges <em>E</em>,
     * followed by <em>E</em> pairs of vertices, with each entry separated by whitespace.
     *
     * @param  in the input stream
     * @throws IndexOutOfBoundsException if the endpoints of any edge are not in prescribed range
     * @throws IllegalArgumentException if the number of vertices or edges is negative
     */
    public Digraph(In in) {
        try {
            this.V = in.readInt();
            if (V < 0) throw new IllegalArgumentException("Number of vertices in a Digraph must be nonnegative");
            indegree = new int[V];
            adj = (Bag<Integer>[]) new Bag[V];
            for (int v = 0; v < V; v++) {
                adj[v] = new Bag<Integer>();
            }
            int E = in.readInt();
            if (E < 0) throw new IllegalArgumentException("Number of edges in a Digraph must be nonnegative");
            for (int i = 0; i < E; i++) {
                int v = in.readInt();
                int w = in.readInt();
                addEdge(v, w); 
            }
        }
        catch (NoSuchElementException e) {
            throw new InputMismatchException("Invalid input format in Digraph constructor");
        }
    }

    /**
     * Initializes a new digraph that is a deep copy of the specified digraph.
     *
     * @param  G the digraph to copy
     */
    public Digraph(Digraph G) {
        this(G.V());
        this.E = G.E();
        for (int v = 0; v < V; v++)
            this.indegree[v] = G.indegree(v);
        for (int v = 0; v < G.V(); v++) {
            // reverse so that adjacency list is in same order as original
            Stack<Integer> reverse = new Stack<Integer>();
            for (int w : G.adj[v]) {
                reverse.push(w);
            }
            for (int w : reverse) {
                adj[v].add(w);
            }
        }
    }

    /**
     * Returns the number of vertices in this digraph.
     *
     * @return the number of vertices in this digraph
     */
    public int V() {
        return V;
    }

    /**
     * Returns the number of edges in this digraph.
     *
     * @return the number of edges in this digraph
     */
    public int E() {
        return E;
    }


    // throw an IndexOutOfBoundsException unless 0 <= v < V
    private void validateVertex(int v) {
        if (v < 0 || v >= V)
            throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V-1));
    }

    /**
     * Adds the directed edge v->w to this digraph.
     *
     * @param  v the tail vertex
     * @param  w the head vertex
     * @throws IndexOutOfBoundsException unless both 0 <= v < V and 0 <= w < V
     */
    public void addEdge(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        adj[v].add(w);
        indegree[w]++;
        E++;
    }

    /**
     * Returns the vertices adjacent from vertex <tt>v</tt> in this digraph.
     *
     * @param  v the vertex
     * @return the vertices adjacent from vertex <tt>v</tt> in this digraph, as an iterable
     * @throws IndexOutOfBoundsException unless 0 <= v < V
     */
    public Iterable<Integer> adj(int v) {
        validateVertex(v);
        return adj[v];
    }

    /**
     * Returns the number of directed edges incident from vertex <tt>v</tt>.
     * This is known as the <em>outdegree</em> of vertex <tt>v</tt>.
     *
     * @param  v the vertex
     * @return the outdegree of vertex <tt>v</tt>               
     * @throws IndexOutOfBoundsException unless 0 <= v < V
     */
    public int outdegree(int v) {
        validateVertex(v);
        return adj[v].size();
    }

    /**
     * Returns the number of directed edges incident to vertex <tt>v</tt>.
     * This is known as the <em>indegree</em> of vertex <tt>v</tt>.
     *
     * @param  v the vertex
     * @return the indegree of vertex <tt>v</tt>               
     * @throws IndexOutOfBoundsException unless 0 <= v < V
     */
    public int indegree(int v) {
        validateVertex(v);
        return indegree[v];
    }

    /**
     * Returns the reverse of the digraph.
     *
     * @return the reverse of the digraph
     */
    public Digraph reverse() {
        Digraph R = new Digraph(V);
        for (int v = 0; v < V; v++) {
            for (int w : adj(v)) {
                R.addEdge(w, v);
            }
        }
        return R;
    }

    /**
     * Returns a string representation of the graph.
     *
     * @return the number of vertices <em>V</em>, followed by the number of edges <em>E</em>,  
     *         followed by the <em>V</em> adjacency lists
     */
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(V + " vertices, " + E + " edges " + NEWLINE);
        for (int v = 0; v < V; v++) {
            s.append(String.format("%d: ", v));
            for (int w : adj[v]) {
                s.append(String.format("%d ", w));
            }
            s.append(NEWLINE);
        }
        return s.toString();
    }

    /**
     * Unit tests the <tt>Digraph</tt> data type.
     */
    public static void main(String[] args) {
        String[] strings = {"cobra", "sobra", "sobrar", "cobro", "cobrou", "sobrando", "cobre"};
        WordDAG wdag = new WordDAG(strings);
        StdOut.println();
        wdag.PrintDag();
        wdag.PrintPathCount("cobro","cobra");
        wdag.out.close();
        // In in = new In(args[0]);
        // Digraph G = new Digraph(in);
        // StdOut.println(G);
    }

}
