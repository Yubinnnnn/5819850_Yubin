#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define RANGE 1000
#define ATTEMPTS 20

// 배열 출력 함수
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 선택 정렬 함수
void selectionSort(int arr[], int size) {
    int step = 10, nextPrint = step;
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }

        // 단계별 출력 (10~20단위 및 마지막 단계)
        if (i + 1 == nextPrint || i + 1 == size - 1) {
            printf("선택 정렬 %d 단계: ", i + 1);
            printArray(arr, size);
            nextPrint += step;
            if (step == 10) step = 20;
        }
    }
}

// 삽입 정렬 함수 및 비교 횟수 계산
int insertionSort(int arr[], int size) {
    int comparisons = 0;
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            comparisons++;
        }
        arr[j + 1] = key;
        comparisons++;
    }
    return comparisons;
}

// 버블 정렬 함수 및 이동 횟수 계산
int bubbleSort(int arr[], int size) {
    int movements = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                movements += 3;  // swap 시 각 이동을 3회로 계산
            }
        }
    }
    return movements;
}

int main() {
    int arr[SIZE], tempArr[SIZE];
    srand(time(NULL));

    // 선택 정렬 수행 및 출력
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % RANGE;
    }
    printf("선택 정렬 시작 배열: ");
    printArray(arr, SIZE);
    selectionSort(arr, SIZE);
    printf("선택 정렬 결과: ");
    printArray(arr, SIZE);

    // 삽입 정렬 수행 및 평균 비교 횟수 계산
    int totalComparisons = 0;
    for (int i = 0; i < ATTEMPTS; i++) {
        for (int j = 0; j < SIZE; j++) {
            tempArr[j] = rand() % RANGE;
        }
        totalComparisons += insertionSort(tempArr, SIZE);
    }
    printf("\n삽입 정렬 평균 비교 횟수: %d\n", totalComparisons / ATTEMPTS);
    printf("삽입 정렬 결과: ");
    printArray(tempArr, SIZE);

    // 버블 정렬 수행 및 평균 이동 횟수 계산
    int totalMovements = 0;
    for (int i = 0; i < ATTEMPTS; i++) {
        for (int j = 0; j < SIZE; j++) {
            tempArr[j] = rand() % RANGE;
        }
        totalMovements += bubbleSort(tempArr, SIZE);
    }
    printf("\n버블 정렬 평균 이동 횟수: %d\n", totalMovements / ATTEMPTS);
    printf("버블 정렬 결과: ");
    printArray(tempArr, SIZE);

    return 0;
}
