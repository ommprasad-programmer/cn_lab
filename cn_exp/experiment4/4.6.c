/*
PR4_6_DistanceVectorRouting.c:
Program to implement Distance Vector Routing using Bellman-Ford equation rules.
*/

#include <stdio.h>

struct node
{
    int dist[20];
    int from[20];
} routing_tables[20];

int main()
{
    int cost_matrix[20][20];
    int nodes_count;

    printf("\n=== Distance Vector Routing Simulator ===\n");
    printf("Enter total number of network routers/nodes: ");
    scanf("%d", &nodes_count);

    printf("Enter the cost adjacency matrix (use 999 for infinity):\n");
    for (int i = 0; i < nodes_count; i++)
    {
        for (int j = 0; j < nodes_count; j++)
        {
            scanf("%d", &cost_matrix[i][j]);
            cost_matrix[i][i] = 0;
            routing_tables[i].dist[j] = cost_matrix[i][j];
            routing_tables[i].from[j] = j;
        }
    }

    // Converge the routing data matrices using Bellman-Ford iterative evaluations
    int count = 0;
    do
    {
        count = 0;
        for (int i = 0; i < nodes_count; i++)
        {
            for (int j = 0; j < nodes_count; j++)
            {
                for (int k = 0; k < nodes_count; k++)
                {
                    if (routing_tables[i].dist[j] > cost_matrix[i][k] + routing_tables[k].dist[j])
                    {
                        routing_tables[i].dist[j] = cost_matrix[i][k] + routing_tables[k].dist[j];
                        routing_tables[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    } while (count != 0);

    // Display localized matrix solutions
    for (int i = 0; i < nodes_count; i++)
    {
        printf("\nTopology Routing Update Map for Router %c:\n", 'A' + i);
        printf("Destination\tShortest Distance\tNext Hop Route Node\n");
        for (int j = 0; j < nodes_count; j++)
        {
            printf("%c\t\t%d\t\t\t%c\n", 'A' + j, routing_tables[i].dist[j], 'A' + routing_tables[i].from[j]);
        }
    }
    printf("\n");
    return 0;
}
