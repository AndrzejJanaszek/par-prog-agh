package wariant_2;

public class Watek implements Runnable {
    private int id;
    private char znak_start;
    private char znak_koniec;
    private Obraz obraz;

    public Watek(int id, char znak_start, char znak_koniec, Obraz obraz) {
        this.id = id;
        this.znak_start = znak_start;
        this.znak_koniec = znak_koniec;
        this.obraz = obraz;
    }

    @Override
    public void run() {
        obraz.zlicz_znaki_przedzial(znak_start, znak_koniec);
        obraz.drukuj_histogram_przedzial(id, znak_start, znak_koniec);
    }
}
