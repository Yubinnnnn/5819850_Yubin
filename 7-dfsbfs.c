#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 11  // ��� �� (0 ~ 10)

// �׷��� ���� ����Ʈ
int graph[MAX][MAX] = {
    {0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},  // 0�� ��� ���� ����
    {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},  // 1�� ��� ���� ����
    {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},  // 2�� ��� ���� ����
    {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},  // 3�� ��� ���� ����
    {0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0},  // 4�� ��� ���� ����
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},  // 5�� ��� ���� ����
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0},  // 6�� ��� ���� ����
    {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1},  // 7�� ��� ���� ����
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},  // 8�� ��� ���� ����
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},  // 9�� ��� ���� ����
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}   // 10�� ��� ���� ����
};

// DFS (���� �켱 Ž��)
void dfs(int start, int target) {
    int stack[MAX];
    int top = -1;
    bool visited[MAX] = { false };
    int visit_count = 0;

    stack[++top] = start;
    printf("Ž�� ���: ");

    while (top != -1) {
        int node = stack[top--];

        if (!visited[node]) {
            visited[node] = true;
            visit_count++;
            printf("%d ", node);  // �湮�� ��� ���

            if (node == target) {
                printf("\nŽ�� ����: %d\n", target);
                printf("�湮�� ����� ��: %d\n", visit_count);
                return;
            }

            // ������ ������ ���ÿ� �߰� (�������� ����)
            for (int i = MAX - 1; i >= 0; i--) {
                if (graph[node][i] == 1 && !visited[i]) {
                    stack[++top] = i;
                }
            }
        }
    }

    printf("\nŽ�� ����: %d�� ã�� �� �����ϴ�.\n", target);
    printf("�湮�� ����� ��: %d\n", visit_count);
}

// BFS (�ʺ� �켱 Ž��)
void bfs(int start, int target) {
    int queue[MAX];
    int front = 0, rear = 0;
    bool visited[MAX] = { false };
    int visit_count = 0;

    queue[rear++] = start;
    printf("Ž�� ���: ");

    while (front != rear) {
        int node = queue[front++];

        if (!visited[node]) {
            visited[node] = true;
            visit_count++;
            printf("%d ", node);  // �湮�� ��� ���

            if (node == target) {
                printf("\nŽ�� ����: %d\n", target);
                printf("�湮�� ����� ��: %d\n", visit_count);
                return;
            }

            // ������ ������ ť�� �߰�
            for (int i = 0; i < MAX; i++) {
                if (graph[node][i] == 1 && !visited[i]) {
                    queue[rear++] = i;
                }
            }
        }
    }

    printf("\nŽ�� ����: %d�� ã�� �� �����ϴ�.\n", target);
    printf("�湮�� ����� ��: %d\n", visit_count);
}

// �޴� �Լ�
void menu() {
    int choice, start, target;

    while (1) {
        printf("\n1 : ���� �켱 Ž��\n");
        printf("2 : �ʺ� �켱 Ž��\n");
        printf("3 : ����\n");
        printf("�޴� �Է�: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf("%d %d", &start, &target);
            dfs(start, target);
        }
        else if (choice == 2) {
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf("%d %d", &start, &target);
            bfs(start, target);
        }
        else if (choice == 3) {
            printf("���α׷��� �����մϴ�.\n");
            break;
        }
        else {
            printf("�߸��� �����Դϴ�. �ٽ� �õ����ּ���.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
