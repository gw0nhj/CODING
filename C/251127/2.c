//퀵정렬 복습

#include <stdio.h>

void Swap(int *a, int *b);
void QuickSort(int arr[], int s, int e);
void Print(int arr[], int Size);

int main() {

    int arr[15] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    QuickSort(arr, 0, 15);

    Print(arr, 15);

    return 0;

}

void Swap(int *a, int *b) {
    int temp;

    temp = *a;
    *a= *b;
    *b = temp;
}


void QuickSort(int arr[], int s, int e) {
    
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

    int Pivot = arr[s];

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

        if(arr[low] >= Pivot && arr[high] < Pivot) {

            Swap(&arr[low], &arr[high]);

        }


        printf("\n");

    }

}

void Print(int arr[], int Size) {

    for(int i = 0; i < Size; i++) {

        printf("%d ", arr[i]);

    }

    printf("\n");

    return;
}