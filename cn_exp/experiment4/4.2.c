/*
PR4_2_SubnetInfo.c:
Program that takes an IPv4 address and subnet mask as input and calculates the following:
(1) Network Address
(2) Broadcast Address
(3) First Usable Host
(4) Last Usable Host
(5) Number of Usable Hosts.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

// Function to count number of 1s in subnet mask
int count_ones(unsigned int mask)
{
    int count = 0;
    while (mask)
    {
        count += (mask & 1);
        mask >>= 1;
    }
    return count;
}

// Convert integer IP to dotted-decimal
void int_to_ip(unsigned int ip, char *buffer)
{
    struct in_addr addr;
    addr.s_addr = htonl(ip);
    strcpy(buffer, inet_ntoa(addr));
}

int main()
{
    char ip_str[20], mask_str[20];
    unsigned int ip, mask;

    printf("\nEnter IP address (e.g., 192.168.1.10): ");
    scanf("%19s", ip_str);

    printf("Enter Subnet Mask (e.g., 255.255.255.0): ");
    scanf("%19s", mask_str);

    if (inet_pton(AF_INET, ip_str, &ip) != 1 || inet_pton(AF_INET, mask_str, &mask) != 1)
    {
        printf("\nInvalid IP address or subnet mask.\n\n");
        return 1;
    }

    ip = ntohl(ip);     // Convert to host byte order
    mask = ntohl(mask); // Convert to host byte order

    unsigned int network = ip & mask;
    unsigned int broadcast = network | (~mask);
    unsigned int first_host = (network == broadcast) ? network : network + 1;
    unsigned int last_host = (network == broadcast) ? network : broadcast - 1;

    int ones = count_ones(mask);
    int usable_hosts = (ones < 31) ? ((1 << (32 - ones)) - 2) : 0;

    char net_str[INET_ADDRSTRLEN], bcast_str[INET_ADDRSTRLEN];
    char first_str[INET_ADDRSTRLEN], last_str[INET_ADDRSTRLEN];

    int_to_ip(network, net_str);
    int_to_ip(broadcast, bcast_str);
    int_to_ip(first_host, first_str);
    int_to_ip(last_host, last_str);

    printf("\n--- Subnet Info ---\n");
    printf("Network Address      : %s\n", net_str);
    printf("Broadcast Address    : %s\n", bcast_str);
    printf("First Usable Host    : %s\n", first_str);
    printf("Last Usable Host     : %s\n", last_str);
    printf("Number of Hosts      : %d\n", usable_hosts);

    printf("\n");
    return 0;
}
