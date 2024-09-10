#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 배열 기반 트리 생성 및 출력
void GenerateArrayTree(int* tree) {
    // 트리 데이터를 배열로 정의 (1 ~ 15)
    int list[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

    // 배열 초기화
    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }

    // 배열 출력
    printf("Array Tree: ");
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[i]);
    }
    printf("\n");
}

// 전위 순회 (배열 트리)
void ArrayPreOrder(int* tree, int index, int size) {
    if (index >= size) return;
    printf("%d ", tree[index]);
    ArrayPreOrder(tree, 2 * index + 1, size); // left child
    ArrayPreOrder(tree, 2 * index + 2, size); // right child
}

// 중위 순회 (배열 트리)
void ArrayInOrder(int* tree, int index, int size) {
    if (index >= size) return;
    ArrayInOrder(tree, 2 * index + 1, size); // left child
    printf("%d ", tree[index]);
    ArrayInOrder(tree, 2 * index + 2, size); // right child
}

// 후위 순회 (배열 트리)
void ArrayPostOrder(int* tree, int index, int size) {
    if (index >= size) return;
    ArrayPostOrder(tree, 2 * index + 1, size); // left child
    ArrayPostOrder(tree, 2 * index + 2, size); // right child
    printf("%d ", tree[index]);
}

// 배열 트리 순회 실행
void ArrayOrders(int* tree, int size) {
    printf("Array PreOrder: ");
    ArrayPreOrder(tree, 0, size);
    printf("\n");

    printf("Array InOrder: ");
    ArrayInOrder(tree, 0, size);
    printf("\n");

    printf("Array PostOrder: ");
    ArrayPostOrder(tree, 0, size);
    printf("\n");
}

// 노드 생성 함수
TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 링크드 트리 생성
void PlaceNode(TreeNode* node, int direction, int data) {
    if (direction == 0) { // left
        node->left = CreateNode(data);
    }
    else { // right
        node->right = CreateNode(data);
    }
}

// 링크드 트리 생성 함수
TreeNode* GenerateLinkTree() {
    TreeNode* root = CreateNode(1);

    PlaceNode(root, 0, 2);       // root의 왼쪽에 2
    PlaceNode(root, 1, 3);       // root의 오른쪽에 3

    PlaceNode(root->left, 0, 4); // 2의 왼쪽에 4
    PlaceNode(root->left, 1, 5); // 2의 오른쪽에 5
    PlaceNode(root->right, 0, 6);// 3의 왼쪽에 6
    PlaceNode(root->right, 1, 7);// 3의 오른쪽에 7

    // 더 많은 노드를 추가할 수 있음

    return root;
}

// 전위 순회 (링크드 트리)
void LinkPreOrder(TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    LinkPreOrder(root->left);
    LinkPreOrder(root->right);
}

// 중위 순회 (링크드 트리)
void LinkInOrder(TreeNode* root) {
    if (root == NULL) return;
    LinkInOrder(root->left);
    printf("%d ", root->data);
    LinkInOrder(root->right);
}

// 후위 순회 (링크드 트리)
void LinkPostOrder(TreeNode* root) {
    if (root == NULL) return;
    LinkPostOrder(root->left);
    LinkPostOrder(root->right);
    printf("%d ", root->data);
}

// 링크드 트리 순회 실행
void LinkOrders(TreeNode* root) {
    printf("Link PreOrder: ");
    LinkPreOrder(root);
    printf("\n");

    printf("Link InOrder: ");
    LinkInOrder(root);
    printf("\n");

    printf("Link PostOrder: ");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    int array[15];
    TreeNode* root;

    // 배열 트리 생성
    GenerateArrayTree(array);
    
    // 배열 트리 순회
    ArrayOrders(array, 15);

    // 링크드 트리 생성
    root = GenerateLinkTree();

    // 링크드 트리 순회
    LinkOrders(root);

    return 0;
}
