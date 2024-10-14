#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int heap[MAX_SIZE];
    int size;
} MaxHeap;

// 현재 힙 상태를 출력하는 함수 (삽입, 삭제 과정 중 필요할 때만 호출)
void printHeap(MaxHeap* heap) {
    for (int i = 1; i <= heap->size; i++) {
        printf("%d ", heap->heap[i]);
    }
    printf("\n");
}

// 최대 힙에 값 추가 (초기 힙 생성 중에는 상태를 출력하지 않음)
int insertMaxHeap(MaxHeap* heap, int value, int print) {
    int movement_count = 0;
    int i = ++heap->size;

    // 트리의 끝에 새로운 값을 삽입
    while (i != 1 && value > heap->heap[i / 2]) {
        heap->heap[i] = heap->heap[i / 2]; // 부모 노드로 값을 이동
        if (print) printHeap(heap);  // 초기 힙 생성 중이 아닌 경우에만 출력
        i /= 2;
        movement_count++;
    }
    heap->heap[i] = value;
    if (print) printHeap(heap);  // 초기 힙 생성 중이 아닌 경우에만 출력
    return movement_count;
}

// 최대 힙에서 루트 노드 삭제 (삭제 과정 출력)
int deleteMaxHeap(MaxHeap* heap) {
    int movement_count = 0;
    if (heap->size == 0) return 0;

    int last_value = heap->heap[heap->size--];
    int parent = 1;
    int child = 2;

    heap->heap[parent] = last_value;
    printHeap(heap);  // 루트에 마지막 노드를 이동한 후 출력

    // 루트부터 하향식으로 재정렬
    while (child <= heap->size) {
        if (child < heap->size && heap->heap[child] < heap->heap[child + 1]) {
            child++; // 더 큰 자식을 선택
        }
        if (last_value >= heap->heap[child]) {
            break;
        }
        heap->heap[parent] = heap->heap[child]; // 자식 노드로 값 이동
        printHeap(heap);  // 노드 이동 후 현재 상태 출력
        parent = child;
        child *= 2;
        movement_count++;
    }
    heap->heap[parent] = last_value;
    printHeap(heap);  // 마지막으로 재정렬 후 상태 출력

    return movement_count;
}

// 힙을 레벨별로 출력
void printHeapByLevel(MaxHeap* heap) {
    int level = 1;
    int index = 1;
    int level_end = 1;

    while (index <= heap->size) {
        printf("[%d] ", level);
        for (int i = index; i <= level_end && i <= heap->size; i++) {
            printf("%d ", heap->heap[i]);
        }
        printf("\n");
        index = level_end + 1;
        level_end = (level_end * 2) + 1;
        level++;
    }
}

// 사용자 인터페이스 실행
void runUserInterface(MaxHeap* heap) {
    char command;
    int value, count;
    int firstInput = 1;  // 첫 입력을 위한 플래그

    while (1) {
        // 첫 입력일 때만 상세한 메뉴 출력
        if (firstInput) {
            printf("i: 입력을 받아 최대 히프에 추가\n");
            printf("d: 최대 히프에서 루트노드 삭제\n");
            printf("p: 히프를 루트에서부터 레벨별로 출력\n");
            printf("c: 종료\n");
            firstInput = 0;  // 첫 입력 후 플래그를 변경
        }

        printf("메뉴 입력: ");  // 항상 메뉴 입력 프롬프트 출력

        scanf(" %c", &command);

        switch (command) {
        case 'i':
            printf("추가 입력값: ");
            scanf("%d", &value);
            count = insertMaxHeap(heap, value, 1);  // 삽입 시 상태를 출력
            printf("노드 이동 횟수: %d\n", count);
            break;

        case 'd':
            count = deleteMaxHeap(heap);
            printf("노드 이동 횟수: %d\n", count);
            break;

        case 'p':
            printf("트리 레벨별 출력\n");
            printHeapByLevel(heap);
            break;

        case 'c':
            printf("종료합니다.\n");
            return;

        default:
            printf("잘못된 입력입니다.\n");
            break;
        }
    }
}

int main() {
    MaxHeap heap;
    heap.size = 0;

    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 초기 힙 생성 (초기 생성 시에는 상태를 출력하지 않음)
    for (int i = 0; i < size; i++) {
        insertMaxHeap(&heap, inputData[i], 0);  // 상태 출력하지 않음
    }

    runUserInterface(&heap);

    return 0;
}
