#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct Stack {
    TreeNode* node;
    struct Stack* next;
} Stack;

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void PlaceNode(TreeNode* parent, int direction, int data) {
    TreeNode* newNode = createNode(data);
    if (direction == 0) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);     // root의 왼쪽 자식
    PlaceNode(root, 1, 5);     // root의 오른쪽 자식
    PlaceNode(root->left, 0, 3);  // 2의 왼쪽 자식
    PlaceNode(root->left, 1, 6);  // 2의 오른쪽 자식
    PlaceNode(root->right, 0, 7); // 5의 왼쪽 자식
    PlaceNode(root->right, 1, 8); // 5의 오른쪽 자식
    PlaceNode(root->left->left, 0, 4); // 추가 노드
}

// 스택 push 함수
void push(Stack** stack, TreeNode* node) {
    Stack* newStackNode = (Stack*)malloc(sizeof(Stack));
    newStackNode->node = node;
    newStackNode->next = *stack;
    *stack = newStackNode;
    printf("push(%d)\n", node->data);
}

// 스택 pop 함수
TreeNode* pop(Stack** stack) {
    if (*stack == NULL) return NULL;
    Stack* temp = *stack;
    *stack = (*stack)->next;
    TreeNode* poppedNode = temp->node;
    printf("pop(%d)\n", poppedNode->data);
    free(temp);
    return poppedNode;
}

// 스택이 비었는지 확인
int isEmpty(Stack* stack) {
    return stack == NULL;
}

// 중위 순회 (스택을 사용한 반복적 방식)
void InOrderIterative(TreeNode* root) {
    Stack* stack = NULL;
    TreeNode* current = root;

    while (!isEmpty(stack) || current != NULL) {
        // 현재 노드의 왼쪽 노드들 먼저 스택에 push
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        // 스택에서 pop하고 방문
        current = pop(&stack);
        printf("visit(%d)\n", current->data);

        // 현재 노드의 오른쪽 노드로 이동
        current = current->right;
    }
}

// 전위 순회 (스택을 사용한 반복적 방식)
void PreOrderIterative(TreeNode* root) {
    if (root == NULL) return;

    Stack* stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack)) {
        TreeNode* node = pop(&stack);
        printf("visit(%d)\n", node->data);

        // 오른쪽 자식을 먼저 push (스택은 후입선출이므로)
        if (node->right != NULL) {
            push(&stack, node->right);
        }
        // 왼쪽 자식을 나중에 push
        if (node->left != NULL) {
            push(&stack, node->left);
        }
    }
}

// 후위 순회 (스택을 사용한 반복적 방식)
void PostOrderIterative(TreeNode* root) {
    if (root == NULL) return;

    Stack* stack1 = NULL;
    Stack* stack2 = NULL;
    push(&stack1, root);

    // 후위 순회는 두 개의 스택을 사용
    while (!isEmpty(stack1)) {
        TreeNode* node = pop(&stack1);
        push(&stack2, node);

        if (node->left != NULL) {
            push(&stack1, node->left);
        }
        if (node->right != NULL) {
            push(&stack1, node->right);
        }
    }

    // 스택2에서 pop하면서 방문
    while (!isEmpty(stack2)) {
        TreeNode* node = pop(&stack2);
        printf("visit(%d)\n", node->data);
    }
}

void LinkOrders(TreeNode* root) {
    printf("In-order Traversal (Iterative):\n");
    InOrderIterative(root);
    printf("\nPre-order Traversal (Iterative):\n");
    PreOrderIterative(root);
    printf("\nPost-order Traversal (Iterative):\n");
    PostOrderIterative(root);
}

int main() {
    TreeNode* root = createNode(1);
    GenerateLinkTree(root);
    LinkOrders(root);

    return 0;
}
