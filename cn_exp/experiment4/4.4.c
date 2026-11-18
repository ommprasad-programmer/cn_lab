/*
PR4_4_VLSMImplementation.c:
Program that takes as input a major network (e.g., 192.168.0.0/24) and a list of required
hosts for multiple subnets.
It allocates subnets using VLSM and generates the list of allocated subnets with proper
mask.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <math.h>

#define MAX_SUBNETS 100

typedef struct
{
    int hosts_required;
    int subnet_size;
    int prefix;
    unsigned int subnet_address;
} Subnet;

// Calculate smallest power of 2 - 2 >= hosts_required
int calculate_prefix(int hosts_required)
{
    int bits = 0;
    while ((1 << bits) - 2 < hosts_required)
        bits++;
    return 32 - bits;
}

int compare(const void *a, const void *b)
{
    Subnet *sa = (Subnet *)a;
    Subnet *sb = (Subnet *)b;
    return sb->hosts_required - sa->hosts_required;  // Descending order
}

void int_to_ip(unsigned int ip, char *buf)
{
    struct in_addr addr;
    addr.s_addr = htonl(ip);
    strcpy(buf, inet_ntoa(addr));
}

int main()
{
    char major_net_str[30];
    char ip_part[20];
    int major_prefix;
    unsigned int major_ip, major_netmask;

    Subnet subnets[MAX_SUBNETS];
    int subnet_count;

    printf("\nEnter major network in CIDR notation (e.g., 192.168.0.0/24): ");
    scanf("%29s", major_net_str);

    char *slash = strchr(major_net_str, '/');
    if (!slash)
    {
        printf("Invalid format.\n\n");
        return 1;
    }

    *slash = '\0';
    strcpy(ip_part, major_net_str);
    major_prefix = atoi(slash + 1);

    if (inet_pton(AF_INET, ip_part, &major_ip) != 1 || major_prefix < 0 || major_prefix > 32)
    {
        printf("Invalid major network.\n\n");
        return 1;
    }

    major_ip = ntohl(major_ip);
    major_netmask = major_prefix == 0 ? 0 : (~0U << (32 - major_prefix));

    printf("Enter number of subnets to allocate: ");
    scanf("%d", &subnet_count);

    for (int i = 0; i < subnet_count; i++)
    {
        printf("Enter number of hosts for subnet %d: ", i + 1);
        scanf("%d", &subnets[i].hosts_required);
        subnets[i].prefix = calculate_prefix(subnets[i].hosts_required);
        subnets[i].subnet_size = 1 << (32 - subnets[i].prefix);
    }

    qsort(subnets, subnet_count, sizeof(Subnet), compare);

    unsigned int current_ip = major_ip;
    unsigned int end_of_major = (major_ip | ~major_netmask);

    printf("\n--- VLSM Subnet Allocation ---\n");
    for (int i = 0; i < subnet_count; i++)
    {
        if (current_ip + subnets[i].subnet_size - 1 > end_of_major)
        {
            printf("Not enough space for subnet %d\n\n", i + 1);
            return 1;
        }

        subnets[i].subnet_address = current_ip;

        char ip_buf[INET_ADDRSTRLEN];
        int_to_ip(current_ip, ip_buf);
        printf("Subnet %d: %s/%d  (Hosts: %d)\n", i + 1, ip_buf, subnets[i].prefix, subnets[i].subnet_size - 2);

        current_ip += subnets[i].subnet_size;
    }

    printf("\n");
    return 0;
}
