public class Cart {
    int booster = 0;
    int velocity = 0;
    
    static String modelName = "카트";

    void addBoost(int x) {
        this.booster += x;
        System.out.println(x + "개의 부스트가 충전되었습니다.");
        System.out.println("잔여 부스트는 " + this.booster + "개입니다.");
    }


    void goBoost() {
        while(this.booster > 0) {
            this.velocity += 10;
            this.booster -= 1;
            System.out.println("가속 중입니다..");
            System.out.println("잔여 부스트: " + this.booster + "개, 현재 속도: " + this.velocity + "km/h");
        }

        if(this.booster == 0) {
            System.out.println("남은 부스트가 없습니다.");
        }
    }

    void runBreak(int x) {
        for(int i = 0; i < x; i++) {
            if(this.velocity > 0) {
                this.velocity -= 10;
                System.out.println("감속중.. 현재 속도: " + this.velocity + "km/h");
            }
            else {
                System.out.println("차량이 멈춥니다.");
                break;
            }
        }
    }
}
