#include <stdio.h>
#include <string.h> // memset 사용을 위해 포함

#define SIZE 5
#define DoubleSIZE SIZE * 2

// C 표준에 맞게 구조체 정의에서 초기화 부분을 제거합니다.
struct BigNum {
    int i_digit[SIZE];
    int d_digit[SIZE];

    int i_total_digit;
    int d_total_digit;
    char sign;  // 1 = 음수, 0 = 양수
};

struct ResultBigNum
{
    int i_digit[DoubleSIZE];
    int d_digit[SIZE];

    int i_total_digit;
    int d_total_digit;
    char sign;  // 1 = 음수, 0 = 양수
};


// BigNum 포인터를 받아서 내부 배열의 자릿수를 조정하는 함수
void UpResultBigNum(struct ResultBigNum *BigNum);
void UpBigNum(struct BigNum *BigNum);
// 테스트를 위한 출력 함수
void PrintBigNum(struct BigNum *BigNum);
void PrintResultBigNum(struct ResultBigNum *pBigNum);

int SizeOf_i_BigNum(struct BigNum *BigNum);
int SizeOf_d_BigNum(struct BigNum *pBigNum);

int SizeOf_i_ResultBigNum(struct ResultBigNum *pBigNum);
int SizeOf_d_ResultBigNum(struct ResultBigNum *pBigNum);

void SignChangeBigNum(struct BigNum *pBigNum);

void Add_BigNum(struct BigNum *BigNum, struct BigNum *BigNum2, struct ResultBigNum *Result);
void Subtract_BigNum(struct BigNum *BigNum, struct BigNum *BigNum2, struct ResultBigNum *Result);
void Multiply_BigNum(struct BigNum *BigNum, struct BigNum *BigNum2, struct ResultBigNum *Result);
void Divide_BigNum(struct BigNum *BigNum, struct BigNum *BigNum2, struct ResultBigNum *Result);


int main(void) {

    struct BigNum A1;
    memset(&A1, 0, sizeof(struct BigNum)); 
    struct BigNum *pA1 = &A1;

    struct BigNum A2;
    memset(&A2, 0, sizeof(struct BigNum)); 
    struct BigNum *pA2 = &A2;
    
    struct ResultBigNum Result;
    memset(&Result, 0, sizeof(struct ResultBigNum)); 
    struct ResultBigNum *pResult = &Result;

    pA1 -> i_digit[2] = 7;  // 100의 자리
    pA1 -> i_digit[1] = 5;  // 10의 자리
    pA1 -> i_digit[0] = 0;  // 1의 자리
    
    pA1 -> sign = 0;

    pA2 -> i_digit[3] = 0;
    pA2 -> i_digit[2] = 0;  // 100의 자리
    pA2 -> i_digit[1] = 3;  // 10의 자리
    pA2 -> i_digit[0] = 3;  // 1의 자리

    pA2 -> d_digit[0] = 0;
    pA2 -> d_digit[1] = 0;
    
    Divide_BigNum(pA1, pA2, pResult);

    PrintResultBigNum(pResult);

    return 0;
}

// 부호 변환 명령어. 값 자체는 같음

void SignChangeBigNum(struct BigNum *pBigNum) {

    pBigNum -> sign++;
    pBigNum -> sign %= 2;

    int D = SizeOf_d_BigNum(pBigNum); // 소수
    int N = SizeOf_i_BigNum(pBigNum); // 정수

    for(int i = 0; i < D; i++) {
        pBigNum->d_digit[i] =  (pBigNum->d_digit[i]) * (-1);
    }
    
    for(int i = 0; i < N; i++) {
        pBigNum->i_digit[i] =  (pBigNum->i_digit[i]) * (-1);
    }

}

/**
 * BigNum 구조체의 i_digit 배열을 순회하며 
 * 각 요소의 값이 9를 초과하면 다음 자릿수로 올림(Carry) 처리합니다.
 * BigNum은 포인터로 전달됩니다.
 */

