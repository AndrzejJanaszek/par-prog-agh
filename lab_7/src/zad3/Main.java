package zad3;

import zad1.Calka_callable;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Main {
    private static final int NTHREADS = 10;
    private static final double dx = 0.1;
    private static final double a = 0;
    private static final double b = Math.PI;

    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
        CalkaData data = new CalkaData();

        double sub = (b-a)/NTHREADS;
        for (int i = 0; i < NTHREADS; i++) {
            Runnable callable = new CalkaRunnable(i*sub, (i+1)*sub, dx, data);
            executor.execute(callable);
        }

        // This will make the executor accept no new threads
        // and finish all existing threads in the queue
        executor.shutdown();

//         Wait until all threads finish
        while (!executor.isTerminated()) {
        }

        double sum = 0;
        System.out.println("Wynik " + data.getSum());
    }
}
