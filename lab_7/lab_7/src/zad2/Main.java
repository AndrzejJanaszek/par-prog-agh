package zad2;

import zad1.Calka_callable;
import zad1.Counter;
import zad1.CounterPlus;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Main {
    private static final int NTHREADS = 10;
    private static final double a = 0;
    private static final double b = Math.PI;
    private static final double dx = 0.1;

    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
        List<Future<Double>> list = new ArrayList<Future<Double>>();

        double sub = (b-a)/NTHREADS;
        for (int i = 0; i < NTHREADS; i++) {
            Callable<Double> callable = new Calka_callable(i*sub, (i+1)*sub,dx);
            Future<Double> fut = executor.submit(callable);

            list.add(fut);
        }

        double sum = 0;
        for(Future<Double> future : list){
            try{
                sum+=future.get();
//                System.out.println(future.get());
            }catch(Exception e){
                System.out.println(e.getMessage());
            }
        }

        System.out.println("Suma: " + sum);

//        // This will make the executor accept no new threads
//        // and finish all existing threads in the queue
//        executor.shutdown();
//
//        // Wait until all threads finish
//        while (!executor.isTerminated()) {}

    }
}
