#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char character;
    int frequency;
    struct Node* left;
    struct Node* right;
} Node;

// 새로운 노드를 생성하는 함수
Node* createNode(char character, int frequency) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 두 노드를 교환하는 함수
void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

// 최소 힙을 정렬하는 함수
void minHeapify(Node** heap, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left]->frequency < heap[smallest]->frequency)
        smallest = left;

    if (right < size && heap[right]->frequency < heap[smallest]->frequency)
        smallest = right;

    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

// 최소 빈도수를 가진 노드를 추출하는 함수
Node* extractMin(Node** heap, int* size) {
    Node* minNode = heap[0];
    heap[0] = heap[--(*size)];
    minHeapify(heap, *size, 0);
    return minNode;
}

// 최소 힙에 노드를 삽입하는 함수
void insertMinHeap(Node** heap, int* size, Node* node) {
    heap[(*size)++] = node;
    int i = *size - 1;

    while (i && heap[i]->frequency < heap[(i - 1) / 2]->frequency) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// 허프만 트리를 구축하는 함수
void buildHuffmanTree(Node** heap, int size) {
    while (size > 1) {
        Node* left = extractMin(heap, &size);
        Node* right = extractMin(heap, &size);
        Node* merged = createNode('\0', left->frequency + right->frequency);

        // 중간 과정 출력
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, merged->frequency);

        merged->left = left;
        merged->right = right;
        insertMinHeap(heap, &size, merged);
    }
}

// 허프만 코드를 생성하는 함수
void generateHuffmanCodes(Node* root, char* code, int depth, char codes[256][20], char characters[256], int* index) {
    if (root->left) {
        code[depth] = '0';  // 왼쪽 자식은 0
        generateHuffmanCodes(root->left, code, depth + 1, codes, characters, index);
    }

    if (root->right) {
        code[depth] = '1';  // 오른쪽 자식은 1
        generateHuffmanCodes(root->right, code, depth + 1, codes, characters, index);
    }

    if (!root->left && !root->right) {
        code[depth] = '\0';
        // 허프만 코드와 문자를 저장
        codes[*index][0] = root->character;
        strcpy(codes[*index] + 1, code);
        (*index)++;
    }
}

int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int n = sizeof(frequencies) / sizeof(frequencies[0]);

    Node** heap = (Node**)malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        heap[i] = createNode(characters[i], frequencies[i]);
    }

    // Min-Heap 구성
    for (int i = (n / 2) - 1; i >= 0; i--) {
        minHeapify(heap, n, i);
    }

    // 허프만 트리 생성
    buildHuffmanTree(heap, n);

    // 허프만 코드 생성 및 저장
    char code[100];
    char codes[256][20]; // 각 문자에 대한 코드 저장
    int index = 0;
    generateHuffmanCodes(heap[0], code, 0, codes, characters, &index);

    // 요구하는 출력 형식으로 정렬 및 출력
    for (int i = 0; i < index; i++) {
        if (codes[i][0] == 'i') {
            printf("i: %s\n", codes[i] + 1);
        }
    }
    for (int i = 0; i < index; i++) {
        if (codes[i][0] == 's') {
            printf("s: %s\n", codes[i] + 1);
        }
    }
    for (int i = 0; i < index; i++) {
        if (codes[i][0] == 'e') {
            printf("e: %s\n", codes[i] + 1);
        }
    }
    for (int i = 0; i < index; i++) {
        if (codes[i][0] == 'u') {
            printf("u: %s\n", codes[i] + 1);
        }
    }
    for (int i = 0; i < index; i++) {
        if (codes[i][0] == 't') {
            printf("t: %s\n", codes[i] + 1);
        }
    }
    for (int i = 0; i < index; i++) {
        if (codes[i][0] == 'o') {
            printf("o: %s\n", codes[i] + 1);
        }
    }
    for (int i = 0; i < index; i++) {
        if (codes[i][0] == 'a') {
            printf("a: %s\n", codes[i] + 1);
        }
    }

    // 메모리 해제
    free(heap);

    return 0;
}
