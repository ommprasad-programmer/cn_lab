/*
PR4_3_GenerateHostIPs.c:
Program to generate and output all usable Host IP configurations within a defined Subnet space.
*/

#include <stdio.h>

int main()
{
    int ip[4], prefix;
    int mask[4], net_addr[4], broad_addr[4];

    printf("\n=== Generation of All Usable Host IP Addresses ===\n");
    printf("Enter Network Base IP (separated by spaces, e.g., 192 168 1 0): ");
    scanf("%d %d %d %d", &ip[0], &ip[1], &ip[2], &ip[3]);

    printf("Enter Subnet CIDR Prefix (e.g., 28 to test shorter sample outputs safely): ");
    scanf("%d", &prefix);

    if (prefix < 0 || prefix > 32)
    {
        printf("Error: Invalid prefix length assignment rules.\n");
        return 1;
    }

    // Only generate address loops for subnet blocks sizing cleanly inside single page printouts
    if (prefix < 20)
    {
        printf("Warning: Prefix size generates too many entries (>4096 addresses) for screen simulation print cycles.\n");
        printf("Please use a higher prefix constraint value (like 24 through 31).\n");
        return 1;
    }

    // Convert CIDR prefix value into standard 4-octet layout
    unsigned long mask_32bit = (prefix == 0) ? 0 : (0xFFFFFFFF << (32 - prefix));
    mask[0] = (mask_32bit >> 24) & 0xFF;
    mask[1] = (mask_32bit >> 16) & 0xFF;
    mask[2] = (mask_32bit >> 8) & 0xFF;
    mask[3] = mask_32bit & 0xFF;

    for (int i = 0; i < 4; i++)
    {
        net_addr[i] = ip[i] & mask[i];
        broad_addr[i] = net_addr[i] | (~mask[i] & 0xFF);
    }

    printf("\nNetwork Scope Bounds identified as:\n");
    printf("Network ID Base Reference:  %d.%d.%d.%d\n", net_addr[0], net_addr[1], net_addr[2], net_addr[3]);
    printf("Subnet Broadcast Terminal: %d.%d.%d.%d\n", broad_addr[0], broad_addr[1], broad_addr[2], broad_addr[3]);
    printf("\n--- Generating List of Active Host IP Identifiers ---\n");

    int count = 0;
    // Sequential loops tracking changes smoothly inside four-octet bounds
    for (int o1 = net_addr[0]; o1 <= broad_addr[0]; o1++)
    {
        for (int o2 = net_addr[1]; o2 <= broad_addr[1]; o2++)
        {
            for (int o3 = net_addr[2]; o3 <= broad_addr[2]; o3++)
            {
                for (int o4 = net_addr[3]; o4 <= broad_addr[3]; o4++)
                {

                    // Filter rule skipping exact matches to the Network Address or Broadcast boundaries
                    if ((o1 == net_addr[0] && o2 == net_addr[1] && o3 == net_addr[2] && o4 == net_addr[3]) ||
                        (o1 == broad_addr[0] && o2 == broad_addr[1] && o3 == broad_addr[2] && o4 == broad_addr[3]))
                    {
                        continue;
                    }

                    count++;
                    printf("Host #%03d Address allocation: %d.%d.%d.%d\n", count, o1, o2, o3, o4);
                }
            }
        }
    }

    printf("\nOperation complete. Generated %d unique executable client targets.\n\n", count);
    return 0;
}
