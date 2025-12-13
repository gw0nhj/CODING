//p36 참조자 연습

#include <iostream>

int main() {

    int a = 3;
    int &other_a = a;
    std::cout << a << std::endl;

    other_a = 17;
    std::cout << a << std::endl;

    return 0;
}