void UpBigNum(struct BigNum *pBigNum)
{
    //소수 부분 자리수 정상화
    int carry = 0;
    for(int i = SIZE; i > 1; i--) {
        
        if(pBigNum->d_digit[i - 1] > 9) {
            
            carry = pBigNum->d_digit[i - 1] / 10;
            pBigNum->d_digit[i - 2] += carry;
            pBigNum->d_digit[i - 1] %= 10;

        }

        if(pBigNum->d_digit[i - 1] < 0) {
            
            carry = pBigNum->d_digit[i - 1] / (-10);
            pBigNum->d_digit[i - 2] -= carry + 1;
            pBigNum->d_digit[i - 1] += 10 * (carry + 1);

        }
    }


    if(pBigNum->d_digit[0] > 9) {
        carry = (pBigNum->d_digit[0]) / 10;
        pBigNum->i_digit[0] += carry;
        pBigNum->d_digit[0] %= 10;
    }

    //정수 부분 자리수 정상화
    if(pBigNum->d_digit[0] < 0) {
            
        carry = pBigNum->d_digit[0] / -10;
        pBigNum->i_digit[0] -= carry + 1;
        pBigNum->d_digit[0] += 10 * (carry + 1);

    }
    
    for(int i = 0; i < SIZE - 1; i++) {
        
        if(pBigNum->i_digit[i] > 9) {
            
            carry = pBigNum->i_digit[i] / 10;
            pBigNum->i_digit[i + 1] += carry;
            pBigNum->i_digit[i] %= 10;

        }

        if(pBigNum->i_digit[i] < 0) {
            
            carry = pBigNum->i_digit[i] / -10;
            pBigNum->i_digit[i + 1] -= carry + 1;
            pBigNum->i_digit[i] += 10 * (carry + 1);

        }

    }

    int F = SizeOf_d_BigNum(pBigNum);
    //부호 정상화
    if((pBigNum->i_digit[SIZE - 1]) < 0) {
        pBigNum->i_digit[SIZE - 1] *= -1;
        pBigNum->i_digit[SIZE - 1]--;
        pBigNum -> sign++;
        pBigNum -> sign %= 2;
        // 부호 정상화 과정에서의 보수 처리
        for(int i = 0; i < F; i++) {

            pBigNum -> d_digit[i] = 9 - (pBigNum -> d_digit[i]);
        }

        for(int i = 0; i < SIZE - 1; i++) {

            pBigNum->i_digit[i] = 9 - (pBigNum->i_digit[i]);

        }

        int trial = 0;
        while(1) {
            
            if(trial < F) {

                if(pBigNum->d_digit[F - 1 - trial] != 0) {
                    pBigNum->d_digit[F - 1 - trial] += 1;
                    break;
                }

            }

            if(trial >= SIZE){

                if (pBigNum->i_digit[trial - SIZE] != 0) {
                    pBigNum->i_digit[trial - SIZE] += 1;
                    break;
                }

            }
            
            trial++;

        }

        printf("%d\n", trial);

    }

    
}

void UpResultBigNum(struct ResultBigNum *pBigNum)
{
    //소수 부분 자리수 정상화
    int F = SizeOf_d_ResultBigNum(pBigNum);
    int carry = 0;
    for(int i = SIZE; i > 0; i--) {
        
        if(pBigNum->d_digit[i] > 9) {
            
            carry = pBigNum->d_digit[i] / 10;
            pBigNum->d_digit[i - 1] += carry;
            pBigNum->d_digit[i] %= 10;

        }

        if(pBigNum->d_digit[i] < 0) {
            
            carry = pBigNum->d_digit[i] / (-10);
            pBigNum->d_digit[i - 1] -= carry + 1;
            pBigNum->d_digit[i] += 10 * (carry + 1);

        }
    }

    carry = (pBigNum->d_digit[0]) / 10;
    pBigNum->i_digit[0] += carry;
    pBigNum->d_digit[0] %= 10;

    //정수 부분 자리수 정상화
    if(pBigNum->d_digit[0] < 0) {
            
        carry = pBigNum->d_digit[0] / (-10);
        pBigNum->i_digit[0] -= carry + 1;
        pBigNum->d_digit[0] += 10 * (carry + 1);

    }
    
    int N = SizeOf_i_ResultBigNum(pBigNum);

    for(int i = 0; i < DoubleSIZE - 1; i++) {
        
        if(pBigNum->i_digit[i] > 9) {
            
            carry = pBigNum->i_digit[i] / 10;
            pBigNum->i_digit[i + 1] += carry;
            pBigNum->i_digit[i] %= 10;

        }

        if(pBigNum->i_digit[i] < 0) {
            
            carry = pBigNum->i_digit[i] / -10;
            pBigNum->i_digit[i + 1] -= carry + 1;
            pBigNum->i_digit[i] += 10 * (carry + 1);

        }

    }

    //부호 정상화
    if(pBigNum->i_digit[DoubleSIZE - 1] < 0) {
        pBigNum->i_digit[DoubleSIZE - 1] *= -1;
        pBigNum->i_digit[DoubleSIZE - 1]--;
        pBigNum -> sign++;
        pBigNum -> sign %= 2;
        // 부호 정상화 과정에서의 보수 처리
        for(int i = 0; i < F; i++) {
            pBigNum->d_digit[i] = 9 - (pBigNum->d_digit[i]);
        }

        for(int i = 0; i < DoubleSIZE - 1; i++) {
            pBigNum->i_digit[i] = 9 - (pBigNum->i_digit[i]);
        }

        int trial = 0;
        while(1) {
            
            if(trial < SIZE) {

                if(pBigNum->d_digit[SIZE - 1 - trial] != 0) {
                    pBigNum->d_digit[SIZE - 1 - trial] += 1;
                    break;
                }

            }

            if(trial >= SIZE){

                if (pBigNum->i_digit[trial - SIZE] != 0) {
                    pBigNum->i_digit[trial - SIZE] += 1;
                    break;
                }

            }
            
            trial++;

        }
        
        printf("%d\n", trial);
    }

}

