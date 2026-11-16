#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

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

int count_prefix_bits(uint32_t mask) {
    int count = 0;
    for (int i = 31; i >= 0; i--) {
        if ((mask >> i) & 1) count++;
        else break;
    }
    return count;
}

int main(void) {
    char ip_str[64];
    char mask_str[64];
    uint32_t ip = 0;
    uint32_t mask = 0;

    printf("============================================================\n");
    printf("        IPv4 Subnet Information and Address Calculator      \n");
    printf("============================================================\n");

    printf("Enter IPv4 Address (e.g. 192.168.10.75): ");
    if (scanf("%63s", ip_str) != 1 || !parse_ip(ip_str, &ip)) {
        printf("Error: Invalid IPv4 address format.\n");
        return 1;
    }

    printf("Enter Subnet Mask (dotted-decimal e.g. 255.255.255.0 or prefix e.g. 24): ");
    if (scanf("%63s", mask_str) != 1) {
        printf("Error reading mask.\n");
        return 1;
    }

    int prefix = 0;
    if (strchr(mask_str, '.') == NULL) {
        if (sscanf(mask_str, "%d", &prefix) != 1 || prefix < 0 || prefix > 32) {
            printf("Error: Prefix must be an integer between 0 and 32.\n");
            return 1;
        }
        mask = (prefix == 0) ? 0 : (~0U << (32 - prefix));
    } else {
        if (!parse_ip(mask_str, &mask)) {
            printf("Error: Invalid subnet mask format.\n");
            return 1;
        }
        prefix = count_prefix_bits(mask);
    }

    uint32_t network = ip & mask;
    uint32_t wildcard = ~mask;
    uint32_t broadcast = network | wildcard;

    char net_str[32], bcast_str[32], mask_formatted[32], wild_str[32];
    char first_host_str[32], last_host_str[32];

    format_ip(network, net_str);
    format_ip(broadcast, bcast_str);
    format_ip(mask, mask_formatted);
    format_ip(wildcard, wild_str);

    uint64_t total_addresses = 1ULL << (32 - prefix);
    uint64_t usable_hosts = 0;

    if (prefix <= 30) {
        usable_hosts = total_addresses - 2;
        format_ip(network + 1, first_host_str);
        format_ip(broadcast - 1, last_host_str);
    } else if (prefix == 31) {
        usable_hosts = 2;
        format_ip(network, first_host_str);
        format_ip(broadcast, last_host_str);
    } else {
        usable_hosts = 1;
        format_ip(network, first_host_str);
        format_ip(network, last_host_str);
    }

    printf("\n--- Subnet Information Summary ---\n");
    printf("Configured IP:        %s\n", ip_str);
    printf("Subnet Mask:          %s (/%d)\n", mask_formatted, prefix);
    printf("Wildcard Mask:        %s\n", wild_str);
    printf("Network Address:      %s\n", net_str);
    printf("Broadcast Address:    %s\n", bcast_str);
    printf("First Usable Host:    %s\n", first_host_str);
    printf("Last Usable Host:     %s\n", last_host_str);
    printf("Total Addresses:      %llu\n", (unsigned long long)total_addresses);
    printf("Usable Host Count:    %llu\n", (unsigned long long)usable_hosts);

    return 0;
}
