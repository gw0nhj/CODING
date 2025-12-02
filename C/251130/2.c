/* 헷갈림 */
#include <stdio.h>
struct TEST {
    int c;
    int pointer;
};

int main() {
    struct TEST t;
    struct TEST *pt = &t;
    int i = 3;

    t.pointer = i;
    printf("i : %d \n", i);
    /*
    -> 가 * 보다 우선순위가 높으므로 먼저 해석하게 된다.
    즉,
    (pt 가 가리키는 구조체 변수의 pointer 멤버) 가 가리키는 변수의 값을 4 로
    바꾼다. 라는 뜻이다/
    */
    pt->pointer += 1;
    printf("i : %d \n", pt->pointer);
    return 0;
}
