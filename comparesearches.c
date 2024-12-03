#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define MAX_NUMBER 999

int compareCount = 0;

// 함수 선언
void generateRandomArray(int array[]);
double getAverageLinearSearchCompareCount(int array[]);
void getQuickSortCompareCount(int array[]);
double getAverageBinarySearchCompareCount(int array[]);
void printArray(int array[]);

// 순차 탐색 함수
int linearSearch(int array[], int size, int target) {
    int comparisons = 0;
    for (int i = 0; i < size; i++) {
        comparisons++;
        if (array[i] == target) {
            return comparisons;
        }
    }
    return comparisons;
}

// 퀵 정렬 함수
void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pivot = array[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            compareCount++;
            if (array[j] < pivot) {
                i++;
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        int temp = array[i + 1];
        array[i + 1] = array[high];
        array[high] = temp;
        quickSort(array, low, i);
        quickSort(array, i + 2, high);
    }
}

// 이진 탐색 함수
int binarySearch(int array[], int size, int target) {
    int low = 0;
    int high = size - 1;
    int comparisons = 0;

    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;
        if (array[mid] == target) {
            return comparisons;
        }
        else if (array[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return comparisons;
}

// 평균 순차 탐색 비교 횟수 계산
double getAverageLinearSearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = rand() % (MAX_NUMBER + 1);
        totalComparisons += linearSearch(array, SIZE, target);
    }
    return (double)totalComparisons / 100;
}

// 퀵 정렬 비교 횟수 계산
void getQuickSortCompareCount(int array[]) {
    compareCount = 0; // 비교 횟수 초기화
    quickSort(array, 0, SIZE - 1);
}

// 평균 이진 탐색 비교 횟수 계산
double getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = rand() % (MAX_NUMBER + 1);
        totalComparisons += binarySearch(array, SIZE, target);
    }
    return (double)totalComparisons / 100;
}

// 배열 생성 함수
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % (MAX_NUMBER + 1);
    }
}

// 배열 출력 함수
void printArray(int array[]) {
    printf("First 20 elements: ");
    for (int i = 0; i < 20; i++) {
        printf("%d ", array[i]);
    }
    printf("\nLast 20 elements: ");
    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 메인 함수
int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    // 3번 연속 수행
    for (int i = 0; i < 3; i++) {
        printf("Run #%d:\n", i + 1);
        generateRandomArray(array);

        // 평균 순차 탐색 비교 횟수 출력
        printf("Average Linear Search Compare Count: %.2f\n",
            getAverageLinearSearchCompareCount(array));

        // 퀵 정렬 비교 횟수 계산 및 출력
        getQuickSortCompareCount(array);
        printf("Quick Sort Compare Count: %d\n", compareCount);

        // 정렬된 배열로 이진 탐색 평균 비교 횟수 계산 및 출력
        printf("Average Binary Search Compare Count: %.2f\n\n",
            getAverageBinarySearchCompareCount(array));

        // 배열 출력
        printArray(array);
        printf("\n");
    }
    return 0;
}
