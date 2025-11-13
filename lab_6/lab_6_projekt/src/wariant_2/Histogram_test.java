package wariant_2;

import java.util.Scanner;


public class Histogram_test {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        System.out.println("Set image size: n (#rows), m(#kolumns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        final int ILOSC_ZNAKOW = 50;
        Obraz obraz_1 = new Obraz(n, m, ILOSC_ZNAKOW);

        obraz_1.calculate_histogram();
        obraz_1.print_histogram();

        System.out.println("Set number of threads");
         int num_threads = scanner.nextInt();
//        int num_threads = ILOSC_ZNAKOW;
        int znaki_per_watek = (int) Math.ceil((double) obraz_1.ILOSC_ZNAKOW / num_threads);

        Thread[] threads = new Thread[num_threads];

        for (int i = 0; i < num_threads; i++) {
            char start = (char)(i*znaki_per_watek + 33);
            char end = (char)((i+1)*znaki_per_watek + 33);
            if(end > (ILOSC_ZNAKOW+33)) end = (char)(ILOSC_ZNAKOW+33);

            if(start > (ILOSC_ZNAKOW+33)) {
                end = (char)0;
                start = (char)1;
            }

            threads[i] = new Thread( new Watek(i, start, end, obraz_1) );
            threads[i].start();
        }

        for (int i = 0; i < num_threads; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
            }
        }

        System.out.println("Czy są równe: " + obraz_1.czy_histogramy_sa_rowne());

    }
}