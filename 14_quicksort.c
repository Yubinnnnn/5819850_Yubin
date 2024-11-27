#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_SIZE 100
#define ITERATIONS 20

// Function prototypes
void quickSort(int arr[], int low, int high, int* compCount, int* moveCount);
int partition(int arr[], int low, int high, int* compCount, int* moveCount);
void printArray(int arr[], int size);
void generateRandomArray(int arr[], int size, int range);

int main() {
    int i, arr[DATA_SIZE];
    int totalComparisons = 0, totalMoves = 0;

    srand((unsigned int)time(NULL)); // Seed random number generator

    // Perform 20 iterations
    for (i = 0; i < ITERATIONS; i++) {
        int compCount = 0, moveCount = 0;
        generateRandomArray(arr, DATA_SIZE, 1000);

        // Print the 40-60 position values for the first iteration
        if (i == 0) {
            printf("Original array (40th to 60th elements):\n");
            for (int j = 39; j < 60; j++) {
                printf("%d ", arr[j]);
            }
            printf("\n\nSorting process:\n");
        }

        // Perform quick sort
        quickSort(arr, 0, DATA_SIZE - 1, &compCount, &moveCount);

        // Accumulate comparison and move counts
        totalComparisons += compCount;
        totalMoves += moveCount;

        // Print sorted array for the first iteration
        if (i == 0) {
            printf("\nSorted array (40th to 60th elements):\n");
            for (int j = 39; j < 60; j++) {
                printf("%d ", arr[j]);
            }
            printf("\n");
        }
    }

    // Calculate and print averages
    printf("\nAverage comparisons: %.2f\n", totalComparisons / (double)ITERATIONS);
    printf("Average moves: %.2f\n", totalMoves / (double)ITERATIONS);

    return 0;
}

// Quick sort function
void quickSort(int arr[], int low, int high, int* compCount, int* moveCount) {
    if (low < high) {
        // Partition the array
        int pivotIndex = partition(arr, low, high, compCount, moveCount);

        // Print array during the first iteration
        static int printCount = 0;
        if (printCount++ < 1) {
            printf("Array during sorting (40th to 60th elements):\n");
            for (int j = 39; j < 60; j++) {
                printf("%d ", arr[j]);
            }
            printf("\n");
        }

        // Recursively sort subarrays
        quickSort(arr, low, pivotIndex - 1, compCount, moveCount);
        quickSort(arr, pivotIndex + 1, high, compCount, moveCount);
    }
}

// Partition function
int partition(int arr[], int low, int high, int* compCount, int* moveCount) {
    int pivot = arr[high];
    (*moveCount)++; // Moving pivot to temp
    int i = low - 1;

    for (int j = low; j < high; j++) {
        (*compCount)++;
        if (arr[j] <= pivot) {
            i++;
            // Swap elements
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            *moveCount += 3; // Swap involves 3 moves
        }
    }

    // Swap pivot into correct position
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    *moveCount += 3; // Swap involves 3 moves

    return i + 1;
}

// Print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Generate random array
void generateRandomArray(int arr[], int size, int range) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % range;
    }
}
