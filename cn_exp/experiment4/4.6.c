/*
PR4_6_DistanceVectorRouting.c:
Program to implement Distance Vector Routing using the Bellman-Ford Algorithm.
*/

#include <stdio.h>

#define MAX_ROUTERS 10
#define INF 999

typedef struct
{
    int cost[MAX_ROUTERS];
    int next_hop[MAX_ROUTERS];
} RoutingTable;

int main()
{
    int n; // Number of routers
    int cost[MAX_ROUTERS][MAX_ROUTERS];
    RoutingTable table[MAX_ROUTERS];

    printf("\nEnter number of routers (Max. %d): ", MAX_ROUTERS);
    scanf("%d", &n);

    printf("\n--- Enter cost matrix (use %d for infinity) ---\n", INF);
    for (int i = 0; i < n; i++)
    {
        printf("From Router %d (to router 0, 1, ... , and %d): ", i, n-1);
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
            cost[i][j] = (i == j) ? 0 : cost[i][j];
            table[i].cost[j] = cost[i][j];
            table[i].next_hop[j] = (cost[i][j] != INF && i != j) ? j : -1;
        }
    }

    // Bellman-Ford Algorithm: Update until convergence
    int updated;
    do
    {
        updated = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    if (table[i].cost[j] > cost[i][k] + table[k].cost[j])
                    {
                        table[i].cost[j] = cost[i][k] + table[k].cost[j];
                        table[i].next_hop[j] = k;
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);

    // Print final routing tables
    printf("\n--- Final Routing Tables ---\n");
    for (int i = 0; i < n; i++)
    {
        printf("\nRouter %d Routing Table:\n", i);
        printf("Destination    Cost    Next Hop\n");
        for (int j = 0; j < n; j++)
        {
            printf("%10d %8d %10d\n", j, table[i].cost[j],
                   (i == j) ? i : table[i].next_hop[j]);
        }
    }

    printf("\n");
    return 0;
}
