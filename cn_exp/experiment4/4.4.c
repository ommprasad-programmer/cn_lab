/*
PR4_4_VLSM.c:
Program to implement Variable Length Subnet Masking (VLSM).
*/

#include <stdio.h>
#include <math.h>

void sortRequirements(int req[], int n)
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (req[i] < req[j])
            {
                temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }
        }
    }
}

int main()
{
    int base_ip[4], num_subnets;
    int requirements[20];

    printf("\n=== Variable Length Subnet Masking (VLSM) ===\n");
    printf("Enter starting Network Base IP (separated by spaces, e.g., 192 168 1 0): ");
    scanf("%d %d %d %d", &base_ip[0], &base_ip[1], &base_ip[2], &base_ip[3]);

    printf("Enter the number of subnets needed: ");
    scanf("%d", &num_subnets);

    for (int i = 0; i < num_subnets; i++)
    {
        printf("Enter host requirement for Subnet %d: ", i + 1);
        scanf("%d", &requirements[i]);
    }

    // Sort descending (largest host requirement first)
    sortRequirements(requirements, num_subnets);

    printf("\nAllocated VLSM Subnets (assuming continuous block processing):\n");
    printf("------------------------------------------------------------------------\n");
    printf("Subnet\tReq\tAllocated Hosts\tNetwork IP\tSubnet Mask\n");
    printf("------------------------------------------------------------------------\n");

    int current_last_octet = base_ip[3];

    for (int i = 0; i < num_subnets; i++)
    {
        // Calculate bits needed for host portion (including +2 for Network/Broadcast IDs)
        int hosts_needed = requirements[i] + 2;
        int host_bits = (int)ceil(log2(hosts_needed));
        int allocated_size = 1 << host_bits;
        int prefix = 32 - host_bits;

        printf("Sub %d\t%d\t%d\t\t%d.%d.%d.%d/%d\t", i + 1, requirements[i], allocated_size - 2, base_ip[0], base_ip[1], base_ip[2], current_last_octet, prefix);

        // Advance the base for the next subnet slice assignment
        current_last_octet += allocated_size;

        if (current_last_octet > 256)
        {
            printf("\nError: Size exceeded Class C boundary capacity.\n");
            break;
        }
        printf("Active block boundary updated.\n");
    }
    printf("------------------------------------------------------------------------\n\n");

    return 0;
}
