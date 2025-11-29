
#include <stdio.h>

#define ZERO 48

void Reverse(char arr1[1001]);
void DelZero(char arr1[1001]);

void Plus(char arr1[1001], char arr2[1001], char Output[2001]);
void Minus(char arr1[1001], char arr2[1001], char Output[2001]);
void Multiply(char arr1[1001], char arr2[1001], char Output[2001]);
void Divide(char arr1[1001], char arr2[1001], char Output[2001]);

void main() {
    
    char Input1[1001], Input2[1001];
    char Output[2001];
    scanf("%s", Input1); //Input1 뒤집힘

    Reverse(Input1);
    DelZero(Input1);

    scanf("%s", Input2); //Input2 뒤집힘

    Reverse(Input2);
    DelZero(Input2);

    Plus(Input1, Input2, Output);
    printf("%s", Output); 


}

void Reverse(char arr1[]) {

    int len = 0;
    while(arr1[len] != '\0') {
        len++;
    }

    for(int i = 0; i < len / 2; i++) {
        char temp = arr1[i];
        arr1[i] = arr1[len - 1 - i];
        arr1[len - 1 - i] = temp;
    }

}

/* void DelZero(char arr1[1001]) {
    char arr2[1001];
    int len = 0;
    while(arr1[len] == '0') {
        len++;
    }

    for(int i = 0; len + i < 1000; i++) {
        arr2[i] = arr1[len + i];
    }

    for(int i = 0; i < 1000 - len; i++) {
        arr1[i] = arr2[i];
    }

    for(int i = 1000 - len; i < 1000; i++) {
        arr1[i] = '\0';
    }

    arr1[1000] = '\0';
} */

void DelZero(char arr1[1001]) {
    // 1. 제거할 '0'의 개수 (앞쪽 '0'의 길이)를 셉니다.
    int len = 0;
    while(arr1[len] == '0' && arr1[len] != '\0') {
        len++;
    }

    // 2. 숫자가 '0'으로만 이루어진 경우 (예: "000")를 처리합니다.
    // '0'만 있을 때는 "0" 하나만 남겨야 합니다.
    if (arr1[len] == '\0' && len > 0) {
        if (len > 1) { // "00" 등을 입력한 경우
            arr1[0] = '0';
            arr1[1] = '\0';
        }
        return; // "0" 또는 이미 "0" 하나만 있는 경우 종료
    }
    
    // 3. '0'이 아닌 실제 숫자를 배열 앞으로 당깁니다. (arr2 사용 제거)
    int i;
    for(i = 0; arr1[len + i] != '\0'; i++) {
        arr1[i] = arr1[len + i];
    }
    
    // 4. 새로운 문자열의 끝에 널 문자('\0')를 추가합니다.
    arr1[i] = '\0';

    // (기존 코드의 나머지 부분은 모두 불필요하거나 잘못된 메모리 접근이므로 삭제)
}


void Plus(char arr1[1001], char arr2[1001], char Output[2001]) {
    // arr1과 arr2는 이미 Reverse 함수를 통해 뒤집혀서 (일의 자리부터) 저장되어 있습니다.
    // 예: "123" -> arr1[0]='3', arr1[1]='2', arr1[2]='1', arr1[3]='\0'

    int i = 0;
    int carry = 0; // 올림(Up)을 정수형으로 사용
    int sum = 0;
    int len1 = 0;
    int len2 = 0;

    // 문자열 길이 계산 (널 문자 직전까지)
    while (arr1[len1] != '\0') len1++;
    while (arr2[len2] != '\0') len2++;

    // Output 배열을 안전하게 초기화합니다.
    // 널 문자를 넣어 기존 내용을 지우거나, 덧셈 과정에서 덮어쓸 것입니다.
    Output[0] = '\0';

    // 두 문자열 중 긴 쪽의 길이만큼 반복합니다. (혹은 둘 다 끝날 때까지)
    // arr1[i]와 arr2[i]가 '\0'이 아니면 해당 문자를 숫자로 변환하고,
    // '\0'이면 0으로 간주합니다.
    while (i < len1 || i < len2 || carry) {
        
        // 1. 현재 자리의 숫자 변환
        // 문자가 숫자인지 확인하고, '\0'이면 0으로 처리합니다.
        int num1 = (i < len1) ? (arr1[i] - '0') : 0;
        int num2 = (i < len2) ? (arr2[i] - '0') : 0;

        // 2. 덧셈 수행
        sum = num1 + num2 + carry;
        
        // 3. 현재 자리의 값 계산 및 올림 처리
        carry = sum / 10;
        sum = sum % 10;
        
        // 4. 결과를 Output 배열에 문자로 저장
        // arr1과 arr2가 뒤집혀 있으므로, Output도 뒤집힌 순서로 저장됩니다.
        Output[i] = sum + '0';
        
        i++; // 다음 자리로 이동
    }

    // 5. Output 배열의 끝에 널 문자 추가
    Output[i] = '\0';
    
    // 6. 결과 문자열을 다시 뒤집어서 원래 순서로 복원
    // (이 과정은 main에서 하는 것이 더 일반적이지만, Plus 함수 내에서 처리합니다.)
    Reverse(Output);
    
    // DelZero는 Reverse 후에 호출되어야 하지만,
    // 이 구현에서는 덧셈 결과가 '0'으로만 시작할 가능성이 낮으므로 (배열이 이미 뒤집혔기 때문에)
    // 일단 Reverse만 수행하고 main에서 DelZero를 호출하는 것이 더 안전합니다.
    // 하지만 현재 main의 로직에 맞춰 Plus 함수가 최종 결과를 출력한다고 가정하고,
    // Plus 함수 내에서 Reverse를 호출했습니다.
    // 만약 `carry`가 남아 '1'이 추가되면, 뒤집혔을 때 가장 앞자리로 가게 되므로 DelZero가 필요 없습니다.
}

/* void Minus(char arr1[1001], char arr2[1001]) {

}
*/

/* void Minus(char arr1[1001], char arr2[1001]) {

}
*/