/* p502 Q2

a.txt 에 어떠한 긴 글이 들어 있는데, 이 글을 입력 받아서 특정한 문자열을 검색하는 프로그램을 만들어보세요 

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Function1(FILE *, char Keyword[]);
void Function2(FILE *, char Keyword[]);

void main() {
    FILE *fp = fopen("251207.txt", "r");
    char Keyword[] = "to";
    int i = 0;
    char c;
    // 코드 1
    // Function1(fp, Keyword);
    // 코드 2
    Function2(fp, Keyword);
}

void Function1(FILE *fp, char Keyword[]) {
    char c = 0;
    int i, j = 0;
    while((c = fgetc(fp)) != EOF) {
        
        j++;

        if(c == Keyword[i]) {
            i++;
            if(Keyword[i] == 0) {
                printf("%d번째 인덱스\n", j - i + 1);
                i = 0;
            }
        }
        else {
            i = 0;
        }


    }
    printf("끝!\n");
}

void Function2(FILE *fp, char Keyword[]) {
    int keyword_len = strlen(Keyword);
    char *str = (char *)malloc(sizeof(char) * (keyword_len + 1));
    
    if (str == NULL) {
        perror("메모리 할당 실패");
        return;
    }

    fseek(fp, 0, SEEK_SET);
    
    long position = 0;
    
    printf("--- (fgets 사용) 파일에서 \"%s\" 검색 시작 ---\n", Keyword);

    while (1) {
        // 현재 위치 저장
        long start_pos = ftell(fp);
        
        // 키워드 길이만큼만 읽기 (keyword_len + 1: \0 포함)
        if (fgets(str, keyword_len + 1, fp) == NULL) {
            break; // 파일 끝
        }
        
        int len_read = strlen(str);
        if (len_read > 0 && str[len_read - 1] == '\n') {
            str[len_read - 1] = '\0';
            len_read--;
        }

        // 키워드와 비교
        if (len_read == keyword_len && strcmp(str, Keyword) == 0) {
            printf("%ld번째 인덱스에서 발견\n", start_pos + 1);
        }
        
        // 핵심: 다음 검색을 위해 포인터를 1바이트만 전진
        fseek(fp, start_pos + 1, SEEK_SET);
    }

    free(str);
    printf("끝!\n");
}