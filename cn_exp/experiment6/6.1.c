/*
PR6_1_DNSSimulation.c:
Program to simulate a Domain Name System (DNS) Client lookup sequence.
*/

#include <stdio.h>
#include <string.h>

#define MAX_ENTRIES 5

// Structure to define DNS resource records mapping context
struct DNSEntry
{
    char domain[50];
    char ip[20];
};

int main()
{
    // Initializing a local simulated DNS database cache table
    struct DNSEntry dns_cache[MAX_ENTRIES] = {
        {"://google.com", "142.250.68.68"},
        {"://bing.com", "204.79.197.200"},
        {"://microsoft.com", "23.211.232.10"},
        {"www.wikipedia.org", "198.35.26.96"},
        {"://github.com", "140.82.112.4"}};

    int choice;
    char search_query[50];
    int found = 0;

    printf("\n=== Domain Name System (DNS) Client Simulator ===\n");
    printf("1. Forward Lookup (Domain Name -> IP Address)\n");
    printf("2. Reverse Lookup (IP Address -> Domain Name)\n");
    printf("Select operating lookup function module (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter Domain Name to resolve (e.g., ://google.com): ");
        scanf("%s", search_query);
        printf("\nDNS Client: Sending query to local DNS resolver server...\n");

        for (int i = 0; i < MAX_ENTRIES; i++)
        {
            if (strcasecmp(dns_cache[i].domain, search_query) == 0)
            {
                printf("DNS Resolver: Match identified in record tables.\n");
                printf(">> Resolved IP Address: %s\n\n", dns_cache[i].ip);
                found = 1;
                break;
            }
        }
    }
    else if (choice == 2)
    {
        printf("Enter IPv4 Address to resolve (e.g., 142.250.68.68): ");
        scanf("%s", search_query);
        printf("\nDNS Client: Sending reverse lookup pointer query file...\n");

        for (int i = 0; i < MAX_ENTRIES; i++)
        {
            if (strcmp(dns_cache[i].ip, search_query) == 0)
            {
                printf("DNS Resolver: Match identified in pointer records.\n");
                printf(">> Resolved Hostname Name: %s\n\n", dns_cache[i].domain);
                found = 1;
                break;
            }
        }
    }
    else
    {
        printf("Error: Invalid choice selection parameters.\n\n");
        return 1;
    }

    if (!found)
    {
        printf("DNS Error Code 404: Host / IP destination mapping not found inside local authoritative tables.\n\n");
    }

    return 0;
}
