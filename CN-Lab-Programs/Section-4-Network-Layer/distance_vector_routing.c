#include <stdio.h>
#include <stdbool.h>

#define MAX_ROUTERS 20
#define INFINITY_COST 9999

typedef struct {
    int distance[MAX_ROUTERS];
    int next_hop[MAX_ROUTERS];
} RoutingTable;

int main(void) {
    int router_count = 0;
    int cost_matrix[MAX_ROUTERS][MAX_ROUTERS];
    RoutingTable table[MAX_ROUTERS];

    printf("============================================================\n");
    printf("         Distance Vector Routing (Bellman-Ford Algorithm)   \n");
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
            table[i].distance[j] = cost_matrix[i][j];
            if (cost_matrix[i][j] != INFINITY_COST && i != j) {
                table[i].next_hop[j] = j;
            } else {
                table[i].next_hop[j] = i;
            }
        }
    }

    bool updated;
    int iteration = 0;

    do {
        updated = false;
        iteration++;

        for (int i = 0; i < router_count; i++) {
            for (int j = 0; j < router_count; j++) {
                for (int k = 0; k < router_count; k++) {
                    if (table[i].distance[k] != INFINITY_COST && table[k].distance[j] != INFINITY_COST) {
                        int candidate_dist = table[i].distance[k] + table[k].distance[j];
                        if (candidate_dist < table[i].distance[j]) {
                            table[i].distance[j] = candidate_dist;
                            table[i].next_hop[j] = table[i].next_hop[k];
                            updated = true;
                        }
                    }
                }
            }
        }
    } while (updated && iteration < router_count * 2);

    printf("\nDistance Vector Routing converged after %d iteration(s).\n\n", iteration);

    for (int i = 0; i < router_count; i++) {
        printf("--- Routing Table for Router %d (Node %c) ---\n", i + 1, 'A' + i);
        printf("%-18s %-15s %-12s\n", "Destination", "Next Hop", "Metric (Cost)");
        printf("---------------------------------------------\n");
        for (int j = 0; j < router_count; j++) {
            if (table[i].distance[j] == INFINITY_COST) {
                printf("Router %2d (%c)      %-15s %-12s\n", j + 1, 'A' + j, "None", "Infinity");
            } else if (i == j) {
                printf("Router %2d (%c)      %-15s %-12d\n", j + 1, 'A' + j, "Local", 0);
            } else {
                printf("Router %2d (%c)      Router %2d (%c)  %-12d\n",
                       j + 1, 'A' + j, table[i].next_hop[j] + 1, 'A' + table[i].next_hop[j], table[i].distance[j]);
            }
        }
        printf("\n");
    }

    return 0;
}
