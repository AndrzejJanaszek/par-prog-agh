public class Czytelnik implements Runnable {

    private final int id;
    private final Czytelnia czytelnia;

    public Czytelnik(int id, Czytelnia czytelnia) {
        this.id = id;
        this.czytelnia = czytelnia;
    }

    @Override
    public void run() {
        try {
            while (true) {
                czytelnia.chceCzytac();
                try {
                    czytelnia.czytam(id);
                } finally {
                    czytelnia.koniecCzytania();
                }

                // trochę "czasu poza czytelnią"
                Thread.sleep((long) (Math.random() * 1000));
            }
        } catch (InterruptedException e) {
            System.out.printf("CZYTELNIK %d: przerwany%n", id);
        }
    }
}
