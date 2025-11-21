package wariant_3;

import java.util.Random;


class Obraz {

    private int size_n;
    private int size_m;
    private char[][] tab;
    private char[] tab_symb;
    private int[] histogram;
    private int[] histogram_par;

    public int ILOSC_ZNAKOW = 5;

    public Obraz(int n, int m, int ile_znakow) {
        this.ILOSC_ZNAKOW = ile_znakow;

        this.size_n = n;
        this.size_m = m;
        tab = new char[n][m];
        tab_symb = new char[94];

        final Random random = new Random();

        // for general case where symbols could be not just integers
        for (int k = 0; k < 94; k++) {
            tab_symb[k] = (char) (k + 33); // substitute symbols
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                tab[i][j] = tab_symb[random.nextInt(ILOSC_ZNAKOW)];  // ascii 33-38
                //		tab[i][j] = tab_symb[random.nextInt(94)];  // ascii 33-127
                //tab[i][j] = (char)(random.nextInt(94)+33);  // ascii 33-127
                System.out.print(tab[i][j] + " ");
            }
            System.out.print("\n");
        }
        System.out.print("\n\n");

        histogram = new int[94];
        histogram_par = new int[94];
        clear_histogram();
    }

    public void clear_histogram() {
        for (int i = 0; i < 94; i++) histogram[i] = 0;
    }

    public void clear_histogram_par() {
        for (int i = 0; i < 94; i++) histogram_par[i] = 0;
    }

    public void calculate_histogram() {

        for (int i = 0; i < size_n; i++) {
            for (int j = 0; j < size_m; j++) {

                // optymalna wersja obliczania histogramu, wykorzystująca fakt, że symbole w tablicy
                // można przekształcić w indeksy tablicy histogramu
                // histogram[(int)tab[i][j]-33]++;

                // wersja bardziej ogólna dla tablicy symboli nie utożsamianych z indeksami
                // tylko dla tej wersji sensowne jest zrównoleglenie w dziedzinie zbioru znaków ASCII
                for (int k = 0; k < 94; k++) {
                    if (tab[i][j] == tab_symb[k]) histogram[k]++;
                    //if(tab[i][j] == (char)(k+33)) histogram[k]++;
                }

            }
        }

    }

// uniwersalny wzorzec dla różnych wariantów zrównoleglenia - można go modyfikować dla
// różnych wersji dekompozycji albo stosować tak jak jest zapisane poniżej zmieniając tylko
// parametry wywołania w wątkach
//
//calculate_histogram_wzorzec(start_wiersz, end_wiersz, skok_wiersz,
//                            start_kol, end_kol, skok_kol,
//                            start_znak, end_znak, skok_znak){
//
//  for(int i=start_wiersz;i<end_wiersz;i+=skok_wiersz) {
//     for(int j=start_kol;j<end_kol;j+=skok_kol) {
//        for(int k=start_znak;k<end_znak;k+=skok_znak) {
//           if(tab[i][j] == tab_symb[k]) histogram[k]++;
//


    public void print_histogram() {

        for (int i = 0; i < ILOSC_ZNAKOW; i++) {
            System.out.print(tab_symb[i] + " " + histogram[i] + "\n");
            //System.out.print((char)(i+33)+" "+histogram[i]+"\n");
        }

    }

    public void zlicz_znak(char znak) {
        int count = 0;
        for (int i = 0; i < size_n; i++) {
            for (int j = 0; j < size_m; j++) {
                if (tab[i][j] == znak) count++;
            }
        }
        histogram_par[znak - 33] = count;
    }

    public synchronized void drukuj_histogram(int id, char znak) {
        int count = histogram_par[znak - 33];
        System.out.print("Wątek " + id + ": " + znak + " ");
        for (int i = 0; i < count; i++) System.out.print("=");
        System.out.println();
    }

    public synchronized void drukuj_histogram(int id) {

        for(int k = 0; k < ILOSC_ZNAKOW; k++){
            int count = histogram_par[k];
            System.out.print("Wątek " + id + ": " + (char)(k+33) + " ");

            for (int i = 0; i < count; i++) System.out.print("=");
            System.out.println();
        }
    }

    public boolean czy_histogramy_sa_rowne() {
        for (int i = 0; i < ILOSC_ZNAKOW; i++) {
            if (histogram_par[i] != histogram[i]) {
                return false;
            }
        }
        return true;
    }

    public void zlicz_znaki_obszar(int wiersz_start, int wiersz_koniec, int wiersz_skok,
                                   int kol_start, int kol_koniec, int kol_skok) {
        int[] tmp_arr = new int[ILOSC_ZNAKOW];

        for(int i = 0; i < ILOSC_ZNAKOW; i++) {
            tmp_arr[i] = 0;
        }

//        System.out.println("Watek;");

        for (int i = wiersz_start; i < wiersz_koniec; i += wiersz_skok) {
            for (int j = kol_start; j < kol_koniec; j += kol_skok) {

                for(int k = 0; k < ILOSC_ZNAKOW; k++) {
                    if (tab[i][j] == tab_symb[k]) tmp_arr[k]++;
                }
            }
        }

        System.out.println(wiersz_start + " " + wiersz_koniec + " " +  wiersz_skok  + " " + kol_start + " " +  kol_koniec + " " +  kol_skok);

        synchronized (this) {
            for(int i = 0; i < ILOSC_ZNAKOW; i++) {
                histogram_par[i] += tmp_arr[i];
            }
        }
    }
}
