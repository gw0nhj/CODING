//퀵정렬 복습

#include <stdio.h>

void Swap(int *a, int *b);
void QuickSort(int arr[], int s, int e);

int main() {

    int arr[10] = {3, 4, 2, 7, 7, 8, 1, 3, 9, 6};
    QuickSort(arr, 0, 9);

    for(int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }

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
            Swap(&arr[low], &Pivot);
            QuickSort(arr , 0, low - 1);
            QuickSort(arr , high, e);
            break;
        }

        if(arr[low] > Pivot && arr[high] < Pivot) {

            Swap(&arr[low], &arr[high]);

        }
    }

}