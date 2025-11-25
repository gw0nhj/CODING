public class Com {
    boolean ON;
    void PowerON() {
        ON = true;
    }
    void PowerOFF() {
        ON = false;
    }

    int plus(int x, int y) {
        int result = x + y;
        return result;
    }

    int plus_0(int x) {
        return plus(x, 1);
    }

    int minus(int x, int y) {
        return x - y;
    }

    int multi(int x, int y) {
        return x * y;
    }

    double div(int x, int y) {
        return (double) x / (double) y;
    }
}