void Add_BigNum(struct BigNum *BigNum, struct BigNum *BigNum2, struct ResultBigNum *Result) {

    if(BigNum -> sign) {
        SignChangeBigNum(BigNum);
    }

    if(BigNum2 -> sign) {
        SignChangeBigNum(BigNum2);
    }

    for(int i = 0; i < SIZE; i++) {
        
        Result -> d_digit[i] = BigNum -> d_digit[i] + BigNum2 -> d_digit[i];
        Result -> i_digit[i] = BigNum -> i_digit[i] + BigNum2 -> i_digit[i];

    }


    UpResultBigNum(Result);

}

void Subtract_BigNum(struct BigNum *BigNum, struct BigNum *BigNum2, struct ResultBigNum *Result) {

    for(int i = 0; i < SIZE; i++) {
        
        Result -> d_digit[i] = BigNum -> d_digit[i] - BigNum2 -> d_digit[i];
        Result -> i_digit[i] = BigNum -> i_digit[i] - BigNum2 -> i_digit[i];

    }

    UpResultBigNum(Result);

}

void Multiply_BigNum(struct BigNum *BigNum, struct BigNum *BigNum2, struct ResultBigNum *Result) {
    
    Result -> sign = ((BigNum ->sign) + (BigNum2 -> sign)) % 2;
    int Arr1[SIZE + SIZE], Arr2[SIZE + SIZE] = {0};
    int ResultArr[(DoubleSIZE) * 2] = {0};
    int I_ResultArr[DoubleSIZE] = {0};
    int D_ResultArr[SIZE] = {0};
    
    //배열 복사(소숫점 없다고 가정)
    for(int i = 0; i < SIZE; i++) {
        Arr1[i] = BigNum ->d_digit[SIZE - 1 - i];
    }
    for(int i = SIZE; i < SIZE + SIZE; i++) {
        Arr1[i] = BigNum ->i_digit[i - SIZE];
    }


    for(int i = 0; i < SIZE; i++) {
        Arr2[i] = BigNum2 ->d_digit[SIZE - 1 - i];
    }
    for(int i = SIZE; i < SIZE + SIZE; i++) {
        Arr2[i] = BigNum2 ->i_digit[i - SIZE];
    }


    //배열끼리 곱
    for(int i = 0; i < DoubleSIZE; i++) {

        for(int j = 0; j < DoubleSIZE; j++) {
            if(Arr1[i] * Arr2[j] != 0) {
                ResultArr[i + j + 1] += Arr1[i] * Arr2[j];
            }
        }

    }

    int carry = 0;

    for(int i = 0; i < DoubleSIZE * 2 - 1; i++) {
        carry = ResultArr[i] / 10;
        ResultArr[i] %= 10;
        ResultArr[i + 1] += carry;
    }

    for(int i = 0; i < DoubleSIZE; i++) {
        I_ResultArr[i] = ResultArr[i + SIZE * 2 + 1];
    }

    for(int i = 0; i < SIZE; i++) {
        D_ResultArr[i] = ResultArr[SIZE * 2 - i];
    }

    for(int i = 0; i < SIZE; i++) {
        Result ->d_digit[i] = D_ResultArr[i];
    }
    for(int i = 0; i < SIZE + SIZE; i++) {
        Result ->i_digit[i] = I_ResultArr[i];
    }
    
}


