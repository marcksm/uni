import java.util.NoSuchElementException;

class BST<Key extends Comparable<Key>, Value> {
   public Node root;
   private Node first;
   private Node last;
   private int N2;
   public Node aux;
   private class Node {
      private Key key;
      private Value val;
      private Node left, right, next;
      private int N;

      public Node (Key key, Value val, int N) {
         this.key = key;
         this.val = val;
         this.N = N;
      }
   }
   public boolean isEmpty2() {
      return first == null;
   }
   public Key peak () {
      if (isEmpty2()) throw new NoSuchElementException("Queue underflow");
      return first.key;
   }
   public Node dequeue () {
      if (isEmpty2()) throw new NoSuchElementException("Queue underflow");
      Node item = first;
      first = first.next;
      N2--;
      if (isEmpty2()) last = null;
      return item;
   }
   public void enqueue (Node item) {
      if (item == null) return;
      Node oldlast = last;
      last = new Node (item.key, item.val, item.N);
      last = item;
      last.next = null;
      if (isEmpty2()) first = last;
      else oldlast.next = last;
      N2++;
   }

   public BST(){
      first = null;
      last = null;
      N2 = 0;

   } 

   public boolean isEmpty() {
      return size() == 0;
   }
   public int size() {
      return size(root);
   }
   private int size (Node x) {
      if (x == null) return 0;
      else return x.N;
   }
   public boolean contains (Key key) {
      if (key == null) throw new NullPointerException("argument null");
      return get (key) != null;
   }
   public Value get (Key key) {
      return get (root, key);
   }
   private Value get (Node x, Key key) {
      if (x== null) return null;
      int cmp = key.compareTo (x.key);
      if      (cmp < 0) return get (x.left, key);
      else if (cmp > 0) return get (x.right, key);
      else              return x.val;
   }
   public void put (Key key, Value val) {
      root = put (root, key, val);
   }
   private Node put (Node x, Key key, Value val) {
      if (x == null) return new Node(key, val, 1);
      int cmp = key.compareTo(x.key);
      if      (cmp < 0) x.left  = put(x.left,  key, val);
      else if (cmp > 0) x.right = put(x.right, key, val);
      else              x.val   = val;
      x.N = 1 + size(x.left) + size(x.right);
      return x;
   }
   public void erd(Node root) {
      if (root == null) return;
      erd(root.left);
      StdOut.println(root.key);
      erd(root.right);
   }
   public void level (Node x) {
      enqueue(x);
      while (!isEmpty2()) {
         Node aux = dequeue();
         if (aux == null) continue;
         StdOut.print (aux.key + " ");
         enqueue(aux.left);
         enqueue(aux.right);
      }
   }
   public Node find (Key k, Node x) {
      if (x == null) return null;
      int cmp = k.compareTo (x.key);
      if (cmp == 0) return x;
      if (cmp < 0 ) return find (k, x.left);
      if (cmp > 0) return find (k, x.right);
      return null;
   }
}

public class LevelTransversal {
   public static void main (String[] args) {
      BST<Integer, Integer> bst = new BST<Integer, Integer>();
      int N = StdIn.readInt();
      int M = StdIn.readInt();
      for (int i = 0; i < N; i++) {
         int aux = StdIn.readInt();
         bst.put (aux, aux);
      }
      for (int i = 0; i < M; i++) {
         int aux = StdIn.readInt();
         bst.aux = bst.find (aux, bst.root);
         bst.level (bst.aux);
         StdOut.println();
      }
   }
}

















































