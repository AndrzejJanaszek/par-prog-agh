package zad1;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Simple_executor_test {

    private static final int NTHREADS = 10;
    private static final double dx = 0.1;
    private static final double a = 0;
    private static final double b = Math.PI;

    public static void main(String[] args) {
        // ############ SEKWENCYJNA CAŁKA ############
        Calka_callable c1 = new Calka_callable(a, b, dx);
        double wynik_sekwencyjny = c1.compute_integral();
        System.out.println("\n##############################");
        System.out.println("wynik sekwencyjny = " + wynik_sekwencyjny);
        System.out.println("##############################\n");

        // ############ CAŁKA PULA WATKOW ############

        List<Future<Double>> futures = new ArrayList<Future<Double>>();
        ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);

        double sub = (b-a)/NTHREADS;
        for (int i = 0; i < NTHREADS; i++) {
            Callable<Double> callable = new Calka_callable(i*sub, (i+1)*sub, dx);
            futures.add(executor.submit(callable));
        }

        // This will make the executor accept no new threads
        // and finish all existing threads in the queue
        executor.shutdown();

        double sum = 0;
        for (Future<Double> future : futures) {
            try{
                double result = future.get();
                System.out.println("Wynik dla jednego zadania: " + result);
                sum += result;
            }catch (Exception e){
                System.out.println(e.getMessage());
            }
        }
        System.out.println("##############################\n");
        System.out.println("Całka policzona sekwencyjnie: " + sum);
        System.out.println("Całka policzona wątkami: " + wynik_sekwencyjny);
        System.out.println("##############################\n");

//        // Wait until all threads finish
//        while (!executor.isTerminated()) {
//        }

    }
} 
