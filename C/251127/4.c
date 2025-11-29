//씹어먹는 C언어 255p Q1

#define Num 5
#include <stdio.h>


void Swap(float *a, float *b);
void QuickSort(float arr[], int s, int e);
void Print(float arr[], int Size);


void main() {

    int Score[Num][3];
    float AverageScore[Num];

    for(int i = 0; i < Num; i++) {
        printf("국, 수, 영 : ");
        scanf("%d, %d, %d", &Score[i][0], &Score[i][1], &Score[i][2]);

        printf("%d\n", Score[i][1]);
        
        AverageScore[i] = (Score[i][0] + Score[i][1] + Score[i][2]) / 3.0;
    }

    Print(AverageScore, Num);
    QuickSort(AverageScore, 0, 4);
    Print(AverageScore, Num);

    return;

}

void Swap(float *a, float *b) {
    float temp;

    temp = *a;
    *a= *b;
    *b = temp;
}


void QuickSort(float arr[], int s, int e) {
    
    if(s == e) {
        return;
    }

    if(s + 1 == e) {
        if(arr[s] > arr[e]) {
            Swap(&arr[s], &arr[e]);
        }
        return;
    }

    int low = s + 1;
    int high = e;

    float Pivot = arr[s];

    while(low < high) {

        if(arr[low] <= Pivot) {

            low++;

        }

        if(arr[high] >= Pivot) {

            high--;
        }

        if(low >= high) {

            Swap(&arr[low-1], &arr[s]);
            QuickSort(arr, 0, low-2);
            QuickSort(arr, low, e);

            break;

        }

        if(arr[low] > Pivot && arr[high] < Pivot) {

            Swap(&arr[low], &arr[high]);

        }
    }

}

void Print(float arr[], int Size) {

    for(int i = 0; i < Size; i++) {

        printf("%f ", arr[i]);

    }

    printf("\n");

    return;
}