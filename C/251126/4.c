#include <stdio.h>

void main() {
    int Rock[2] = {1, 2};
    int *SEX = &Rock[0];

    printf("1 : %d\n", *SEX);
    printf("2 : %d\n", *(SEX + 1));

    int OR[4][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    int(*P2) = OR[3];
    
    printf("%d\n", P2[1]);
    
}