/*
PR4_7_LinkStateRouting.c:
Program to implement Link State Routing using the Dijkstra Algorithm.
*/

#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF 999

int cost[MAX][MAX], dist[MAX], visited[MAX], prev[MAX];
int n;

void dijkstra(int src)
{
    for (int i = 0; i < n; i++)
    {
        dist[i] = cost[src][i];
        visited[i] = 0;
        prev[i] = (cost[src][i] != INF && i != src) ? src : -1;
    }

    dist[src] = 0;
    visited[src] = 1;

    for (int count = 1; count < n; count++)
    {
        int min = INF, u = -1;

        for (int i = 0; i < n; i++)
            if (!visited[i] && dist[i] < min)
            {
                min = dist[i];
                u = i;
            }

        if (u == -1) break;  // No more reachable nodes

        visited[u] = 1;

        for (int v = 0; v < n; v++)
        {
            if (!visited[v] && cost[u][v] != INF && dist[u] + cost[u][v] < dist[v])
            {
                dist[v] = dist[u] + cost[u][v];
                prev[v] = u;
            }
        }
    }
}

void print_path(int dest)
{
    if (prev[dest] == -1)
    {
        printf("%d", dest);
        return;
    }
    print_path(prev[dest]);
    printf(" -> %d", dest);
}

int main()
{
    int src;

    printf("\nEnter number of routers: ");
    scanf("%d", &n);

    printf("\n--- Enter cost matrix (use %d for infinity) ---\n", INF);
    for (int i = 0; i < n; i++)
    {
        printf("From Router %d (to router 0, 1, ... , and %d): ", i, n-1);
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
            if (i == j) cost[i][j] = 0;
        }
    }

    printf("\nEnter source router (0 to %d): ", n - 1);
    scanf("%d", &src);

    dijkstra(src);

    printf("\nShortest paths from router %d:\n", src);
    for (int i = 0; i < n; i++)
    {
        if (i == src) continue;

        printf("To %d: Cost = %d, Path = ", i, dist[i]);
        if (dist[i] == INF)
        {
            printf("No path\n");
        }
        else
        {
            print_path(i);
            printf("\n");
        }
    }

    printf("\n");
    return 0;
}
