/* p502 Q3

a.txt 에 문자열을 입력 받아서 b.txt 에 그 문자열을 역으로 출력하는 프로그램을 만들어보세요

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 문자열을 역순으로 만드는 함수
void reverse_string(char* str) {
    if (str == NULL) return;

    size_t len = strlen(str);
    char *start = str;
    char *end = str + len - 1;
    char temp;

    // 문자열의 시작과 끝을 교환하며 안쪽으로 이동
    while (end > start) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main() {
    FILE *fa, *fb;
    char *buffer = NULL; // a.txt 내용을 저장할 버퍼
    long file_size = 0;

    // 1. a.txt 파일을 읽기 모드로 열기
    fa = fopen("251207.txt", "r");
    if (fa == NULL) {
        fprintf(stderr, "오류: 'a.txt' 파일을 열 수 없습니다. 파일이 존재하는지 확인하세요.\n");
        return 1;
    }

    // 2. 파일 크기 확인 및 3. 문자열 읽기를 위한 준비
    // 파일 포인터를 파일의 끝으로 이동
    fseek(fa, 0, SEEK_END);
    file_size = ftell(fa); // 현재 위치 (파일 크기)를 얻음
    
    if (file_size == -1L || file_size == 0) {
        fprintf(stderr, "오류: 'a.txt' 파일이 비어 있거나 크기를 읽을 수 없습니다.\n");
        fclose(fa);
        return 1;
    }
    
    // 파일 포인터를 다시 파일의 처음으로 이동
    rewind(fa);

    // 파일 크기 + 널 종료 문자(\0)를 위한 메모리 할당
    buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "오류: 메모리 할당에 실패했습니다.\n");
        fclose(fa);
        return 1;
    }

    // 3. a.txt의 전체 내용을 버퍼로 읽어 들임
    size_t read_count = fread(buffer, 1, file_size, fa);
    if (read_count != (size_t)file_size) {
        fprintf(stderr, "경고: 파일 내용을 모두 읽지 못했습니다.\n");
    }
    buffer[file_size] = '\0'; // 문자열로 처리하기 위해 널 종료 문자 추가

    // 4. 읽어 들인 문자열을 역순으로 변환
    reverse_string(buffer);

    // 5. b.txt 파일을 쓰기 모드로 열기
    fb = fopen("b.txt", "w");
    if (fb == NULL) {
        fprintf(stderr, "오류: 'b.txt' 파일을 생성하거나 열 수 없습니다.\n");
        free(buffer);
        fclose(fa);
        return 1;
    }

    // 5. 역순 문자열을 b.txt에 출력
    fwrite(buffer, 1, file_size, fb);

    // 6. 자원 해제
    printf("성공적으로 'a.txt'의 내용을 역순으로 만들어 'b.txt'에 저장했습니다.\n");
    
    free(buffer);
    fclose(fa);
    fclose(fb);

    return 0;
}