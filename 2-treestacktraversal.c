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
    newNode ->data = data;
    newNode ->left = NULL;
    newNode ->right = NULL;
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
    PlaceNode(root, 0, 2);     // root�� ���� �ڽ�
    PlaceNode(root, 1, 5);     // root�� ������ �ڽ�
    PlaceNode(root->left, 0, 3);  // 2�� ���� �ڽ�
    PlaceNode(root->left, 1, 6);  // 2�� ������ �ڽ�
    PlaceNode(root->right, 0, 7); // 5�� ���� �ڽ�
    PlaceNode(root->right, 1, 8); // 5�� ������ �ڽ�
    PlaceNode(root->left->left, 0, 4); // �߰� ���
}

// ���� push �Լ�
void push(Stack** stack, TreeNode* node) {
    Stack* newStackNode = (Stack*)malloc(sizeof(Stack));
    newStackNode->node = node;
    newStackNode->next = *stack;
    *stack = newStackNode;
    printf("push(%d)\n", node->data);
}

// ���� pop �Լ�
TreeNode* pop(Stack** stack) {
    if (*stack == NULL) return NULL;
    Stack* temp = *stack;
    *stack = (*stack)->next;
    TreeNode* poppedNode = temp->node;
    printf("pop(%d)\n", poppedNode->data);
    free(temp);
    return poppedNode;
}

// ������ ������� Ȯ��
int isEmpty(Stack* stack) {
    return stack == NULL;
}

// ���� ��ȸ (������ ����� �ݺ��� ���)
void InOrderIterative(TreeNode* root) {
    Stack* stack = NULL;
    TreeNode* current = root;

    while (!isEmpty(stack) || current != NULL) {
        // ���� ����� ���� ���� ���� ���ÿ� push
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        // ���ÿ��� pop�ϰ� �湮
        current = pop(&stack);
        printf("visit(%d)\n", current->data);

        // ���� ����� ������ ���� �̵�
        current = current->right;
    }
}

// ���� ��ȸ (������ ����� �ݺ��� ���)
void PreOrderIterative(TreeNode* root) {
    if (root == NULL) return;

    Stack* stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack)) {
        TreeNode* node = pop(&stack);
        printf("visit(%d)\n", node->data);

        // ������ �ڽ��� ���� push (������ ���Լ����̹Ƿ�)
        if (node->right != NULL) {
            push(&stack, node->right);
        }
        // ���� �ڽ��� ���߿� push
        if (node->left != NULL) {
            push(&stack, node->left);
        }
    }
}

// ���� ��ȸ (������ ����� �ݺ��� ���)
void PostOrderIterative(TreeNode* root) {
    if (root == NULL) return;

    Stack* stack1 = NULL;
    Stack* stack2 = NULL;
    push(&stack1, root);

    // ���� ��ȸ�� �� ���� ������ ���
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

    // ����2���� pop�ϸ鼭 �湮
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
