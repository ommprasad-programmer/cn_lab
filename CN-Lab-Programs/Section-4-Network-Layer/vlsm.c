#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SUBNETS 32

typedef struct {
    char name[32];
    int required_hosts;
    int allocated_hosts;
    int prefix;
    uint32_t network_ip;
    uint32_t mask;
    uint32_t broadcast_ip;
    uint32_t first_host;
    uint32_t last_host;
} SubnetRequest;

bool parse_ip(const char *str, uint32_t *ip_val) {
    int o1, o2, o3, o4;
    if (sscanf(str, "%d.%d.%d.%d", &o1, &o2, &o3, &o4) != 4) return false;
    if (o1 < 0 || o1 > 255 || o2 < 0 || o2 > 255 || o3 < 0 || o3 > 255 || o4 < 0 || o4 > 255) return false;
    *ip_val = ((uint32_t)o1 << 24) | ((uint32_t)o2 << 16) | ((uint32_t)o3 << 8) | (uint32_t)o4;
    return true;
}

void format_ip(uint32_t ip, char *buffer) {
    sprintf(buffer, "%u.%u.%u.%u",
            (ip >> 24) & 0xFF,
            (ip >> 16) & 0xFF,
            (ip >> 8) & 0xFF,
            ip & 0xFF);
}

int calculate_host_bits(int needed_hosts) {
    int bits = 2;
    while ((1U << bits) - 2 < (unsigned int)needed_hosts) {
        bits++;
        if (bits > 30) return -1;
    }
    return bits;
}

int compare_subnets(const void *a, const void *b) {
    const SubnetRequest *sub_a = (const SubnetRequest *)a;
    const SubnetRequest *sub_b = (const SubnetRequest *)b;
    return sub_b->required_hosts - sub_a->required_hosts;
}

int main(void) {
    char base_ip_str[64];
    int base_prefix = 0;
    int num_subnets = 0;
    SubnetRequest subnets[MAX_SUBNETS];

    printf("============================================================\n");
    printf("     Variable Length Subnet Masking (VLSM) Calculator       \n");
    printf("============================================================\n");

    printf("Enter Major Network IP (e.g. 192.168.1.0): ");
    uint32_t base_ip = 0;
    if (scanf("%63s", base_ip_str) != 1 || !parse_ip(base_ip_str, &base_ip)) {
        printf("Error: Invalid IP address format.\n");
        return 1;
    }

    printf("Enter Major Network CIDR Prefix (e.g. 24): ");
    if (scanf("%d", &base_prefix) != 1 || base_prefix < 1 || base_prefix > 30) {
        printf("Error: Invalid CIDR prefix.\n");
        return 1;
    }

    printf("Enter number of subnets needed (1 to %d): ", MAX_SUBNETS);
    if (scanf("%d", &num_subnets) != 1 || num_subnets < 1 || num_subnets > MAX_SUBNETS) {
        printf("Error: Invalid number of subnets.\n");
        return 1;
    }

    for (int i = 0; i < num_subnets; i++) {
        printf("Enter name/label for Subnet %d: ", i + 1);
        if (scanf("%31s", subnets[i].name) != 1) {
            printf("Error reading subnet name.\n");
            return 1;
        }
        printf("Enter number of required usable hosts for %s: ", subnets[i].name);
        if (scanf("%d", &subnets[i].required_hosts) != 1 || subnets[i].required_hosts <= 0) {
            printf("Error: Required host count must be positive.\n");
            return 1;
        }
    }

    qsort(subnets, num_subnets, sizeof(SubnetRequest), compare_subnets);

    uint32_t major_mask = (base_prefix == 0) ? 0 : (~0U << (32 - base_prefix));
    base_ip = base_ip & major_mask;
    uint32_t current_ip = base_ip;
    uint32_t major_end = base_ip | (~major_mask);

    for (int i = 0; i < num_subnets; i++) {
        int host_bits = calculate_host_bits(subnets[i].required_hosts);
        if (host_bits < 0) {
            printf("Error: Host requirement too large.\n");
            return 1;
        }
        subnets[i].prefix = 32 - host_bits;
        subnets[i].allocated_hosts = (1U << host_bits) - 2;
        subnets[i].mask = ~0U << host_bits;

        uint32_t block_size = 1U << host_bits;

        if ((uint64_t)current_ip + block_size - 1 > (uint64_t)major_end) {
            printf("\nError: Major network address space exhausted at subnet '%s'!\n", subnets[i].name);
            return 1;
        }

        subnets[i].network_ip = current_ip;
        subnets[i].broadcast_ip = current_ip + block_size - 1;
        subnets[i].first_host = current_ip + 1;
        subnets[i].last_host = subnets[i].broadcast_ip - 1;

        current_ip += block_size;
    }

    printf("\n========================================================================================================\n");
    printf("                                         VLSM Subnet Allocation Table                                   \n");
    printf("========================================================================================================\n");
    printf("%-10s %-8s %-8s %-16s %-16s %-16s %-16s\n",
           "Subnet", "Needed", "Alloc", "Network / CIDR", "Mask", "Usable Host Range", "Broadcast");
    printf("--------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_subnets; i++) {
        char net_s[32], mask_s[32], first_s[32], last_s[32], bcast_s[32];
        char range_s[128];
        char net_cidr[64];
        format_ip(subnets[i].network_ip, net_s);
        format_ip(subnets[i].mask, mask_s);
        format_ip(subnets[i].first_host, first_s);
        format_ip(subnets[i].last_host, last_s);
        format_ip(subnets[i].broadcast_ip, bcast_s);

        snprintf(net_cidr, sizeof(net_cidr), "%s/%d", net_s, subnets[i].prefix);
        snprintf(range_s, sizeof(range_s), "%s - %s", first_s, last_s);

        printf("%-10s %-8d %-8d %-16s %-16s %-32s %-16s\n",
               subnets[i].name, subnets[i].required_hosts, subnets[i].allocated_hosts,
               net_cidr, mask_s, range_s, bcast_s);
    }
    printf("========================================================================================================\n");

    return 0;
}
