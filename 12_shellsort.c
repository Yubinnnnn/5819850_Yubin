#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100  // 배열 크기

// 랜덤 숫자 생성 함수
void generateRandomNumbers(int arr[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 1000;  // 0~999 사이의 랜덤 숫자
    }
}

// 쉘 정렬 함수
void doShellSort(int arr[], int gapFactor, int* comparisonCount, int* moveCount) {
    int tempArray[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        tempArray[i] = arr[i];
    }

    int gap;
    *comparisonCount = 0;
    *moveCount = 0;

    printf("Shell Sort (n/%d):\n", gapFactor);

    if (gapFactor == 2) {  // n/2 방식
        for (gap = ARRAY_SIZE / 2; gap > 0; gap /= 2) {
            printf("Sorting with gap = %d:\n", gap);
            for (int i = gap; i < ARRAY_SIZE; i++) {
                int temp = tempArray[i];
                (*moveCount)++;  // temp에 값을 넣음
                int j;
                for (j = i; j >= gap && tempArray[j - gap] > temp; j -= gap) {
                    tempArray[j] = tempArray[j - gap];
                    (*comparisonCount)++;
                    (*moveCount)++;  // 값을 이동
                }
                tempArray[j] = temp;
                (*moveCount)++;  // temp 값 삽입
            }

            // 현재 상태 출력
            for (int i = 0; i < 20; i++) {
                printf("%d ", tempArray[i]);
            }
            printf("...\n");
        }
    }
    else if (gapFactor == 3) {  // n/3 방식
        for (gap = ARRAY_SIZE / 3; gap > 0; gap /= 3) {
            printf("Sorting with gap = %d:\n", gap);
            for (int i = gap; i < ARRAY_SIZE; i++) {
                int temp = tempArray[i];
                (*moveCount)++;  // temp에 값을 넣음
                int j;
                for (j = i; j >= gap && tempArray[j - gap] > temp; j -= gap) {
                    tempArray[j] = tempArray[j - gap];
                    (*comparisonCount)++;
                    (*moveCount)++;  // 값을 이동
                }
                tempArray[j] = temp;
                (*moveCount)++;  // temp 값 삽입
            }

            // 현재 상태 출력
            for (int i = 0; i < 20; i++) {
                printf("%d ", tempArray[i]);
            }
            printf("...\n");
        }
    }

    printf("Sorted shellArray (gap = %d):\n", gapFactor);
    for (int i = 0; i < 20; i++) {
        printf("%d ", tempArray[i]);
    }
    printf("...\n");
}

int main() {
    srand(time(0));  // 랜덤 시드 초기화

    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    // 랜덤 배열 생성
    generateRandomNumbers(array);

    // 쉘 정렬 (n/2)
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // 쉘 정렬 (n/3)
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    return 0;
}
