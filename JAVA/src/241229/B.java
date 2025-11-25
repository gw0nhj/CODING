public class B {
    public static void main(String[] args) {
        Cart MyCart = new Cart();
        MyCart.addBoost(5);
        MyCart.goBoost();

        MyCart.addBoost(15);
        MyCart.goBoost();

        MyCart.runBreak(25);
    }
}
