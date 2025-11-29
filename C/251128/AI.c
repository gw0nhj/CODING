#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 최대 자릿수와 배열 크기 정의
#define MAX_DIGITS 1000 
#define SIZE_INPUT (MAX_DIGITS + 2)  // 입력 수 (1000자리 + 널 문자 + 예비)
#define SIZE_OUTPUT (MAX_DIGITS * 2 + 2) // 곱셈 결과 최대 2000자리 + 널 문자 + 예비

// 함수 프로토타입
void Reverse(char arr[]);
void Normalize(char arr[]);
int Compare(const char a[], const char b[]);

void Add(const char arr1[], const char arr2[], char output[]);
void Subtract(const char arr1[], const char arr2[], char output[]);
void SubtractInternal(char a[], const char b[], char result[]); 
void Multiply(const char arr1[], const char arr2[], char output[]);
void Divide(const char arr1[], const char arr2[], char output[]);

// ************************************************************
// 보조 함수 구현
// ************************************************************

/**
 * @brief 문자열을 제자리(in-place)에서 뒤집습니다.
 * Big Integer 연산을 위해 1의 자리를 인덱스 0에 배치하는 데 사용됩니다.
 * @param arr 뒤집을 문자열 배열
 */
void Reverse(char arr[]) {
    int len = strlen(arr);
    for (int i = 0; i < len / 2; i++) {
        char temp = arr[i];
        arr[i] = arr[len - 1 - i];
        arr[len - 1 - i] = temp;
    }
}

/**
 * @brief 결과 문자열의 앞에 붙은 불필요한 '0'을 제거하고,
 * 숫자 하나만 남았을 경우 "0"을 유지합니다. (비-뒤집힌 상태 기준)
 * @param arr 정리할 문자열 배열
 */
void Normalize(char arr[]) {
    int len = strlen(arr);
    if (len == 0) {
        arr[0] = '0';
        arr[1] = '\0';
        return;
    }

    int i = 0;
    // 맨 앞의 '0'의 개수를 셉니다.
    while (i < len - 1 && arr[i] == '0') {
        i++;
    }

    // i > 0 이면 '0'을 제거해야 합니다.
    if (i > 0) {
        // 남은 문자열을 앞으로 당깁니다.
        int j = 0;
        while (arr[i + j] != '\0') {
            arr[j] = arr[i + j];
            j++;
        }
        arr[j] = '\0';
    }
}

/**
 * @brief 두 큰 수(비-뒤집힌 문자열)를 비교합니다.
 * @param a 첫 번째 숫자 문자열
 * @param b 두 번째 숫자 문자열
 * @return a > b 이면 1, a < b 이면 -1, a == b 이면 0
 */
int Compare(const char a[], const char b[]) {
    int lenA = strlen(a);
    int lenB = strlen(b);

    if (lenA > lenB) return 1;
    if (lenA < lenB) return -1;

    // 길이가 같으면 사전 순 비교
    return strcmp(a, b);
}

// ************************************************************
// 산술 연산 함수 구현
// ************************************************************

/**
 * @brief 두 큰 수의 덧셈을 수행합니다. (arr1 + arr2)
 * 입력과 출력 모두 뒤집힌 상태로 처리합니다.
 */
void Add(const char arr1[], const char arr2[], char output[]) {
    int len1 = strlen(arr1);
    int len2 = strlen(arr2);
    int maxLen = (len1 > len2) ? len1 : len2;
    int carry = 0;
    int i = 0;

    for (i = 0; i < maxLen || carry; i++) {
        // 현재 자릿수의 값 (문자가 없으면 0)
        int digit1 = (i < len1) ? arr1[i] - '0' : 0;
        int digit2 = (i < len2) ? arr2[i] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        
        output[i] = (sum % 10) + '0';
        carry = sum / 10;
    }
    output[i] = '\0'; // 결과 문자열 마감
}

/**
 * @brief a에서 b를 뺍니다. (a >= b 가정, 뒤집힌 문자열)
 * 결과는 result에 저장됩니다. (result는 a와 크기가 같아야 함)
 */
void SubtractInternal(char a[], const char b[], char result[]) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    int borrow = 0;
    int i = 0;

    for (i = 0; i < lenA; i++) {
        int digitA = a[i] - '0';
        int digitB = (i < lenB) ? b[i] - '0' : 0;

        int diff = digitA - digitB - borrow;
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i] = diff + '0';
    }
    result[i] = '\0';
}

/**
 * @brief 두 큰 수의 뺄셈을 수행합니다. (arr1 - arr2)
 * 부호를 처리하며, 출력은 비-뒤집힌 상태입니다.
 */
