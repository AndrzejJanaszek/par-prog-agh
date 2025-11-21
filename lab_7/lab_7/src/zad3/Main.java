package zad3;

import java.util.Arrays;
import java.util.concurrent.ForkJoinPool;

public class Main {

    public static void main(String[] args) {
        ForkJoinPool pool = new ForkJoinPool();
        int[] arr = {2,1,3,7};
        DivideTask task = new DivideTask(arr);
        pool.invoke(task);

        pool.submit(task);

        int [] res = task.join();
        System.out.println( Arrays.toString(res) );
    }
}
