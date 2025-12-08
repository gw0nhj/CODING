//파일 입출력 연습
#include <stdio.h>
FILE *fp;

void main() {
    fp = fopen("251207.txt", "w");
    
    if(fp == NULL) {
        printf("쓸 수가 없단 말이야!\n");
        return;
    }

    fputs("그래그래 이렇게 글을 쓰는거야 임마!\n", fp);
    
    fclose(fp);
    return;
}