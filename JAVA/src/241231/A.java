

public class A {

    public static void main(String[] args) {
        
        Singleton obj1 = Singleton.getInstance();
        Singleton obj2 = Singleton.getInstance();

        if(obj1 == obj2) {
            System.err.println("Yes_Muhyeon");
        }

        System.out.println(Earth.EARTH_RADIUS);
        System.out.println(Earth.EARTH_AREA);
    }
}
