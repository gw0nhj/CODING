//함수 포인터 개념 잡기
#include <stdio.h> 

void Function_0(int *A, int *B);
void Function_1(int*, int*);

void main() {

    int a = 1;
    int b = 996;

    Function_0(&a, &b);

    void (*Function_1)(int*, int*);
    Function_1 = Function_0;

    Function_1(&a, &b);

    return;

}

void Function_0(int *A, int *B) {
    
   if(*A > *B) {

        printf("%d(A) WIN!\n", *A);

   }
   else {

        printf("%d(B) WIN!\n", *B);
        
   }
    
}
