#include <stdio.h>
#include <stdlib.h>

// 트리 노드 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef TreeNode* element; // 요소의 타입
typedef struct QueueNode { // 큐의 노드 타입
    element data;
    struct QueueNode* link;
} QueueNode;

typedef struct { // 큐 ADT 구현
    QueueNode* front, * rear;
} LinkedQueueType;

// 큐 초기화 함수
void init(LinkedQueueType* q) {
    q->front = q->rear = NULL;
}

// 큐가 비어 있는지 확인하는 함수
int is_empty(LinkedQueueType* q) {
    return (q->front == NULL);
}

// 큐에 요소 삽입
void enqueue(LinkedQueueType* q, element item) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->data = item;
    temp->link = NULL;
    if (is_empty(q)) {
        q->front = temp;
        q->rear = temp;
    }
    else {
        q->rear->link = temp;
        q->rear = temp;
    }
}

// 큐에서 요소 제거
element dequeue(LinkedQueueType* q) {
    if (is_empty(q)) {
        fprintf(stderr, "Queue is empty\n");
        exit(1);
    }
    else {
        QueueNode* temp = q->front;
        element item = temp->data;
        q->front = q->front->link;
        if (q->front == NULL)
            q->rear = NULL;
        free(temp);
        return item;
    }
}

// 트리 노드를 생성하는 함수
TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 트리 노드를 적절한 위치에 배치하는 함수
void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = CreateNode(data);
    if (direction == 0) {
        node->left = newNode;
    }
    else {
        node->right = newNode;
    }
}

// 트리를 생성하는 함수
void GenerateLinkTree(TreeNode* root) {
    // 루트 1의 자식: 2, 9
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);

    // 2의 자식: 3, 5
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);

    // 3의 자식: 4, 6
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);

    // 5의 자식: 7, 8
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);

    // 9의 자식: 10, 13
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);

    // 10의 자식: 11, 12
    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);

    // 13의 자식: 14, 15
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

// 노드의 합을 구하는 함수 (반복적 방법)
int GetSumOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    int sum = 0;
    LinkedQueueType queue;
    init(&queue);

    enqueue(&queue, root);
    while (!is_empty(&queue)) {
        TreeNode* node = dequeue(&queue);
        sum += node->data;

        if (node->left != NULL) {
            enqueue(&queue, node->left);
        }
        if (node->right != NULL) {
            enqueue(&queue, node->right);
        }
    }

    return sum;
}

// 트리의 노드 수를 구하는 함수 (반복적 방법)
int GetNumberOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    int count = 0;
    LinkedQueueType queue;
    init(&queue);

    enqueue(&queue, root);
    while (!is_empty(&queue)) {
        TreeNode* node = dequeue(&queue);
        count++;

        if (node->left != NULL) {
            enqueue(&queue, node->left);
        }
        if (node->right != NULL) {
            enqueue(&queue, node->right);
        }
    }

    return count;
}

// 트리의 높이를 구하는 함수 (반복적 방법)
int GetHeightOfTree(TreeNode* root) {
    if (root == NULL) return 0;

    int height = 0;
    LinkedQueueType queue;
    init(&queue);

    enqueue(&queue, root);
    while (!is_empty(&queue)) {
        int nodeCount = 0;
        for (QueueNode* temp = queue.front; temp != NULL; temp = temp->link) {
            nodeCount++;
        }

        height++;
        for (int i = 0; i < nodeCount; i++) {
            TreeNode* node = dequeue(&queue);
            if (node->left != NULL) {
                enqueue(&queue, node->left);
            }
            if (node->right != NULL) {
                enqueue(&queue, node->right);
            }
        }
    }

    return height;
}

// 단말 노드(리프 노드)의 수를 구하는 함수 (반복적 방법)
int GetNumberOfLeafNodes(TreeNode* root) {
    if (root == NULL) return 0;

    int leafCount = 0;
    LinkedQueueType queue;
    init(&queue);

    enqueue(&queue, root);
    while (!is_empty(&queue)) {
        TreeNode* node = dequeue(&queue);

        // 리프 노드인 경우
        if (node->left == NULL && node->right == NULL) {
            leafCount++;
        }

        if (node->left != NULL) {
            enqueue(&queue, node->left);
        }
        if (node->right != NULL) {
            enqueue(&queue, node->right);
        }
    }

    return leafCount;
}

int main() {
    TreeNode* root = CreateNode(1);
    GenerateLinkTree(root);

    printf("트리의 모든 노드의 합: %d\n", GetSumOfNodes(root));
    printf("트리의 전체 노드 개수: %d\n", GetNumberOfNodes(root));
    printf("트리의 높이: %d\n", GetHeightOfTree(root));
    printf("트리의 단말 노드 개수: %d\n", GetNumberOfLeafNodes(root));

    return 0;
}
