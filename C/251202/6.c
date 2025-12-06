#include <stdio.h>
#include <stdlib.h>


void main () {
    int i, Input;
    int X, Y;
    int **Arr;

    printf("arr[x][y] 형태의 배열을 만들 것.\n");
    scanf("%d %d", &X, &Y);

    Arr= (int **)malloc(sizeof(int *) * X);
    for(i = 0; i < X; i++) {
        Arr[i] = (int *)malloc(sizeof(int) * Y);
    }

    Arr++;
    **Arr = 3;
    Arr++;
    **Arr = 2;
    Arr++;
    **Arr = 1;

    Arr -= 2;
    printf("%d" , **Arr);

    for (i = 0; i < X; i++) {
        free(Arr[i]);
    }
    free(Arr);

}