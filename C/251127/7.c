//255p Q5
//숫자의 편의성을 위해 2 < M, N < 11이라 가정.

#include <stdio.h>
#include <math.h>

int NtoTen(int Number, int N);
int TentoM(int Number, int M);

void main() {

    printf("4진법일 때 (1312)는 10진법일 때 %d\n", NtoTen(1312, 4));
    printf("이를 다시 2진법으로 변환하면 %d", TentoM(NtoTen(1312, 4), 2));

    return;

}

int NtoTen(int Number, int N) {

    int Quotient = Number;
    int Reminder = 0;

    int ReturnValue = 0;
    int i = 0;

    if(N > 10 || N < 2) {
        printf("ㅈㅅ 구현못함");
    }


    while(Quotient > 0) {
        Reminder = Quotient % 10;
        Quotient /= 10;

        if(Reminder >= N) {
            printf("잘못된 입력\n");
            return 0;
        }

        for(int j = 0; j < i; j++) {
            Reminder *= N;
        }

        ReturnValue += Reminder;

        i++;
    }

    return ReturnValue;
    
}

int TentoM(int Number, int M) {
    
    int Quotient = Number;
    int Reminder = 0;

    int ReturnValue = 0;
    int i = 0;

    if(M > 10 || M <= 1) {
        printf("잘못된 입력");
    }

    while(Quotient > 0) {
        Reminder = Quotient % M;
        Quotient /= M;

        for(int j = 0; j < i; j++) {
            Reminder *= 10;
        }

        ReturnValue += Reminder;

        i++;
    }

    return ReturnValue;

}