void Subtract(const char arr1[], const char arr2[], char output[]) {
    char tempA[SIZE_INPUT], tempB[SIZE_INPUT];
    char result[SIZE_INPUT];
    
    // 비-뒤집힌 상태로 비교
    strcpy(tempA, arr1); Reverse(tempA);
    strcpy(tempB, arr2); Reverse(tempB);
    
    int comparison = Compare(tempA, tempB);

    // 1. 결과가 0인 경우
    if (comparison == 0) {
        output[0] = '0';
        output[1] = '\0';
        return;
    }

    // 2. arr1 >= arr2 인 경우 (양수)
    if (comparison > 0) {
        SubtractInternal((char*)arr1, arr2, result);
        Reverse(result); // 결과를 다시 뒤집어 일반적인 순서로 만듭니다.
        strcpy(output, result);
        Normalize(output); // 앞의 '0' 제거
        return;
    }

    // 3. arr1 < arr2 인 경우 (음수)
    // 부호를 위해 '-'를 붙인 후, arr2 - arr1을 계산합니다.
    SubtractInternal((char*)arr2, arr1, result); // arr2 - arr1
    
    // 결과 뒤집기, 부호 추가
    Reverse(result);
    output[0] = '-';
    strcpy(output + 1, result);
    Normalize(output + 1);
}

/**
 * @brief 두 큰 수의 곱셈을 수행합니다. (arr1 * arr2)
 * 입력은 뒤집힌 상태이며, 출력은 비-뒤집힌 상태입니다.
 */
void Multiply(const char arr1[], const char arr2[], char output[]) {
    int len1 = strlen(arr1);
    int len2 = strlen(arr2);
    int resultLen = len1 + len2;

    // 결과 배열을 '0'으로 초기화
    int *res = (int*)calloc(resultLen, sizeof(int));
    if (res == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        return;
    }

    // 1. 각 자릿수를 곱하고 합산합니다.
    for (int i = 0; i < len1; i++) {
        int digit1 = arr1[i] - '0';
        int carry = 0;
        for (int j = 0; j < len2; j++) {
            int digit2 = arr2[j] - '0';
            
            int product = digit1 * digit2 + res[i + j] + carry;
            
            res[i + j] = product % 10;
            carry = product / 10;
        }
        res[i + len2] += carry;
    }

    // 2. 결과 배열을 문자열로 변환합니다. (뒤집힌 상태)
    int i = resultLen - 1;
    while (i > 0 && res[i] == 0) { // 맨 앞 '0' 제거
        i--;
    }
    
    int k = 0;
    while (i >= 0) {
        output[k++] = res[i] + '0';
        i--;
    }
    output[k] = '\0';
    
    free(res); // 메모리 해제
    
    Normalize(output); // 출력 문자열 정리
}

/**
 * @brief 두 큰 수의 나눗셈을 수행합니다. (arr1 / arr2, 정수 몫)
 * 나눗셈은 비-뒤집힌 문자열로 처리하는 것이 직관적이므로 내부적으로 Reverse를 해제합니다.
 */
void Divide(const char arr1[], const char arr2[], char output[]) {
    char dividend[SIZE_INPUT];
    char divisor[SIZE_INPUT];

    // 입력 인수가 뒤집힌 상태이므로 다시 되돌립니다.
    strcpy(dividend, arr1); Reverse(dividend);
    strcpy(divisor, arr2); Reverse(divisor);

    // 1. 예외 처리: 0으로 나누는 경우
    if (strcmp(divisor, "0") == 0) {
        strcpy(output, "Divide By Zero Error");
        return;
    }

    // 2. 예외 처리: 피제수 < 제수인 경우
    if (Compare(dividend, divisor) < 0) {
        output[0] = '0';
        output[1] = '\0';
        return;
    }

    int lenDvd = strlen(dividend);
    int lenDvs = strlen(divisor);
    
    // 부분 피제수와 몫을 저장할 배열
    char partialDividend[SIZE_INPUT] = {0};
    char quotient[SIZE_INPUT] = {0};
    int q_idx = 0;

    // 3. 나눗셈의 첫 번째 부분 피제수 설정
    strncpy(partialDividend, dividend, lenDvs);
    partialDividend[lenDvs] = '\0';
    
    // 4. 나머지 자릿수에 대해 반복
    for (int i = lenDvs; i <= lenDvd; i++) {
        // 현재 부분 피제수를 비-뒤집힌 상태로 가져옵니다.
        // 현재 partialDividend는 비-뒤집힌 상태입니다.

        int k = 0; // 몫의 자릿수
        
        // **문제 발생 지점 1: 루프 내부에서 변수 선언**
        char temp_divisor_rev[SIZE_INPUT]; // 제수(divisor)의 뒤집힌 버전을 저장
        
        // 제수(divisor)를 k번 곱하여 partialDividend보다 작은 최대 k를 찾습니다.
        while (1) {
            char tempQuotient[SIZE_OUTPUT] = {0}; // k * divisor 결과 저장 (곱셈 결과는 길 수 있음)
            
            // k+1 * divisor 를 계산 (뒤집힌 상태에서 곱셈 수행)
            // 곱셈 함수는 뒤집힌 입력을 받기 때문에 divisor를 뒤집어야 합니다.
            
            // k+1 * divisor가 partialDividend보다 크다면 루프 종료
            if (k + 1 > 9) break; // 10 이상은 불가능

            // 현재 k+1을 문자로 만들고 뒤집습니다.
            char k_str_rev[2] = {k + 1 + '0', '\0'};
            Reverse(k_str_rev); 
            
            strcpy(temp_divisor_rev, divisor); Reverse(temp_divisor_rev); // divisor를 뒤집음

            Multiply(k_str_rev, temp_divisor_rev, tempQuotient); // k+1 * divisor (비-뒤집힌)
            Normalize(tempQuotient); // 결과 정규화

            if (Compare(tempQuotient, partialDividend) > 0) {
                break;
            }
            k++;
        }

        quotient[q_idx++] = k + '0'; // 몫에 자릿수 추가

        // 부분 피제수 갱신: partialDividend - k * divisor
        if (k > 0) {
            char k_str_rev[2] = {k + '0', '\0'};
            Reverse(k_str_rev); 
            
            char k_dvs[SIZE_OUTPUT];
            char pDvs_rev[SIZE_INPUT];
            char k_dvs_rev[SIZE_OUTPUT]; // **문제 발생 지점 2: k_dvs_rev 선언**
            
            // k * divisor 계산
            strcpy(temp_divisor_rev, divisor); Reverse(temp_divisor_rev); // divisor를 뒤집음
            Multiply(k_str_rev, temp_divisor_rev, k_dvs); // k * divisor (비-뒤집힌)
            Normalize(k_dvs);

            // 부분 피제수 - (k * divisor) 계산 (뒤집힌 상태로 변환 필요)
            strcpy(pDvs_rev, partialDividend); Reverse(pDvs_rev);
            strcpy(k_dvs_rev, k_dvs); Reverse(k_dvs_rev);
            
            // 결과는 pDvs_rev에 저장됨
            SubtractInternal(pDvs_rev, k_dvs_rev, pDvs_rev); 
            Reverse(pDvs_rev); // 다시 비-뒤집힌 상태로
            strcpy(partialDividend, pDvs_rev);
            Normalize(partialDividend); // 갱신된 partialDividend 정규화
        }

        // 다음 자릿수 가져오기
        if (i < lenDvd) {
            int currentLen = strlen(partialDividend);
            // 부분 피제수가 '0'으로만 이루어진 경우 (예: 0을 입력)
            // '0'을 제거하고 다음 자릿수를 추가해야 합니다.
            if (currentLen == 1 && partialDividend[0] == '0') {
                partialDividend[0] = dividend[i];
                partialDividend[1] = '\0';
            } else {
                partialDividend[currentLen] = dividend[i];
                partialDividend[currentLen + 1] = '\0';
            }
            // Normalize(partialDividend); // 이미 위의 if/else에서 처리됨
        }
    }
    
    quotient[q_idx] = '\0';
    Normalize(quotient); // 최종 몫 정규화 (앞의 '0' 제거)
    strcpy(output, quotient);
}

