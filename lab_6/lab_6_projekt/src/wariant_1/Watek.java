package wariant_1;

public class Watek extends Thread {
    private int id;
    private char znak;
    private Obraz obraz;

    public Watek(int id, char znak, Obraz obraz) {
        this.id = id;
        this.znak = znak;
        this.obraz = obraz;
    }

    @Override
    public void run() {
        obraz.zlicz_znak(znak);
        obraz.drukuj_histogram(id, znak);
    }
}
