package zad4;

public class CalkaData {
    private double res = 0;

    synchronized void addRes(double res) {
        this.res += res;
    }
    synchronized double getRes() {
        return res;
    }
}
