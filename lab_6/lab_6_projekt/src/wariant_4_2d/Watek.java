package wariant_4_2d;

public class Watek implements Runnable {
    private int id;
    private int wiersz_start;
    private int wiersz_koniec;
    private int wiersz_skok;
    private int kol_start;
    private int kol_koniec;
    private int kol_skok;
    private Obraz obraz;

    public Watek(int id, int wiersz_start, int wiersz_koniec, int wiersz_skok, int kol_start, int kol_koniec, int kol_skok, Obraz obraz) {
        this.id = id;

        this.wiersz_start = wiersz_start;
        this.wiersz_koniec = wiersz_koniec;;
        this.wiersz_skok = wiersz_skok;

        this.kol_start = kol_start;
        this.kol_koniec = kol_koniec;
        this.kol_skok = kol_skok;

        this.obraz = obraz;
    }

    @Override
    public void run() {
        obraz.zlicz_znaki_obszar(wiersz_start, wiersz_koniec, wiersz_skok, kol_start, kol_koniec, kol_skok);
//        obraz.drukuj_histogram(id);
    }
}
