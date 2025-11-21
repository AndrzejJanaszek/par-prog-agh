package wariant_4_2d;

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
        int num_threads_wier = 3; //= scanner.nextInt();
        int num_threads_kol = 3; //= scanner.nextInt();
//        int num_threads = ILOSC_ZNAKOW;
//        int znaki_per_watek = (int) Math.ceil((double) obraz_1.ILOSC_ZNAKOW / num_threads);

        Thread[][] threads = new Thread[num_threads_wier][num_threads_kol];

        int kol_na_watek = (int)Math.ceil((double)m/num_threads_kol);
        int wier_na_watek = (int)Math.ceil((double)m/num_threads_wier);
        for (int i = 0; i < num_threads_wier; i++) {
            for (int j = 0; j < num_threads_kol; j++) {
                int wiersz_start = i*wier_na_watek;
                int wiersz_koniec = (i+1)*wier_na_watek;
                int wiersz_skok = 1;

                int kol_start = j*kol_na_watek;
                int kol_koniec = (j+1)*kol_na_watek;
                int kol_skok = 1;

                if(kol_koniec > m) kol_koniec = m;
                if(wiersz_koniec > n) wiersz_koniec = n;

                if(kol_start > m) kol_start = m;
                if(wiersz_start > n) wiersz_start = n;

                threads[i][j] = new Thread(new Watek(i,
                        wiersz_start, wiersz_koniec, wiersz_skok,
                        kol_start, kol_koniec, kol_skok, obraz_1));
                threads[i][j].start();
            }
        }

        for (int i = 0; i < num_threads_wier; i++) {
            for (int j = 0; j < num_threads_kol; j++) {
            try {
                threads[i][j].join();
            } catch (InterruptedException e) {
            }}
        }

        obraz_1.drukuj_histogram(1);

        System.out.println("Czy są równe: " + obraz_1.czy_histogramy_sa_rowne());

    }
}