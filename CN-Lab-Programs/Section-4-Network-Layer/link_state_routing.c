#include <stdio.h>
#include <stdbool.h>

#define MAX_ROUTERS 20
#define INFINITY_COST 9999

int find_min_distance(const int distance[], const bool visited[], int router_count) {
    int min_val = INFINITY_COST;
    int min_index = -1;

    for (int v = 0; v < router_count; v++) {
        if (!visited[v] && distance[v] <= min_val) {
            min_val = distance[v];
            min_index = v;
        }
    }
    return min_index;
}

void print_path(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%c", 'A' + j);
        return;
    }
    print_path(parent, parent[j]);
    printf(" -> %c", 'A' + j);
}

int get_first_hop(int parent[], int destination, int source) {
    if (destination == source) return source;
    int current = destination;
    while (parent[current] != -1 && parent[current] != source) {
        current = parent[current];
    }
    return current;
}

void run_dijkstra_for_router(int source, int router_count, int cost_matrix[MAX_ROUTERS][MAX_ROUTERS]) {
    int distance[MAX_ROUTERS];
    bool visited[MAX_ROUTERS];
    int parent[MAX_ROUTERS];

    for (int i = 0; i < router_count; i++) {
        distance[i] = INFINITY_COST;
        visited[i] = false;
        parent[i] = -1;
    }

    distance[source] = 0;

    for (int count = 0; count < router_count - 1; count++) {
        int u = find_min_distance(distance, visited, router_count);
        if (u == -1 || distance[u] == INFINITY_COST) break;

        visited[u] = true;

        for (int v = 0; v < router_count; v++) {
            if (!visited[v] && cost_matrix[u][v] != 0 && cost_matrix[u][v] != INFINITY_COST && distance[u] != INFINITY_COST) {
                if (distance[u] + cost_matrix[u][v] < distance[v]) {
                    distance[v] = distance[u] + cost_matrix[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    printf("--- Link-State Routing Table for Router %d (Node %c) ---\n", source + 1, 'A' + source);
    printf("%-16s %-15s %-12s %-25s\n", "Destination", "Next Hop", "Cost", "Shortest Path");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < router_count; i++) {
        if (distance[i] == INFINITY_COST) {
            printf("Router %2d (%c)    %-15s %-12s %-25s\n", i + 1, 'A' + i, "Unreachable", "INF", "None");
        } else if (i == source) {
            printf("Router %2d (%c)    %-15s %-12d %c\n", i + 1, 'A' + i, "Direct (Local)", 0, 'A' + source);
        } else {
            int first_hop = get_first_hop(parent, i, source);
            printf("Router %2d (%c)    Router %2d (%c)  %-12d ",
                   i + 1, 'A' + i, first_hop + 1, 'A' + first_hop, distance[i]);
            print_path(parent, i);
            printf("\n");
        }
    }
    printf("\n");
}

int main(void) {
    int router_count = 0;
    int cost_matrix[MAX_ROUTERS][MAX_ROUTERS];

    printf("============================================================\n");
    printf("        Link State Routing (Dijkstra's Algorithm)           \n");
    printf("============================================================\n");

    printf("Enter number of routers (2 to %d): ", MAX_ROUTERS);
    if (scanf("%d", &router_count) != 1 || router_count < 2 || router_count > MAX_ROUTERS) {
        printf("Error: Invalid number of routers.\n");
        return 1;
    }

    printf("Enter cost adjacency matrix (%d x %d, enter 0 for self, %d for no direct link):\n",
           router_count, router_count, INFINITY_COST);

    for (int i = 0; i < router_count; i++) {
        for (int j = 0; j < router_count; j++) {
            if (scanf("%d", &cost_matrix[i][j]) != 1) {
                printf("Error reading matrix element at [%d][%d].\n", i, j);
                return 1;
            }
            if (i == j) {
                cost_matrix[i][j] = 0;
            }
        }
    }

    printf("\nGenerating Link-State Routing Tables for all routers...\n\n");
    for (int i = 0; i < router_count; i++) {
        run_dijkstra_for_router(i, router_count, cost_matrix);
    }

    return 0;
}
