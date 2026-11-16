/*
PR4_7_LinkStateRouting.c:
Program to implement Link State Routing using Dijkstra's Algorithm graph parsing logic.
*/

#include <stdio.h>

#define INF 999

void dijkstra(int cost[20][20], int n, int startnode)
{
    int distance[20], pred[20];
    int visited[20], count, mindistance, nextnode;

    for (int i = 0; i < n; i++)
    {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }

    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;

    while (count < n - 1)
    {
        mindistance = INF;

        // Find the node with the minimum distance metric from unvisited pools
        for (int i = 0; i < n; i++)
        {
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }
        }

        visited[nextnode] = 1;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                if (mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
            }
        }
        count++;
    }

    // Output shortest topology configurations
    printf("\nShortest Link-State Path Mapping from Source Router %c:\n", 'A' + startnode);
    for (int i = 0; i < n; i++)
    {
        if (i != startnode)
        {
            printf("Router Destination %c: Minimum Metric Cost = %d (Path Tracer Sequence: %c", 'A' + i, distance[i], 'A' + i);
            int j = i;
            do
            {
                j = pred[j];
                printf(" <- %c", 'A' + j);
            } while (j != startnode);
            printf(")\n");
        }
    }
}

int main()
{
    int adj_cost[20][20], total_routers, source;

    printf("\n=== Link State Routing Simulator (Dijkstra) ===\n");
    printf("Enter structural count of network routers: ");
    scanf("%d", &total_routers);

    printf("Enter Routing Link Cost Adjacency Matrix (use 999 for Unreachable/Infinite nodes):\n");
    for (int i = 0; i < total_routers; i++)
    {
        for (int j = 0; j < total_routers; j++)
        {
            scanf("%d", &adj_cost[i][j]);
        }
    }

    printf("Select local Root Source Router index ID (0 for A, 1 for B, etc.): ");
    scanf("%d", &source);

    dijkstra(adj_cost, total_routers, source);
    printf("\n");

    return 0;
}
