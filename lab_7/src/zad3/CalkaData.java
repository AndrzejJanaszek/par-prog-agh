package zad3;

public class CalkaData {
    private double sum = 0;

    synchronized public void addSum(double x){
        sum += x;
    }

    public synchronized double getSum(){
        return sum;
    }
}
