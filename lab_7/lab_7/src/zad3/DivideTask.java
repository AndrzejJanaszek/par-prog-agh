package zad3;

import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.concurrent.RecursiveTask;

class DivideTask extends RecursiveTask<int[]> {

    int[] arrayToDivide;

    public DivideTask(int[] arrayToDivide) {
        this.arrayToDivide = arrayToDivide;
    }

    protected int[] compute() {
        if(arrayToDivide.length==1){
            return arrayToDivide;
        }
        int[] left_arr = Arrays.copyOfRange(arrayToDivide, 0, arrayToDivide.length / 2);
        int[] right_arr = Arrays.copyOfRange(arrayToDivide, arrayToDivide.length / 2, arrayToDivide.length);

        DivideTask task1 = new DivideTask(left_arr);
        DivideTask task2 = new DivideTask(right_arr);

        task1.fork();
        task2.fork();

        //Wait for results from both tasks
        int[] tab1 = task1.join();
        int[] tab2 = task2.join();

        int[] scal_tab_arr = new int[tab1.length + tab2.length];

        scal_tab(tab1, tab2, scal_tab_arr);

        return scal_tab_arr;
    }

    private void scal_tab(
            int[] tab1,
            int[] tab2,
            int[] scal_tab) {

        int i = 0, j = 0, k = 0;

        while ((i < tab1.length) && (j < tab2.length)) {

            if (tab1[i] < tab2[j]) {
                scal_tab[k] = tab1[i++];
            } else {
                scal_tab[k] = tab2[j++];
            }

            k++;
        }

        if (i == tab1.length) {

            for (int a = j; a < tab2.length; a++) {
                scal_tab[k++] = tab2[a];
            }

        } else {

            for (int a = i; a < tab1.length; a++) {
                scal_tab[k++] = tab1[a];
            }

        }
    }

}