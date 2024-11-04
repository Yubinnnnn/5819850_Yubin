#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 10 // 그래프의 정점 수

// 최소 거리 노드를 찾는 함수
int minDistance(int dist[], bool found[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!found[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

// 다익스트라 알고리즘 함수
void dijkstra(int graph[V][V], int src) {
    int dist[V];       // 시작 노드로부터의 최소 거리
    bool found[V];     // 최단 경로에 포함된 노드 여부
    int found_order[V]; // 노드가 발견된 순서 저장

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        found[i] = false;
        found_order[i] = -1;
    }
    dist[src] = 0;

    int order_index = 0;

    // 각 노드에 대해 최단 경로 찾기
    for (int count = 0; count < V; count++) {
        int u = minDistance(dist, found);
        found[u] = true;
        found_order[order_index++] = u + 1;

        // 출력: Distance와 Found 배열 상태
        printf("Distance: ");
        for (int i = 0; i < V; i++) {
            if (dist[i] == INT_MAX) {
                printf("* ");
            }
            else {
                printf("%d ", dist[i]);
            }
        }
        printf("\nFound: ");
        for (int i = 0; i < V; i++) {
            printf("%d ", found[i] ? 1 : 0);
        }
        printf("\n\n");

        // u와 인접한 노드들의 거리 업데이트
        for (int v = 0; v < V; v++)
            if (!found[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // 발견 순서 출력
    printf("Found Order: ");
    for (int i = 0; i < V; i++) {
        if (found_order[i] != -1)
            printf("%d ", found_order[i]);
    }
    printf("\n");
}

int main() {
    // 예제 인접 행렬 (그래프 가중치)
    int graph[V][V] = {
        {0, 3, 0, 0, 0, 0, 0, 8, 0, 0},
        {3, 0, 1, 0, 0, 0, 0, 0, 5, 0},
        {0, 1, 0, 6, 0, 0, 0, 0, 2, 0},
        {0, 0, 6, 0, 7, 0, 0, 0, 0, 10},
        {0, 0, 0, 7, 0, 8, 0, 0, 0, 0},
        {0, 0, 0, 0, 8, 0, 9, 0, 0, 0},
        {0, 0, 0, 0, 0, 9, 0, 3, 4, 0},
        {8, 0, 0, 0, 0, 0, 3, 0, 0, 12},
        {0, 5, 2, 0, 0, 0, 4, 0, 0, 11},
        {0, 0, 0, 10, 0, 0, 0, 12, 11, 0}
    };

    int src = 0; // 시작 노드 (1번 노드로 설정)
    dijkstra(graph, src);

    return 0;
}
