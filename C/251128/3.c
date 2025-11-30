//311 Q1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Rev(char arr[]);

void main() {

    char String[101];
    scanf("%s", String);
    Rev(String);

    printf("\n%s", String);
}

void Rev(char arr[]) {

    int len = strlen(arr);

    char temp;
    for(int i = 0; i < (len / 2); i++) {
        temp = arr[i];
        arr[i] = arr[len - 1 - i];
        arr[len - 1 - i] = temp;
    }
    
}