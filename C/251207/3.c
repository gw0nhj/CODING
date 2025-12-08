/* 

502p Q1
사용자로 부터 경로를 입력 받아서 그 곳에 파일을 생성하고 a 를 입력해놓는 프로그램을 만들어보세요

*/

#include <stdio.h>

void main() {
    char Input[130], address[150];
    scanf("%s", Input);

    int i = 0;
    while(Input[i] != 0) {
        address[i] = Input[i];
        i++;
    }
    if(Input[0] != 0) {
        address[i++] = '\\';
        address[i++] = 'f';
        address[i++] = 'i';
        address[i++] = 'l';
        address[i++] = 'e';
        address[i++] = '.';
        address[i++] = 't';
        address[i++] = 'x';
        address[i++] = 't';
    }

    printf("%s", address);
    FILE *fp = fopen(address, "w");
    fputs("이거 설마 되는건가?", fp);
    fclose(fp);
    return;
}