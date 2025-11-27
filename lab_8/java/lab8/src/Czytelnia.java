// Czytelnia.java
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Czytelnia {

    private int liczbaCzyt = 0;
    private int liczbaPisz = 0;

    private final ReentrantLock lock = new ReentrantLock();
    private final Condition czytelnicy = lock.newCondition();
    private final Condition pisarze = lock.newCondition();

    // --- protokół wejścia pisarza ---
    public void chcePisac() throws InterruptedException {
        lock.lock();
        try {
            while (liczbaCzyt + liczbaPisz > 0) {
                pisarze.await();
            }
            liczbaPisz++;
        } finally {
            lock.unlock();
        }
    }

    public void pisze(int id) {
        System.out.printf("PISARZ %d: piszę (czyt=%d, pis=%d)%n", id, liczbaCzyt, liczbaPisz);
        try {
            Thread.sleep((long) (Math.random() * 500));
        } catch (InterruptedException ignored) {}
    }

    public void koniecPisania() {
        lock.lock();
        try {
            liczbaPisz--;

            if(lock.hasWaiters(pisarze)) {
                pisarze.signal();
            }else if (lock.hasWaiters(czytelnicy)) {
                czytelnicy.signal();
            }
        } finally {
            lock.unlock();
        }
    }

    public void chceCzytac() throws InterruptedException {
        lock.lock();
        try {
            while (liczbaPisz > 0 || lock.hasWaiters(pisarze)) {
                czytelnicy.await();
            }
            liczbaCzyt++;

            if (lock.hasWaiters(czytelnicy)) {
                czytelnicy.signal();
            }
        } finally {
            lock.unlock();
        }
    }

    public void czytam(int id) {
        System.out.printf("CZYTELNIK %d: czytam (czyt=%d, pis=%d)%n",
                id, liczbaCzyt, liczbaPisz);
        try {
            Thread.sleep((long) (Math.random() * 400));
        } catch (InterruptedException ignored) {}
    }

    public void koniecCzytania() {
        lock.lock();
        try {
            liczbaCzyt--;
            if (liczbaCzyt == 0 && lock.hasWaiters(pisarze)) {
                pisarze.signal();
            }
        } finally {
            lock.unlock();
        }
    }
}
