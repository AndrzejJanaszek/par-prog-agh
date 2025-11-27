public class Main {
    public static void main(String[] args) {

        Czytelnia czytelnia = new Czytelnia();

        int liczbaCzytelnikow = 10;
        int liczbaPisarzy = 5;

        for (int i = 0; i < liczbaCzytelnikow; i++) {
            new Thread(new Czytelnik(i, czytelnia), "Czytelnik-" + i).start();
        }

        for (int i = 0; i < liczbaPisarzy; i++) {
            new Thread(new Pisarz(i, czytelnia), "Pisarz-" + i).start();
        }
    }
}
