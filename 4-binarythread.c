#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int key;
    struct TreeNode* left, * right;
} TreeNode;

typedef struct ThreadNode {
    int key;
    struct ThreadNode* left, * right;
    bool isThreaded;
} ThreadNode;

TreeNode* createTreeNode(int key) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

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

void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->key);
        BinaryTreeInOrder(root->right);
    }
}

ThreadNode* createThreadNode(int key) {
    ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->isThreaded = false;
    return newNode;
}

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

void createInOrderThread(ThreadNode* root, ThreadNode** prev) {
    if (root == NULL) return;

    createInOrderThread(root->left, prev);

    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->isThreaded = true;
    }

    *prev = root;

    createInOrderThread(root->right, prev);
}

ThreadNode* GenerateThreadTree(int inputData[], int n) {
    ThreadNode* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insertThreadNode(root, inputData[i]);
    }
    ThreadNode* prev = NULL;
    createInOrderThread(root, &prev);
    return root;
}

void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* curr = root;

    while (curr->left != NULL) {
        curr = curr->left;
    }

    while (curr != NULL) {
        printf("%d ", curr->key);

        if (curr->isThreaded) {
            curr = curr->right;
        }
        else {
            curr = curr->right;
            while (curr != NULL && curr->left != NULL) {
                curr = curr->left;
            }
        }
    }
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int n = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* binaryRoot = NULL;
    for (int i = 0; i < n; i++) {
        binaryRoot = insertTreeNode(binaryRoot, inputData[i]);
    }

    printf("Inorder Traversal of Binary Search Tree: ");
    BinaryTreeInOrder(binaryRoot);
    printf("\n");

    ThreadNode* threadRoot = GenerateThreadTree(inputData, n);

    printf("Inorder Traversal of Threaded Binary Tree: ");
    ThreadTreeInOrder(threadRoot);
    printf("\n");

    return 0;
}
