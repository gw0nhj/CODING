//포토캐논 복사생성자 연습
//p103

#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

class Photon_Cannon {
    private:
        int hp, shield;
        int coord_x, coord_y;
        int damage;
    public:
        Photon_Cannon(int x, int y);
        Photon_Cannon(const Photon_Cannon &pc);

        void show_status();
};

int main ()
{
    Photon_Cannon P1(3, 5);
    Photon_Cannon P2(P1);

    P2.show_status();

    return 0;
}

Photon_Cannon::Photon_Cannon(int x, int y) {
    cout << "생성 완료" << endl;
    hp = shield = 100;
    coord_x = x;
    coord_y = y;
    damage = 20;
}

Photon_Cannon::Photon_Cannon(const Photon_Cannon &pc) {
    cout << "복사 완료" << endl;
    hp = pc.hp;
    shield = pc.shield;
    damage = pc.damage;
    coord_x = pc.coord_x;
    coord_y = pc.coord_y;
}

void Photon_Cannon::show_status() {
    cout << " " << endl;
    cout << "STATUS" << endl;
    cout << "======" << endl;
    cout << "HP: " << hp << endl << "shield: " << shield << endl;
    cout << "damage: " << damage << endl;
    cout << "located in " << coord_x << ", " << coord_y << endl;
}