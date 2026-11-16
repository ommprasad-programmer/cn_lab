#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool parse_and_validate_ipv4(const char *ip_str, int *o1, int *o2, int *o3, int *o4) {
    if (ip_str == NULL || strlen(ip_str) == 0) return false;

    int dot_count = 0;
    for (int i = 0; ip_str[i] != '\0'; i++) {
        if (ip_str[i] == '.') dot_count++;
        else if (!isdigit((unsigned char)ip_str[i])) return false;
    }
    if (dot_count != 3) return false;

    char copy[64];
    strncpy(copy, ip_str, 63);
    copy[63] = '\0';

    char *token = strtok(copy, ".");
    int octets[4];
    int count = 0;

    while (token != NULL) {
        if (count >= 4) return false;
        if (strlen(token) == 0 || strlen(token) > 3) return false;
        if (strlen(token) > 1 && token[0] == '0') return false;

        char *endptr;
        long val = strtol(token, &endptr, 10);
        if (*endptr != '\0' || val < 0 || val > 255) return false;

        octets[count++] = (int)val;
        token = strtok(NULL, ".");
    }

    if (count != 4) return false;

    *o1 = octets[0];
    *o2 = octets[1];
    *o3 = octets[2];
    *o4 = octets[3];

    return true;
}

char identify_class(int first_octet, const char **default_mask, const char **description) {
    if (first_octet >= 1 && first_octet <= 126) {
        *default_mask = "255.0.0.0 (/8)";
        *description = "Unicast (Class A - Large Networks)";
        return 'A';
    } else if (first_octet == 127) {
        *default_mask = "255.0.0.0 (/8)";
        *description = "Loopback / Diagnostic Block";
        return 'L';
    } else if (first_octet >= 128 && first_octet <= 191) {
        *default_mask = "255.255.0.0 (/16)";
        *description = "Unicast (Class B - Medium Networks)";
        return 'B';
    } else if (first_octet >= 192 && first_octet <= 223) {
        *default_mask = "255.255.255.0 (/24)";
        *description = "Unicast (Class C - Small Networks)";
        return 'C';
    } else if (first_octet >= 224 && first_octet <= 239) {
        *default_mask = "Not Applicable";
        *description = "Multicast (Class D)";
        return 'D';
    } else if (first_octet >= 240 && first_octet <= 255) {
        *default_mask = "Not Applicable";
        *description = "Reserved / Experimental (Class E)";
        return 'E';
    } else {
        *default_mask = "Not Applicable";
        *description = "Special / Reserved (0.0.0.0/8)";
        return '0';
    }
}

int main(void) {
    char input_ip[128];
    int o1, o2, o3, o4;

    printf("============================================================\n");
    printf("         IPv4 Address Validation and Classification         \n");
    printf("============================================================\n");

    printf("Enter an IPv4 address (e.g. 192.168.1.10): ");
    if (scanf("%127s", input_ip) != 1) {
        printf("Error: Failed to read input.\n");
        return 1;
    }

    if (!parse_and_validate_ipv4(input_ip, &o1, &o2, &o3, &o4)) {
        printf("\nResult: INVALID IPv4 Address!\n");
        printf("Reason: The input must consist of exactly 4 octets separated by dots,\n");
        printf("        each octet ranging from 0 to 255 without leading zeros.\n");
        return 1;
    }

    const char *default_mask = "";
    const char *description = "";
    char class_id = identify_class(o1, &default_mask, &description);

    printf("\n--- Validation and Analysis Result ---\n");
    printf("Status:              VALID IPv4 Address\n");
    printf("Standard Notation:   %d.%d.%d.%d\n", o1, o2, o3, o4);
    printf("Octet Breakdown:     Octet1 = %d, Octet2 = %d, Octet3 = %d, Octet4 = %d\n", o1, o2, o3, o4);

    if (class_id >= 'A' && class_id <= 'E') {
        printf("Address Class:       Class %c\n", class_id);
    } else if (class_id == 'L') {
        printf("Address Class:       Loopback Address (Class A range)\n");
    } else {
        printf("Address Class:       Special / Default Route\n");
    }

    printf("Designated Purpose:  %s\n", description);
    printf("Default Subnet Mask: %s\n", default_mask);

    return 0;
}
