package zad4;

import zad1.Counter;
import zad1.CounterPlus;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    private static final int NTHREADS = 10;
    private static final double a = 0;
    private static final double b = Math.PI;
    private static final double dx = 0.1;

    public static void main(String[] args) {

        ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);

        CalkaData data = new CalkaData();

        double sub = (b-a)/NTHREADS;
        for (int i = 0; i < 50; i++) {
            Runnable worker = new CalkaRunnable(i*sub, (i+1)*sub,dx,data);
            executor.execute(worker);
        }

        executor.shutdown();

        // Wait until all threads finish
        while (!executor.isTerminated()) {}

        System.out.println(data.getRes());
    }
}
