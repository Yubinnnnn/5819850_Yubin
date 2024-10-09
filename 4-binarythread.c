#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 이진 탐색 트리 노드 구조체
typedef struct TreeNode {
    int key;
    struct TreeNode* left, * right;
} TreeNode;

// 스레드 이진트리 노드 구조체
typedef struct ThreadNode {
    int key;
    struct ThreadNode* left, * right;
    bool isThreaded; // 오른쪽 자식이 스레드인지 여부
} ThreadNode;

// 이진 탐색 트리 노드 생성 함수
TreeNode* createTreeNode(int key) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 이진 탐색 트리 삽입 함수
TreeNode* insertTreeNode(TreeNode* root, int key) {
    if (root == NULL) return createTreeNode(key);

    if (key < root->key) {
        root->left = insertTreeNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = insertTreeNode(root->right, key);
    }
    return root;
}

// 이진 탐색 트리 중위 순회 함수 (재귀)
void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->key);
        BinaryTreeInOrder(root->right);
    }
}

// 스레드 이진트리 노드 생성 함수
ThreadNode* createThreadNode(int key) {
    ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->isThreaded = false;
    return newNode;
}

// 스레드 이진트리 삽입 함수
ThreadNode* insertThreadNode(ThreadNode* root, int key) {
    if (root == NULL) return createThreadNode(key);

    if (key < root->key) {
        root->left = insertThreadNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = insertThreadNode(root->right, key);
    }
    return root;
}

// 중위 순회를 위한 스레드 설정 함수
void createInOrderThread(ThreadNode* root, ThreadNode** prev) {
    if (root == NULL) return;

    // 왼쪽 서브트리 방문
    createInOrderThread(root->left, prev);

    // 이전 노드가 NULL이 아니면, 이전 노드의 오른쪽 자식을 현재 노드로 설정
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->isThreaded = true;
    }

    // 현재 노드를 이전 노드로 업데이트
    *prev = root;

    // 오른쪽 서브트리 방문
    createInOrderThread(root->right, prev);
}

// 스레드 이진트리 생성 함수
ThreadNode* GenerateThreadTree(int inputData[], int n) {
    ThreadNode* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insertThreadNode(root, inputData[i]);
    }
    // 스레드 설정
    ThreadNode* prev = NULL;
    createInOrderThread(root, &prev);
    return root;
}

// 스레드 이진트리 중위 순회 (스택 없이 반복 방식)
void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* curr = root;

    // 가장 왼쪽 노드로 이동
    while (curr->left != NULL) {
        curr = curr->left;
    }

    // 스레드 이진트리의 중위 순회
    while (curr != NULL) {
        printf("%d ", curr->key);

        // 스레드가 있으면 오른쪽으로 이동
        if (curr->isThreaded) {
            curr = curr->right;
        }
        else {
            // 스레드가 없으면 오른쪽 자식으로 이동하고 가장 왼쪽으로 계속 이동
            curr = curr->right;
            while (curr != NULL && curr->left != NULL) {
                curr = curr->left;
            }
        }
    }
}

int main() {
    // 주어진 입력 데이터
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int n = sizeof(inputData) / sizeof(inputData[0]);

    // 1. 이진 탐색 트리 생성
    TreeNode* binaryRoot = NULL;
    for (int i = 0; i < n; i++) {
        binaryRoot = insertTreeNode(binaryRoot, inputData[i]);
    }

    // 2. 이진 탐색 트리 중위 순회 출력
    printf("Inorder Traversal of Binary Search Tree: ");
    BinaryTreeInOrder(binaryRoot);
    printf("\n");

    // 3. 스레드 이진트리 생성
    ThreadNode* threadRoot = GenerateThreadTree(inputData, n);

    // 4. 스레드 이진트리 중위 순회 출력
    printf("Inorder Traversal of Threaded Binary Tree: ");
    ThreadTreeInOrder(threadRoot);
    printf("\n");

    return 0;
}
