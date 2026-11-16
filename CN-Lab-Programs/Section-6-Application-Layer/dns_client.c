#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

void resolve_hostname(const char *hostname) {
    struct addrinfo hints;
    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;

    printf("\nPerforming DNS query for: \"%s\"...\n", hostname);

    int status = getaddrinfo(hostname, NULL, &hints, &result);
    if (status != 0) {
        printf("DNS Resolution Error: %s\n", gai_strerror(status));
        return;
    }

    if (result->ai_canonname != NULL) {
        printf("Canonical Name (CNAME): %s\n", result->ai_canonname);
    }

    printf("\nResolved IPv4 Address(es):\n");
    printf("-----------------------------------------\n");

    int count = 0;
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)ptr->ai_addr;
        char ip_string[INET_ADDRSTRLEN];
        if (inet_ntop(AF_INET, &(ipv4->sin_addr), ip_string, sizeof(ip_string)) != NULL) {
            count++;
            printf("  Address %d: %s\n", count, ip_string);
        }
    }
    printf("-----------------------------------------\n");
    printf("Total records found: %d\n", count);

    freeaddrinfo(result);
}

int main(void) {
    char hostname[256];

    printf("============================================================\n");
    printf("                  DNS Client Simulation                     \n");
    printf("============================================================\n");

    printf("Enter hostname/domain name to resolve (e.g. localhost, google.com): ");
    if (scanf("%255s", hostname) != 1) {
        printf("Error: Failed to read hostname.\n");
        return 1;
    }

    if (strlen(hostname) == 0) {
        printf("Error: Hostname cannot be empty.\n");
        return 1;
    }

    resolve_hostname(hostname);

    return 0;
}
