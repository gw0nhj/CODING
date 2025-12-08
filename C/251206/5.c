//prgama 사용 예시
#include <stdio.h>
// #pragma pack(1)

struct Six {
    char arr[2];
    int N;
};

int main() {
    struct Six Data;
    printf("%d", sizeof(Data));

    return 0;
}