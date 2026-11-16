/*
PR4_2_SubnetInformation.c:
Program to evaluate Subnet Bounds: Network Address, Broadcast Address, and Host Capacity.
*/

#include <stdio.h>

int main()
{
    int ip[4], mask[4];
    int net_addr[4], broad_addr[4];
    int prefix;

    printf("\n=== Determination of Subnet Information ===\n");
    printf("Enter Base IP Address (separated by spaces, e.g., 192 168 1 10): ");
    scanf("%d %d %d %d", &ip[0], &ip[1], &ip[2], &ip[3]);

    printf("Enter CIDR Subnet Mask Prefix Length (e.g., 24 for 255.255.255.0): ");
    scanf("%d", &prefix);

    if (prefix < 0 || prefix > 32)
    {
        printf("Error: Invalid prefix size allocation.\n");
        return 1;
    }

    // Convert CIDR prefix value into standard 4-octet subnet mask layout
    unsigned long mask_32bit = (prefix == 0) ? 0 : (0xFFFFFFFF << (32 - prefix));
    mask[0] = (mask_32bit >> 24) & 0xFF;
    mask[1] = (mask_32bit >> 16) & 0xFF;
    mask[2] = (mask_32bit >> 8) & 0xFF;
    mask[3] = mask_32bit & 0xFF;

    printf("\nComputed Subnet Mask: %d.%d.%d.%d\n", mask[0], mask[1], mask[2], mask[3]);

    // Bitwise operational calculation logic
    for (int i = 0; i < 4; i++)
    {
        net_addr[i] = ip[i] & mask[i];                   // Network ID address = IP AND Mask
        broad_addr[i] = net_addr[i] | (~mask[i] & 0xFF); // Broadcast Address = Network OR NOT Mask
    }

    printf("Network Address:   %d.%d.%d.%d\n", net_addr[0], net_addr[1], net_addr[2], net_addr[3]);
    printf("Broadcast Address: %d.%d.%d.%d\n", broad_addr[0], broad_addr[1], broad_addr[2], broad_addr[3]);

    // Host index evaluation count rules
    if (prefix >= 31)
    {
        printf("Total Usable Hosts: 0 (Point-to-Point links or loopback overrides)\n\n");
    }
    else
    {
        long total_hosts = 1 << (32 - prefix);
        long usable_hosts = total_hosts - 2; // Deduced subtraction of network and broadcast lines
        printf("Total Address Spaces in Subnet: %ld\n", total_hosts);
        printf("Total Usable Host Placements:   %ld\n\n", usable_hosts);
    }

    return 0;
}
