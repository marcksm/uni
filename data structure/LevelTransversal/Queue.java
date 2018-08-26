
import java.util.NoSuchElementException;

public class Queue <Key extends Comparable<Key>, Value> {
   private Node<Key> first;
   private Node<Key> last;
   private int N2;

   private static class Node <Key> {
      private Key item;
      private Node<Key> next;
   }

   public Queue () {
      first = null;
      last = null;
      N2 = 0;
   }
   public boolean isEmpty2() {
      return first == null;
   }
   public int size () {
      return N2;
   }
   public Key peak () {
      if (isEmpty2()) throw new NoSuchElementException("Queue underflow");
      return first.item;
   }
   public Key dequeue () {
      if (isEmpty2()) throw new NoSuchElementException("Queue underflow");
      Key item = first.item;
      first = first.next;
      N2--;
      if (isEmpty2()) last = null;
      return item;
   }
   public void enqueue (Key item) {
      Node<Key> oldlast = last;
      last = new Node<Key>();
      last.item = item;
      last.next = null;
      if (isEmpty2()) first = last;
      else oldlast.next = last;
      N2++;
   }
}















































