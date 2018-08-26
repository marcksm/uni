public class SAT {
    private Digraph G;
    private KosarajuSharirSCC scc;
    private int V;
    private int E;
    private int V2;
    private boolean[] v;
    public SAT (In in) {
        V = in.readInt();
        E = in.readInt();
        V2 = 2*V+1;
        G = new Digraph(V2);
        for (int i = 0; i < E; i++) {
            int v = in.readInt();
            if (v < 0) v = -v + V;
            int w = in.readInt();
            if (w < 0) w = -w + V;
            G.addEdge(negacao(w), v);
            G.addEdge(negacao(v), w);
        }
        scc = new KosarajuSharirSCC(G);
    }
    private int negacao (int v) {
        if (v > V) return v-V;
        else return v+V;
    }
    public boolean isSAT () {
        for (int i = 1; i < V; i++) 
            if(scc.stronglyConnected(i, negacao(i))) return false;
        return true;
    }
    public static void main(String[] args) {
        In in = new In();
        SAT st2 = new SAT(in); 
        if (st2.isSAT()) StdOut.println ("VERDADE");
        else StdOut.println("MENTIRA");
    }
}
