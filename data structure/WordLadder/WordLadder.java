/******************************************************************************
 *  Compilation:  javac WordLadder.java
 *  Execution:    java WordLadder word1 word2 < wordlist.txt
 *  Dependencies: Graph.java IndexSET.java In.java BreadthFirstPaths.java
 *
 *  Data files:   http://algs4.cs.princeton.edu/41graph/words5.txt
 *                http://algs4.cs.princeton.edu/41graph/words6.txt
 *                http://algs4.cs.princeton.edu/41graph/words5-knuth.txt
 *
 *  Creates a minimum length word ladder connecting two words.
 *
 *  java WordLadder words5.txt
 *  flirt break
 *  length = 11
 *  flirt
 *  flint
 *  fling
 *  cling
 *  clink
 *  click
 *  clock
 *  cloak
 *  croak
 *  creak
 *  break
 *
 *  allow brown
 *  NOT CONNECTED
 *
 *  white house
 *  length = 18
 *  white
 *  while
 *  whale
 *  shale
 *  shake
 *  slake
 *  slate
 *  plate
 *  place
 *  peace
 *  peach
 *  poach
 *  coach
 *  couch
 *  cough
 *  rough
 *  rouge
 *  rouse
 *  house
 *  
 *  % java WordLadder words5-knuth.txt
 *  white house
 *  length = 9
 *  white
 *  whits
 *  shits
 *  shots
 *  soots
 *  roots
 *  routs
 *  route
 *  rouse
 *  house
 *
 ******************************************************************************/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Comparator;
import java.util.Collections;
public class WordLadder {
    public static class comparator implements Comparator<String>{
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
    public static boolean isNeighbor(String a, String b) {
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
    public static String shiftar (String a, int times) {
        for (int i = 0; i < times; i++)
            a = a.charAt(a.length() - 1) + a.substring(0, a.length() - 1);
        return a;
    }
    public static String desshiftar (String a, int times) {
        for (int i = 0; i < times; i++){
            a = a.substring(1, a.length()) + a.charAt(0);
        }
        return a;
    }
    public static void main(String[] args) {
        In in = new In(args[0]);
        String[] words = in.readAllStrings();
        MSD.sort(words);
        ST<String, Integer> si = new ST<String, Integer>();
        ST<Integer, String> is = new ST<Integer, String>();
        ST<String, Integer> si2 = new ST<String, Integer>();
        ArrayList<String> tmp = new ArrayList<>();
        int size = 0;
        int shift = 0;
        int k, f;
        int max = 0;
        k = 0;
        for (int i = 0; i < words.length; i++) {
            size = words[i].length();
            if (size > shift) shift = size;
            si.put(words[i], i);
            si2.put(words[i], i);
            is.put(i, words[i]);
        }

        Graph G = new Graph(words.length);

        while (!StdIn.isEmpty()) {
            String from = StdIn.readString();
            String to   = StdIn.readString();
            if (!si2.contains(from)) throw new RuntimeException(from + " is not in word list");
            if (!si2.contains(to))   throw new RuntimeException(to   + " is not in word list");
            if (from.length() > to.length()) max = from.length();
            else max = to.length();
            for (; k < max; k++) {
                for (int i = 0; i < words.length; i++) {
                    for (f = i+1; (f < words.length) && words[i].compareTo(words[f]) < 0 && isNeighbor(words[i], words[f]); f++) {
                        int w1 = si.get(words[i]);
                        int w2 = si.get(words[f]);
                        G.addEdge(w2, w1);
                    }
                }
                for (int t = 0; t < words.length; t++) {
                    int wa = si.get(words[t]); //Manter o indice original na ST para palavra shiftada
                    words[t] = words[t].charAt(words[t].length() - 1) + words[t].substring(0, words[t].length() - 1);//Shift para direita
                    si.put(words[t], wa); //Manter o indice original na ST para palavra shiftada
                }
                tmp = new ArrayList<String>(Arrays.asList(words));
                Collections.sort(tmp, new comparator());
                words = tmp.toArray(new String[0]);
            }
            int a = si2.get(from);
            int b = si2.get(to);
            BreadthFirstPaths bfs = new BreadthFirstPaths(G, a);
            if (bfs.hasPathTo(b)) {
                for (int v : bfs.pathTo(b)) {
                    StdOut.println(is.get(v));
                }
            }
            else StdOut.println("NOT CONNECTED");
            StdOut.println();
        }
    }
}
