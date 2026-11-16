/*
PR2_2_ManchesterAndDifferentialManchesterEncoding.c:
Program to implement Polar Manchester and Differential Manchester line coding techniques.
*/

#include <stdio.h>
#include <stdlib.h>

// Function to implement Polar Manchester encoding
void polarManchester(int data[], int n)
{
    printf("\nPolar Manchester Encoding: ");
    for (int i = 0; i < n; i++)
    {
        if (data[i] == 0)
        {
            printf("| + to - "); // High to Low transition for 0
        }
        else if (data[i] == 1)
        {
            printf("| - to + "); // Low to High transition for 1
        }
        else
        {
            printf("Invalid data bit\n");
            return;
        }
    }
    printf("|\n");
}

// Function to implement Differential Manchester encoding
void differentialManchester(int data[], int n)
{
    printf("\nDifferential Manchester Encoding: ");
    int current_level = 1; // Assume initial level is high (can be 0 or 1)
    for (int i = 0; i < n; i++)
    {
        if (data[i] == 0)
        {
            // No transition at the beginning of the bit, transition in the middle
            if (current_level == 1)
            {
                printf("| + to - ");
                current_level = 0;
            }
            else
            {
                printf("| - to + ");
                current_level = 1;
            }
        }
        else if (data[i] == 1)
        {
            // Transition at the beginning of the bit, then transition in the middle
            if (current_level == 1)
            {
                printf("| - to + ");
                current_level = 0;
            }
            else
            {
                printf("| + to - ");
                current_level = 1;
            }
        }
        else
        {
            printf("Invalid data bit\n\n");
            return;
        }
    }
    printf("|\n\n");
}

int main()
{
    int n;
    printf("\nEnter the number of data bits: ");
    scanf("%d", &n);

    int *data = (int *)malloc(n * sizeof(int));
    if (data == NULL)
    {
        printf("\nMemory allocation failed.\n");
        return 1;
    }

    printf("\nEnter the data bits (0 or 1) separated by space: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &data[i]);
    }

    polarManchester(data, n);
    differentialManchester(data, n);

    free(data);
    return 0;
}
