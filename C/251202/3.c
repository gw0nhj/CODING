#include "2.c"

int Compare(char *str1, char *str2);

void main () {
    char Arr1[20] = "He's alive";
    char Arr2[20] = "He's alive";
    char Arr3[20] = "He's dead";

    printf("%d\n", Compare(Arr1, Arr2));
    printf("%d", Compare(Arr3, Arr2));
}
