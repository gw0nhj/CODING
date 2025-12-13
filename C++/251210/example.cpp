#include <iostream>
#include <cstring> // C++에서는 <string.h> 대신 <cstring> 사용

// **********************************************
// 1. Point 클래스의 멤버 접근자 추가 (OOP 관점)
// **********************************************
class Marine {
private:
    int hp;
    int coord_x, coord_y;
    int damage;
    bool is_dead;
    char* name; // 동적 할당 멤버

    // 헬퍼 함수: 이름을 깊은 복사
    void copy_name(const char* marine_name);

public:
    // ** 생성자 및 소멸자 **
    Marine();
    Marine(int x, int y, const char* marine_name);
    Marine(int x, int y);
    ~Marine();

    // ** 1. 🚨 치명적인 문제 해결: 깊은 복사를 위한 복사 생성자 및 대입 연산자 **
    Marine(const Marine& other); // 복사 생성자 (Deep Copy)
    Marine& operator=(const Marine& other); // 복사 대입 연산자 (Deep Copy)

    // ** 멤버 함수 **
    int attack() const; // 객체의 상태를 변경하지 않으므로 const 지정
    void be_attacked(int damage_earn);
    void move(int x, int y);
    void show_status() const; // 객체의 상태를 변경하지 않으므로 const 지정
};

// ----------------------------------------------------
// 2. 구현부 (Implementation)
// ----------------------------------------------------

// 이름 복사를 위한 헬퍼 함수
void Marine::copy_name(const char* marine_name) {
    if (marine_name) {
        name = new char[std::strlen(marine_name) + 1];
        std::strcpy(name, marine_name);
    } else {
        name = nullptr; // nullptr 사용
    }
}

// 기본 생성자
Marine::Marine() : hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false), name(nullptr) {}

// 이름 지정 생성자
Marine::Marine(int x, int y, const char* marine_name) 
    : hp(50), coord_x(x), coord_y(y), damage(5), is_dead(false) {
    copy_name(marine_name);
}

// 좌표 지정 생성자
Marine::Marine(int x, int y) 
    : hp(50), coord_x(x), coord_y(y), damage(5), is_dead(false), name(nullptr) {}

// 소멸자
Marine::~Marine() {
    std::cout << (name ? name : "Unknown Marine") << " 의 소멸자 호출 ! " << std::endl;
    if (name != nullptr) { // nullptr 사용
        delete[] name;
        name = nullptr; // 안전을 위해 해제 후 포인터를 비웁니다.
    }
}

// 깊은 복사 생성자
Marine::Marine(const Marine& other)
    : hp(other.hp), coord_x(other.coord_x), coord_y(other.coord_y), 
      damage(other.damage), is_dead(other.is_dead) {
    copy_name(other.name);
}

// 깊은 복사 대입 연산자
Marine& Marine::operator=(const Marine& other) {
    // 1. 자기 자신에게 대입하는지 확인 (자체 대입 방지)
    if (this == &other) {
        return *this;
    }

    // 2. 현재 name 메모리 해제
    if (name != nullptr) {
        delete[] name;
    }

    // 3. 값 복사
    hp = other.hp;
    coord_x = other.coord_x;
    coord_y = other.coord_y;
    damage = other.damage;
    is_dead = other.is_dead;

    // 4. 새로운 이름 메모리 할당 및 복사 (깊은 복사)
    copy_name(other.name);

    return *this;
}

void Marine::move(int x, int y) {
    coord_x = x;
    coord_y = y;
}

int Marine::attack() const { return damage; }

void Marine::be_attacked(int damage_earn) {
    hp -= damage_earn;
    if (hp <= 0) is_dead = true;
}

void Marine::show_status() const {
    std::cout << " *** Marine : " << (name ? name : "Unknown") << " ***" << std::endl;
    std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
    std::cout << " HP : " << hp << std::endl;
    std::cout << " Dead : " << (is_dead ? "Yes" : "No") << std::endl;
}

// ----------------------------------------------------
// 3. main 함수
// ----------------------------------------------------

int main() {
    // 마린 포인터 배열 (C-스타일 배열 대신 std::vector<Marine*> 권장되지만, 원본 유지)
    Marine* marines[100] = { nullptr, }; 
    
    // new를 사용했으므로 delete를 통해 메모리 해제 책임이 있습니다.
    marines[0] = new Marine(2, 3, "Marine 2");
    marines[1] = new Marine(1, 5, "Marine 1");

    marines[0]->show_status();
    marines[1]->show_status();

    std::cout << "\n마린 1 이 마린 2 를 공격! " << std::endl;
    marines[0]->be_attacked(marines[1]->attack());

    marines[0]->show_status();
    marines[1]->show_status();

    // 🛑 동적 할당된 메모리 해제
    delete marines[0]; 
    delete marines[1];
    
    // 이 시점에서 소멸자 호출 출력 확인
    
    return 0;
}