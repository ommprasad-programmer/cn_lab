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
    printf("        Generation of All Usable Host IP Addresses          \n");
    printf("============================================================\n");

    printf("Enter IPv4 Address (e.g. 192.168.1.10): ");
    if (scanf("%63s", ip_str) != 1 || !parse_ip(ip_str, &ip)) {
        printf("Error: Invalid IPv4 address format.\n");
        return 1;
    }

    printf("Enter Subnet Mask or CIDR prefix (e.g. 255.255.255.240 or 28): ");
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
    uint32_t broadcast = network | (~mask);

    char net_str[32], bcast_str[32];
    format_ip(network, net_str);
    format_ip(broadcast, bcast_str);

    printf("\nSubnet Network Address:   %s\n", net_str);
    printf("Subnet Broadcast Address: %s\n", bcast_str);

    if (prefix >= 31) {
        printf("Subnet prefix /%d does not have standard separate usable host ranges.\n", prefix);
        return 0;
    }

    uint32_t first_host = network + 1;
    uint32_t last_host = broadcast - 1;
    uint64_t total_hosts = (uint64_t)(last_host - first_host + 1);

    printf("Total Usable Hosts:       %llu\n", (unsigned long long)total_hosts);

    int display_limit = 0;
    printf("\nEnter maximum number of host IPs to display (e.g. 50, or 0 for all): ");
    if (scanf("%d", &display_limit) != 1 || display_limit < 0) {
        printf("Error: Invalid display limit.\n");
        return 1;
    }

    uint64_t count_to_show = (display_limit == 0 || (uint64_t)display_limit > total_hosts) ? total_hosts : (uint64_t)display_limit;

    printf("\n--- Usable Host IP Addresses (Showing %llu of %llu) ---\n",
           (unsigned long long)count_to_show, (unsigned long long)total_hosts);

    for (uint64_t i = 0; i < count_to_show; i++) {
        uint32_t current_host = first_host + (uint32_t)i;
        char host_str[32];
        format_ip(current_host, host_str);
        printf("Host %4llu: %s\n", (unsigned long long)(i + 1), host_str);
    }

    if (count_to_show < total_hosts) {
        printf("... (%llu more hosts not displayed. Last host is ", (unsigned long long)(total_hosts - count_to_show));
        char last_str[32];
        format_ip(last_host, last_str);
        printf("%s)\n", last_str);
    }

    return 0;
}
