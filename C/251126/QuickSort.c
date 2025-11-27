#include <stdio.h>

// 두 요소를 교환하는 헬퍼 함수
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// 분할(Partition) 함수: 피벗을 기준으로 배열을 나누고 피벗의 최종 위치를 반환
int partition(int arr[], int low, int high) {
    // 1. 피벗 선택: 가장 오른쪽 요소를 피벗으로 선택
    int pivot = arr[high]; 
    int i = (low - 1); // 피벗보다 작은 요소들의 끝 인덱스

    // 2. 분할 과정: 피벗보다 작은 요소를 왼쪽으로 보냅니다.
    for (int j = low; j <= high - 1; j++) {
        // 현재 요소(arr[j])가 피벗보다 작으면
        if (arr[j] < pivot) {
            i++; // 작은 요소 인덱스 증가
            swap(&arr[i], &arr[j]); // arr[i]와 arr[j]를 교환
        }
    }

    // 3. 피벗을 최종 위치(i+1)에 배치
    swap(&arr[i + 1], &arr[high]);
    return (i + 1); // 피벗의 최종 인덱스를 반환
}

// 퀵 정렬 함수 (제자리 정렬)
void QuickSort(int arr[], int low, int high) {
    // 1. 기본 조건: 정렬할 요소가 2개 이상일 때만 진행
    if (low < high) {
        // 2. 분할: 피벗의 최종 위치(pi)를 얻음
        int pi = partition(arr, low, high);

        // 3. 재귀 호출: 왼쪽 서브 배열 정렬 (low ~ pi-1)
        QuickSort(arr, low, pi - 1);

        // 4. 재귀 호출: 오른쪽 서브 배열 정렬 (pi+1 ~ high)
        QuickSort(arr, pi + 1, high);
    }
}

int main() {
    int N = 5;
    int score[N];

    for(int i = 0; i < N; i++) {
        printf("%d번째 학생의 점수 입력: ", i + 1);
        scanf("%d", &score[i]);
    }

    QuickSort(score, 0, N-1);

    printf("정렬된 점수: ");
    for(int i = 0; i < N; i++) {
        printf("%d ", score[N - 1 - i]);
    }
    printf("\n");
    
    return 0;
}