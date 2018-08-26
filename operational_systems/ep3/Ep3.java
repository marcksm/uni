/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/

import java.util.Scanner;
import java.io.File;

public class Ep3 {

    public static void prompt () {
        Simulation.testMode = false;
        Scanner in = new Scanner (System.in);
        while (true) {
            System.out.printf ("(ep3): ");
            if (!in.hasNextLine ()) {
                System.out.println ();
                return;
            }
            String[] line = in.nextLine ().replaceAll ("^[ ]+", "").split ("[ ]+");
            if (line.length == 1 && line[0].isEmpty ()) continue;
            switch (line[0]) {
                case "carrega":
                    Simulation.trace = new File (line[1]);
                    break;
                case "espaco":
                    Simulation.spType = Integer.parseInt (line[1]);
                    break;
                case "substitui":
                    Simulation.pgType = Integer.parseInt (line[1]);
                    break;
                case "executa":
                    Simulation.interval = Integer.parseInt (line[1]);
                    Simulation.run ();
                    return;
                case "sai":
                    return;
                case "testMode":
                    Simulation.testMode = true;
                    break;
                default:
                    System.out.println ("Comando inválido");
                    break;

            }

        }
    }

    public static void main (String[] args) {
        prompt ();
    }

}
