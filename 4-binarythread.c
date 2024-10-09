#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ���� Ž�� Ʈ�� ��� ����ü
typedef struct TreeNode {
    int key;
    struct TreeNode* left, * right;
} TreeNode;

// ������ ����Ʈ�� ��� ����ü
typedef struct ThreadNode {
    int key;
    struct ThreadNode* left, * right;
    bool isThreaded; // ������ �ڽ��� ���������� ����
} ThreadNode;

// ���� Ž�� Ʈ�� ��� ���� �Լ�
TreeNode* createTreeNode(int key) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// ���� Ž�� Ʈ�� ���� �Լ�
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

// ���� Ž�� Ʈ�� ���� ��ȸ �Լ� (���)
void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->key);
        BinaryTreeInOrder(root->right);
    }
}

// ������ ����Ʈ�� ��� ���� �Լ�
ThreadNode* createThreadNode(int key) {
    ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->isThreaded = false;
    return newNode;
}

// ������ ����Ʈ�� ���� �Լ�
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

// ���� ��ȸ�� ���� ������ ���� �Լ�
void createInOrderThread(ThreadNode* root, ThreadNode** prev) {
    if (root == NULL) return;

    // ���� ����Ʈ�� �湮
    createInOrderThread(root->left, prev);

    // ���� ��尡 NULL�� �ƴϸ�, ���� ����� ������ �ڽ��� ���� ���� ����
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->isThreaded = true;
    }

    // ���� ��带 ���� ���� ������Ʈ
    *prev = root;

    // ������ ����Ʈ�� �湮
    createInOrderThread(root->right, prev);
}

// ������ ����Ʈ�� ���� �Լ�
ThreadNode* GenerateThreadTree(int inputData[], int n) {
    ThreadNode* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insertThreadNode(root, inputData[i]);
    }
    // ������ ����
    ThreadNode* prev = NULL;
    createInOrderThread(root, &prev);
    return root;
}

// ������ ����Ʈ�� ���� ��ȸ (���� ���� �ݺ� ���)
void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* curr = root;

    // ���� ���� ���� �̵�
    while (curr->left != NULL) {
        curr = curr->left;
    }

    // ������ ����Ʈ���� ���� ��ȸ
    while (curr != NULL) {
        printf("%d ", curr->key);

        // �����尡 ������ ���������� �̵�
        if (curr->isThreaded) {
            curr = curr->right;
        }
        else {
            // �����尡 ������ ������ �ڽ����� �̵��ϰ� ���� �������� ��� �̵�
            curr = curr->right;
            while (curr != NULL && curr->left != NULL) {
                curr = curr->left;
            }
        }
    }
}

int main() {
    // �־��� �Է� ������
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int n = sizeof(inputData) / sizeof(inputData[0]);

    // 1. ���� Ž�� Ʈ�� ����
    TreeNode* binaryRoot = NULL;
    for (int i = 0; i < n; i++) {
        binaryRoot = insertTreeNode(binaryRoot, inputData[i]);
    }

    // 2. ���� Ž�� Ʈ�� ���� ��ȸ ���
    printf("Inorder Traversal of Binary Search Tree: ");
    BinaryTreeInOrder(binaryRoot);
    printf("\n");

    // 3. ������ ����Ʈ�� ����
    ThreadNode* threadRoot = GenerateThreadTree(inputData, n);

    // 4. ������ ����Ʈ�� ���� ��ȸ ���
    printf("Inorder Traversal of Threaded Binary Tree: ");
    ThreadTreeInOrder(threadRoot);
    printf("\n");

    return 0;
}
