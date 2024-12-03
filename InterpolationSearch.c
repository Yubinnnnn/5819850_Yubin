#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000
#define MAX_NUMBER 9999

// 함수 선언
void generateRandomArray(int array[]);
void quickSort(int array[], int low, int high);
int binarySearch(int array[], int size, int target);
int interpolationSearch(int array[], int size, int target);
double getAverageBinarySearchCompareCount(int array[]);
double getAverageInterpolationSearchCompareCount(int array[]);
void printArray(int array[]);

// 퀵 정렬 함수
void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pivot = array[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
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

// 보간 탐색 함수
int interpolationSearch(int array[], int size, int target) {
    int low = 0;
    int high = size - 1;
    int comparisons = 0;

    while (low <= high && target >= array[low] && target <= array[high]) {
        comparisons++;
        if (low == high) {
            if (array[low] == target) {
                return comparisons;
            }
            return comparisons;
        }

        // 보간 공식
        int pos = low + ((double)(high - low) / (array[high] - array[low]) * (target - array[low]));

        if (array[pos] == target) {
            return comparisons;
        }
        else if (array[pos] < target) {
            low = pos + 1;
        }
        else {
            high = pos - 1;
        }
    }
    return comparisons;
}

// 평균 이진 탐색 비교 횟수 계산
double getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE];  // 배열에서 무작위로 target 선택
        totalComparisons += binarySearch(array, SIZE, target);
    }
    return (double)totalComparisons / 1000;
}

// 평균 보간 탐색 비교 횟수 계산
double getAverageInterpolationSearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE];  // 배열에서 무작위로 target 선택
        totalComparisons += interpolationSearch(array, SIZE, target);
    }
    return (double)totalComparisons / 1000;
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

// main 함수
int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);
    quickSort(array, 0, SIZE - 1);
    printArray(array);

    // 평균 비교 횟수를 3번 연속으로 출력
    for (int i = 0; i < 3; i++) {
        printf("Run %d:\n", i + 1);
        printf("Average Compare Count of Binary Search: %.2f\n",
            getAverageBinarySearchCompareCount(array));
        printf("Average Compare Count of Interpolation Search: %.2f\n",
            getAverageInterpolationSearchCompareCount(array));
    }

    return 0;
}
