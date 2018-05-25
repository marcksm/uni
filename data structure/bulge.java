public class bulge {
   public static void main (String[] args) {
      double size = Double.parseDouble (args[0]);
      StdDraw.setYscale (-size, size);
      StdDraw.setXscale (-size, size);
      double x = -size;
      double y = -size;
      double sqsize = (2 * size) / 15;
      double ssqsize = sqsize / 4;
      int color = 1;
      int test = 6;
      int i = 0;
      int b = 0;
      double rate = 1.30;
      while (true) {
         if (color == 1) StdDraw.setPenColor (StdDraw.BLACK);
         else StdDraw.setPenColor (StdDraw.WHITE);
         StdDraw.filledSquare (x + (sqsize / 2), y + (sqsize / 2), sqsize / 2);
         color = -color;
         if (y >= size) break;
         if (x + sqsize >= size) {
            y = y + sqsize;
            x = - size - sqsize;
            color = - color;
         }
         x = x + sqsize;
      }
      x = sqsize;
      y = sqsize;
      while (test > 1) {
         if (i == test) {
            if (b == 1) {
               color = -color;
               b = 0;
            }
            y = sqsize;
            x = x + sqsize;
            if (i % 2 == 0)  color = - color;
            i = 0;
            if (test == 5 || test == 4 || test == 3) {
               i = -1;
               b = 1;
            }

            test--;
         }
         if (color == 1) StdDraw.setPenColor (StdDraw.BLACK);
         else StdDraw.setPenColor (StdDraw.WHITE);
         StdDraw.filledSquare (x + rate*ssqsize , y - rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (x - rate*ssqsize , y + rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (x + rate*ssqsize , - y + rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (x - rate*ssqsize , - y - rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (- x - rate*ssqsize , y - rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (- x + rate*ssqsize , y + rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (- x + rate*ssqsize , - y - rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (- x - rate*ssqsize , - y + rate*ssqsize, ssqsize / 2);
         color = - color;
         i++;
         y = y + sqsize;
      }
      test = 6;
      y = 0;
      x = sqsize;
      color = - color;
      while (test >= 1) {
         if (color == 1) StdDraw.setPenColor (StdDraw.BLACK);
         else StdDraw.setPenColor (StdDraw.WHITE);

         StdDraw.filledSquare (x - rate*ssqsize , y + rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (x - rate*ssqsize , y - rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (y + rate*ssqsize , x - rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (y - rate*ssqsize , x - rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (- x + rate*ssqsize , y + rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (- x + rate*ssqsize , y - rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (y + rate*ssqsize , - x + rate*ssqsize, ssqsize / 2);
         StdDraw.filledSquare (y - rate*ssqsize , - x + rate*ssqsize, ssqsize / 2);
         x = x + sqsize;
         color = -color;
         test--;
      }
      StdDraw.show (20);
   }
}



































