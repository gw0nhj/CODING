public class A {
    public static void main(String[] args) {
        Com PC0 = new Com();
        int X = 3;
        int Y = 3;
        int P = PC0.plus(X, Y);
        int M = PC0.minus(X, Y);
        int mul = PC0.multi(X, Y);
        double div = PC0.div(X, Y);

        System.out.println(P + " " + M + " " + mul + " " + (int) div);
    }
}
