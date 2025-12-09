/* p502 Q3

a.txt 에 문자열을 입력 받아서 b.txt 에 그 문자열을 역으로 출력하는 프로그램을 만들어보세요

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    FILE *fa = fopen("a.txt", "r");

    if (fa == NULL) {
        fprintf(stderr, "오류: 'a.txt' 파일을 열 수 없습니다. 파일이 존재하는지 확인하세요.\n");
        return 1;
    }
    FILE *fb = fopen("b.txt", "w");
    char c;

    size_t FILE_size = 0;
    while((c = getc(fa)) != EOF) {
        FILE_size++;
    }
    fseek(fa, 0, SEEK_SET);

    if (FILE_size == -1L || FILE_size == 0) {
        fprintf(stderr, "오류: 'a.txt' 파일이 비어 있거나 크기를 읽을 수 없습니다.\n");
        fclose(fa);
        return 1;
    }
    
    char *file = (char *)malloc(sizeof(char) * (FILE_size + 1));
    file[FILE_size] = 0;
    fseek(fa, 0, SEEK_SET);

    int i = 0;
    for(i = 0; i < FILE_size; i++) {
        file[i] = getc(fa);
    }

    i--;
    for(;i >= 0; i--) {
        putc(file[i], fb);
    }

    fclose(fa);
    fclose(fb);

    printf("완료!\n");
    return 0;
}
