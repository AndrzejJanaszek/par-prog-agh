public class Pisarz implements Runnable {

    private final int id;
    private final Czytelnia czytelnia;

    public Pisarz(int id, Czytelnia czytelnia) {
        this.id = id;
        this.czytelnia = czytelnia;
    }

    @Override
    public void run() {
        try {
            while (true) {
                czytelnia.chcePisac();
                try {
                    czytelnia.pisze(id);
                } finally {
                    czytelnia.koniecPisania();
                }

                // czas "poza pisaniem"
                Thread.sleep((long) (Math.random() * 1500));
            }
        } catch (InterruptedException e) {
            System.out.printf("PISARZ %d: przerwany%n", id);
        }
    }
}
