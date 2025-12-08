// fopen 및 EOF 테스트

#include <stdio.h>
void main() {
    FILE *fp = fopen("251207.txt", "r");
    int size = 0;
    char c;

    while((c=fgetc(fp)) != EOF) {
        size++;
    }

    printf("%d", size);
}