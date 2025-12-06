//p450 Q2 
//동적으로 할당된 배열을 다시 바꾸는 작업

#include <stdio.h>
#include <stdlib.h>

void main () {
    
    int *p, *temp;
    int Input, i, add, Index, Value;

    printf("초기 배열을 설정하겠습니다. 크기는요?\n");
    scanf("%d", &i);
    
    p = (int *)malloc(sizeof(int) * i);
    
    while(Input != 3) {
        printf("어떻게 하시겠습니까?\n");
        printf("1. 배열 크기 추가, 2. 원소 입력, 3. 종료\n");
        scanf("%d", &Input);

        switch (Input)
        {
        case 1:
            printf("증가시킬 크기는요?\n");
            scanf("%d", &add);

            add = add + i;

            temp = (int *)malloc(sizeof(int) * add);
            for(int k = 0; k < i; k++) {
                temp[k] = p[k];
            }
            free(p);
            p = temp;

            break;
        
        case 2:

            Index = 0;
            printf("설정할 원소(인덱스)를 고르세요.\n");
            scanf("%d", &Index);
            p += Index;

            printf("설정할 원소의 값을 고르세요.\n");
            scanf("%d", &Value);
            *p = Value;
            p -= Index;

            Index = 0;
            break;

        default:
            break;
        }
    }

    free(p);

}