//미래에 재도전!!!!
void Divide_BigNum(struct BigNum *BigNum, struct BigNum *BigNum2, struct ResultBigNum *Result) {
    
    Result -> sign = ((BigNum ->sign) + (BigNum2 -> sign)) % 2;
    int Arr1[SIZE + SIZE], Arr2[SIZE + SIZE] = {0};
    int ResultArr[(DoubleSIZE) * 2] = {0};
    int I_ResultArr[DoubleSIZE] = {0};
    int D_ResultArr[SIZE] = {0};
    
    //배열 복사(소숫점 없다고 가정)
    for(int i = 0; i < SIZE; i++) {
        Arr1[i] = BigNum ->d_digit[SIZE - 1 - i];
    }
    for(int i = SIZE; i < SIZE + SIZE; i++) {
        Arr1[i] = BigNum ->i_digit[i - SIZE];
    }


    for(int i = 0; i < SIZE; i++) {
        Arr2[i] = BigNum2 ->d_digit[SIZE - 1 - i];
    }
    for(int i = SIZE; i < SIZE + SIZE; i++) {
        Arr2[i] = BigNum2 ->i_digit[i - SIZE];
    }

    int Arr3[DoubleSIZE] = {0};

    int carry = 0;

    // .9999 보정
    if(ResultArr[0] == 9) {
        ResultArr[0]++;
        for(int i = 0; i < ((DoubleSIZE * 2) - 1); i++) {
            carry = ResultArr[i] / 10;
            ResultArr[i] %= 10;
            ResultArr[i + 1] += carry;
        }
    }

    for(int i = 0; i < DoubleSIZE; i++) {
        I_ResultArr[i] = ResultArr[i + SIZE * 2];
    }

    for(int i = 0; i < SIZE; i++) {
        D_ResultArr[i] = ResultArr[SIZE * 2 - i - 1];
    }


    for(int i = 0; i < SIZE; i++) {
        Result ->d_digit[i] = D_ResultArr[i];
    }
    for(int i = 0; i < SIZE + SIZE; i++) {
        Result ->i_digit[i] = I_ResultArr[i];
    }

}


// 테스트를 위한 출력 함수
void PrintBigNum(struct BigNum *pBigNum) {
    int D = SizeOf_d_BigNum(pBigNum);
    int N = SizeOf_i_BigNum(pBigNum);

    if(pBigNum -> sign) printf("-");

    for (int i = N - 1; i >= 0; i--) {
        printf("%d", pBigNum->i_digit[i]);
    }

    if(D > 0) {
        printf(".");
        for(int i = 0; i < D; i++) {
            printf("%d", pBigNum->d_digit[i]);
        }
    }
    printf("\n");
}

// ResultBigNum 출력함수
void PrintResultBigNum(struct ResultBigNum *pBigNum) {

    int D = SizeOf_d_ResultBigNum(pBigNum); // 소수
    int N = SizeOf_i_ResultBigNum(pBigNum); // 정수

    if(pBigNum -> sign) printf("-");

    for (int i = N - 1; i >= 0; i--) {
        printf("%d", pBigNum->i_digit[i]);
    }

    if(D > 0) {
        printf(".");
        for(int i = 0; i < D; i++) {
            printf("%d", pBigNum->d_digit[i]);
        }
    }

    printf("\n");
}

// BigNum의 정수부분 실제크기 추정
int SizeOf_i_BigNum(struct BigNum *pBigNum) {

    int i = 0;
    int SizeBigNum = 0;
    const int K = (sizeof((pBigNum->i_digit))) / 4;
    while(i != K) {

        if(pBigNum->i_digit[i] != 0) {
            SizeBigNum = i + 1;
        }

        i++;
    }

    return SizeBigNum;
}

// BigNum의 소수부분 실제크기 추정
int SizeOf_d_BigNum(struct BigNum *pBigNum) {

    int i = 0;
    int SizeBigNum = 0;
    const int K = (sizeof((pBigNum->d_digit))) / 4;
    while(i != K) {

        if((pBigNum->d_digit[i]) != 0) {
            SizeBigNum = i + 1;
        }

        i++;
    }

    return SizeBigNum;
}

// ResultBigNum의 정수부분 실제크기 추정
int SizeOf_i_ResultBigNum(struct ResultBigNum *pBigNum) {

    int i = 0;
    int SizeBigNum = 0;
    const int K = (sizeof((pBigNum->i_digit))) / 4;
    while(i != K) {

        if(pBigNum->i_digit[i] != 0) {
            SizeBigNum = i + 1;
        }

        i++;
    }

    return SizeBigNum;
}

// ResultBigNum의 소수부분 실제크기 추정
int SizeOf_d_ResultBigNum(struct ResultBigNum *pBigNum) {

    int i = 0;
    int SizeBigNum = 0;
    const int K = (sizeof((pBigNum->d_digit))) / 4;
    while(i != K) {

        if(pBigNum->d_digit[i] != 0) {
            SizeBigNum = i + 1;
        }

        i++;
    }

    return SizeBigNum;
}