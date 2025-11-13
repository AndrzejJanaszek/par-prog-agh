package wariant_1;

import java.util.Scanner;


public class Histogram_test {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        System.out.println("Set image size: n (#rows), m(#kolumns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        final int ILOSC_ZNAKOW = 5;
        Obraz obraz_1 = new Obraz(n, m, ILOSC_ZNAKOW);

        obraz_1.calculate_histogram();
        obraz_1.print_histogram();

        System.out.println("Set number of threads");
//         int num_threads = scanner.nextInt();
        int num_threads = ILOSC_ZNAKOW;

        Watek[] NewThr = new Watek[num_threads];

        for (int i = 0; i < num_threads; i++) {
            (NewThr[i] = new Watek(i, (char) (i + 33), obraz_1)).start();
        }

        for (int i = 0; i < num_threads; i++) {
            try {
                NewThr[i].join();
            } catch (InterruptedException e) {
            }
        }

        System.out.println("Czy są równe: " + obraz_1.czy_histogramy_sa_rowne());

    }
}