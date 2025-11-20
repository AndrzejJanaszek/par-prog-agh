package zad2;

import java.util.Arrays;
import java.util.concurrent.ForkJoinPool;

public class Main {
    public static void main(String[] args) {
        ForkJoinPool pool = new ForkJoinPool();
        int[] arr = {2,1,3,4,2,0,9};
        DivideTask task = new DivideTask(arr);
        pool.invoke(task);
//        pool.execute(task);
        pool.submit(task);

        int[] resuklt_arr = task.join();

        System.out.println("Początkowa tablica: " + Arrays.toString(arr));
        System.out.println("Posortowana tablica: " + Arrays.toString(resuklt_arr));
    }
}
