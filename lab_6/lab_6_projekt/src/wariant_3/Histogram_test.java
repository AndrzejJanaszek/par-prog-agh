package wariant_3;

import java.util.Scanner;

//wariant cykliczny
public class Histogram_test {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        System.out.println("Set image size: n (#rows), m(#kolumns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        final int ILOSC_ZNAKOW = 2;
        Obraz obraz_1 = new Obraz(n, m, ILOSC_ZNAKOW);

        obraz_1.calculate_histogram();
//        obraz_1.print_histogram();

        System.out.println("Set number of threads");
        int num_threads = scanner.nextInt();
//        int num_threads = ILOSC_ZNAKOW;
//        int znaki_per_watek = (int) Math.ceil((double) obraz_1.ILOSC_ZNAKOW / num_threads);

        Thread[] threads = new Thread[num_threads];

        for (int i = 0; i < num_threads; i++) {
//            cykliczny
//            int wiersz_start = i;
//            int wiersz_koniec = n;
//            int wiersz_skok = num_threads;
//            int kol_start = 0;
//            int kol_koniec = m;
//            int kol_skok = 1;

            // blokowy
            int kol_na_watek = (int)Math.ceil(m/num_threads);
            int wiersz_start = 0;
            int wiersz_koniec = n;
            int wiersz_skok = 1;

            int kol_start = i*kol_na_watek;
            int kol_koniec = (i+1)*kol_na_watek;
            int kol_skok = 1;

            threads[i] = new Thread(new Watek(i,
                    wiersz_start, wiersz_koniec, wiersz_skok,
                    kol_start, kol_koniec, kol_skok, obraz_1));
            threads[i].start();
        }

        for (int i = 0; i < num_threads; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
            }
        }

        obraz_1.drukuj_histogram(1);

        System.out.println("Czy są równe: " + obraz_1.czy_histogramy_sa_rowne());

    }
}