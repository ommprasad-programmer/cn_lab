/*
PR4_3_AllUsableHostIPsInSubnet.c:
Program that takes a subnet (e.g., 192.168.1.0/29) and generate all valid host IP addresses
in that subnet range.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

// Convert integer IP to dotted-decimal string
void int_to_ip(unsigned int ip, char *buffer)
{
    struct in_addr addr;
    addr.s_addr = htonl(ip);
    strcpy(buffer, inet_ntoa(addr));
}

int main()
{
    char input[30];
    char ip_part[20];
    int prefix;
    unsigned int ip, netmask, network, broadcast;

    printf("\nEnter subnet in CIDR notation (e.g., 192.168.1.0/29): ");
    scanf("%29s", input);

    // Split CIDR into IP and prefix length
    char *slash = strchr(input, '/');
    if (!slash)
    {
        printf("Invalid CIDR format.\n");
        return 1;
    }

    *slash = '\0';
    strcpy(ip_part, input);
    prefix = atoi(slash + 1);

    if (prefix < 0 || prefix > 32)
    {
        printf("Invalid prefix length.\n");
        return 1;
    }

    if (inet_pton(AF_INET, ip_part, &ip) != 1)
    {
        printf("Invalid IP address.\n");
        return 1;
    }

    ip = ntohl(ip);
    netmask = prefix == 0 ? 0 : (~0U << (32 - prefix));
    network = ip & netmask;
    broadcast = network | ~netmask;

    int host_count = (prefix >= 31) ? 0 : (1 << (32 - prefix)) - 2;

    if (host_count <= 0)
    {
        printf("No usable host addresses in this subnet.\n");
        return 0;
    }

    printf("\nUsable IP addresses in subnet %s/%d:\n", ip_part, prefix);
    for (unsigned int host = network + 1; host < broadcast; host++)
    {
        char ip_str[INET_ADDRSTRLEN];
        int_to_ip(host, ip_str);
        printf("%s\n", ip_str);
    }

    printf("\n");
    return 0;
}
