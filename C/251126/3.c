#include <stdio.h>

void QuickSort(int arr[], int Left, int Right) {
    
    // 1. 기본 조건 수정: Left가 Right보다 크거나 같으면 종료 (ArrSize가 0 또는 1)
    if (Left >= Right) {
        // 정렬할 요소가 0개 또는 1개인 경우 재귀 종료
        return; 
    }
    
    int Pivot = arr[Left];
    
    // ArrSize는 피벗을 포함한 요소의 총 개수입니다.
    int ArrSize = Right - Left + 1;
    
    // VLA (Variable Length Array) 사용
    int Before[ArrSize]; 
    int After[ArrSize]; 
    int l = 0; // Before 배열에 채워진 요소 개수
    int r = 0;
    
    for(int i = Left + 1; i <= Right; i++) { 
        
        if(arr[i] >= Pivot) {
            Before[l++] = arr[i]; // i는 arr의 유효한 인덱스입니다.
        }
        else {
            After[r++] = arr[i]; // i는 arr의 유효한 인덱스입니다.
        }
    }

    // 3. 재귀 호출 (Recursive Calls)
    // l과 r이 0일 때를 대비하여 명시적 처리와 끝 인덱스 전달
    if (l > 0) {
        QuickSort(Before, 0, l - 1);
    }
    if (r > 0) {
        QuickSort(After, 0, r - 1); 
    }

    // 4. 병합 (Merging)
    int current = Left; // 원본 배열에 다시 채워넣을 시작 인덱스를 여기서 정의

    // Before 배열 복사
    for(int j = 0; j < l; j++) {
        arr[current++] = Before[j];
    }
        
    // 피벗 배치
    arr[current++] = Pivot;

    // After 배열 복사
    for(int j = 0; j < r; j++) {
        arr[current++] = After[j];
    }
}

int main() {
    int N = 15;
    int score[N];

    for(int i = 0; i < N; i++) {
        printf("%d번째 학생의 점수 입력: ", i + 1);
        scanf("%d", &score[i]);
    }

    QuickSort(score, 0, N-1);

    printf("정렬된 점수: ");
    for(int i = 0; i < N; i++) {
        printf("%d ", score[i]);
    }
    printf("\n");
    
    return 0;
}