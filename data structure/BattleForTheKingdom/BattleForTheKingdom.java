public class BattleForTheKingdom {
    private int V;
    private int E;    
    private int K;
    private int feiticeiro;
    private int[] herois;
    private Queue<Integer> cidadesRestantes;
    EdgeWeightedDigraph G;
    
    public BattleForTheKingdom (In in) {
        V = in.readInt();
        E = in.readInt();
        K = in.readInt();
        herois = new int[K];
        if (E < 0) throw new IllegalArgumentException("Number of edges must be nonnegative");
        G = new EdgeWeightedDigraph(V);
        for (int i = 0; i < E; i++) {
            int v = in.readInt();
            int w = in.readInt();
            if (v < 0 || v >= V) throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V-1));
            if (w < 0 || w >= V) throw new IndexOutOfBoundsException("vertex " + w + " is not between 0 and " + (V-1));
            int tempo = in.readInt();
            G.addEdge(new DirectedEdge(v, w, tempo));
        }
        for (int i = 0; i < K; i++) herois[i] = in.readInt();
        feiticeiro = in.readInt();
        cidadesSeguras ();
    }

    public void cidadesSeguras () {
        int tempoFeit, tempoHeroi, cidades, aux, cidade;
        aux = 0;
        cidades = V;
        cidadesRestantes = new Queue<Integer>();
        for (int i = 0; i < V; i++) cidadesRestantes.enqueue(i);
        DijkstraSP fc = new DijkstraSP(G, feiticeiro);
        for (int i = 0; i < K; i++) {
            DijkstraSP hc = new DijkstraSP(G, herois[i]);
            for (int x = 0; x < cidades; x++) {
                cidade = (Integer)cidadesRestantes.dequeue();
                tempoFeit = (int)fc.distTo(cidade);
                tempoHeroi = (int)hc.distTo(cidade);
                if (tempoFeit < tempoHeroi) {
                   aux++;
                }
                else cidadesRestantes.enqueue(cidade);
            }
            cidades = cidades - aux;
            aux = 0;
            if (cidades <= 0) break;
        }


    }
    public void pontosSeguros () {
        if (!cidadesRestantes.isEmpty()) {
            StdOut.println("VICTORY AND HAPPY EVER AFTER");
            StdOut.println(cidadesRestantes.size());
            while (!cidadesRestantes.isEmpty()) {
                int x = cidadesRestantes.dequeue();
                StdOut.print(x + " ");
            }
            StdOut.println();
         }
         else StdOut.println("DEMISE OF THE KINGDOM");
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        BattleForTheKingdom B = new BattleForTheKingdom(in);

        B.pontosSeguros();

    }

}
