#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 11  // 노드 수 (0 ~ 10)

// 그래프 인접 리스트
int graph[MAX][MAX] = {
    {0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},  // 0번 노드 연결 정보
    {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},  // 1번 노드 연결 정보
    {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},  // 2번 노드 연결 정보
    {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},  // 3번 노드 연결 정보
    {0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0},  // 4번 노드 연결 정보
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},  // 5번 노드 연결 정보
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0},  // 6번 노드 연결 정보
    {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1},  // 7번 노드 연결 정보
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},  // 8번 노드 연결 정보
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},  // 9번 노드 연결 정보
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}   // 10번 노드 연결 정보
};

// DFS (깊이 우선 탐색)
void dfs(int start, int target) {
    int stack[MAX];
    int top = -1;
    bool visited[MAX] = { false };
    int visit_count = 0;

    stack[++top] = start;
    printf("탐색 경로: ");

    while (top != -1) {
        int node = stack[top--];

        if (!visited[node]) {
            visited[node] = true;
            visit_count++;
            printf("%d ", node);  // 방문한 노드 출력

            if (node == target) {
                printf("\n탐색 성공: %d\n", target);
                printf("방문한 노드의 수: %d\n", visit_count);
                return;
            }

            // 인접한 노드들을 스택에 추가 (역순으로 넣음)
            for (int i = MAX - 1; i >= 0; i--) {
                if (graph[node][i] == 1 && !visited[i]) {
                    stack[++top] = i;
                }
            }
        }
    }

    printf("\n탐색 실패: %d을 찾을 수 없습니다.\n", target);
    printf("방문한 노드의 수: %d\n", visit_count);
}

// BFS (너비 우선 탐색)
void bfs(int start, int target) {
    int queue[MAX];
    int front = 0, rear = 0;
    bool visited[MAX] = { false };
    int visit_count = 0;

    queue[rear++] = start;
    printf("탐색 경로: ");

    while (front != rear) {
        int node = queue[front++];

        if (!visited[node]) {
            visited[node] = true;
            visit_count++;
            printf("%d ", node);  // 방문한 노드 출력

            if (node == target) {
                printf("\n탐색 성공: %d\n", target);
                printf("방문한 노드의 수: %d\n", visit_count);
                return;
            }

            // 인접한 노드들을 큐에 추가
            for (int i = 0; i < MAX; i++) {
                if (graph[node][i] == 1 && !visited[i]) {
                    queue[rear++] = i;
                }
            }
        }
    }

    printf("\n탐색 실패: %d을 찾을 수 없습니다.\n", target);
    printf("방문한 노드의 수: %d\n", visit_count);
}

// 메뉴 함수
void menu() {
    int choice, start, target;

    while (1) {
        printf("\n1 : 깊이 우선 탐색\n");
        printf("2 : 너비 우선 탐색\n");
        printf("3 : 종료\n");
        printf("메뉴 입력: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("시작 번호와 탐색할 값 입력: ");
            scanf("%d %d", &start, &target);
            dfs(start, target);
        }
        else if (choice == 2) {
            printf("시작 번호와 탐색할 값 입력: ");
            scanf("%d %d", &start, &target);
            bfs(start, target);
        }
        else if (choice == 3) {
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else {
            printf("잘못된 선택입니다. 다시 시도해주세요.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