// ************************************************************
// 메인 함수
// ************************************************************

void main() {
    // 입력을 비-뒤집힌 문자열로 받습니다.
    char input1_str[SIZE_INPUT], input2_str[SIZE_INPUT];
    char input1_rev[SIZE_INPUT], input2_rev[SIZE_INPUT];
    char output[SIZE_OUTPUT] = {0};
    char op;

    printf("**************************************************\n");
    printf("        C언어 Big Integer Calculator (1000자리)\n");
    printf("**************************************************\n");
    printf("첫 번째 큰 수를 입력하세요 (최대 %d자리): ", MAX_DIGITS);
    if (scanf("%1000s", input1_str) != 1) return;

    printf("두 번째 큰 수를 입력하세요 (최대 %d자리): ", MAX_DIGITS);
    if (scanf("%1000s", input2_str) != 1) return;

    printf("연산자를 입력하세요 (+, -, *, /): ");
    // 버퍼에 남아있는 개행 문자 제거 후 연산자 입력
    while (getchar() != '\n'); 
    if (scanf("%c", &op) != 1) return;

    // 연산을 위해 문자열을 복사하고 뒤집습니다. (1의 자리가 인덱스 0)
    strcpy(input1_rev, input1_str); Reverse(input1_rev);
    strcpy(input2_rev, input2_str); Reverse(input2_rev);

    printf("\n--- 계산 결과 ---\n");
    printf("%s %c %s = ", input1_str, op, input2_str);

    switch (op) {
        case '+':
            Add(input1_rev, input2_rev, output);
            // 덧셈 결과는 뒤집힌 상태이므로 다시 뒤집어 출력합니다.
            Reverse(output);
            Normalize(output);
            printf("%s\n", output);
            break;
        case '-':
            // 뺄셈 함수는 내부적으로 부호 및 뒤집기를 처리하고 비-뒤집힌 상태로 결과를 반환합니다.
            Subtract(input1_rev, input2_rev, output);
            printf("%s\n", output);
            break;
        case '*':
            // 곱셈 함수는 내부적으로 비-뒤집힌 상태로 결과를 반환합니다.
            Multiply(input1_rev, input2_rev, output);
            printf("%s\n", output);
            break;
        case '/':
            // 나눗셈 함수는 내부적으로 비-뒤집힌 상태로 결과를 반환합니다.
            Divide(input1_rev, input2_rev, output);
            printf("%s\n", output);
            break;
        default:
            printf("잘못된 연산자입니다.\n");
            break;
    }
    printf("-----------------\n");
}