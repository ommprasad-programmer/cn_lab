/*
PR6_1_DNS.c:
Program to implement a DNS query generator to resolve domain names.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DNS_PORT 53
#define MAXBUF 512

// DNS header structure
struct DNSHeader
{
    unsigned short id;
    unsigned short flags;
    unsigned short qd_count;
    unsigned short an_count;
    unsigned short ns_count;
    unsigned short ar_count;
};

// DNS question section ends with type (A) and class (IN)
struct DNSQuestion
{
    unsigned short qtype;
    unsigned short qclass;
};

void encode_hostname(char *encoded, const char *host)
{
    while (*host)
    {
        const char *dot = strchr(host, '.');
        int len = dot ? dot - host : strlen(host);
        *encoded++ = len;
        memcpy(encoded, host, len);
        encoded += len;
        if (!dot) break;
        host = dot + 1;
    }
    *encoded++ = 0;
}

int main()
{
    char domain[256];
    unsigned char buf[MAXBUF];

    printf("\nEnter domain to resolve (e.g., google.com): ");
    scanf("%s", domain);

    // Create socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(DNS_PORT);
    dest.sin_addr.s_addr = inet_addr("8.8.8.8"); // Google's DNS

    // Build DNS request
    struct DNSHeader *dns = (struct DNSHeader *)buf;
    dns->id = htons(rand() % 65536);
    dns->flags = htons(0x0100);        // standard query, recursion desired
    dns->qd_count = htons(1);
    dns->an_count = 0;
    dns->ns_count = 0;
    dns->ar_count = 0;

    // Encode domain name
    unsigned char *qname = buf + sizeof(struct DNSHeader);
    encode_hostname((char *)qname, domain);

    // Add question type and class
    struct DNSQuestion *qinfo = (struct DNSQuestion *)(qname + strlen((char *)qname) + 1);
    qinfo->qtype = htons(1);   // A record
    qinfo->qclass = htons(1);  // IN class

    int query_len = sizeof(struct DNSHeader) + strlen((char *)qname) + 1 + sizeof(struct DNSQuestion);

    sendto(sock, buf, query_len, 0, (struct sockaddr *)&dest, sizeof(dest));

    printf("\n[Client] DNS Query Sent for %s\n", domain);

    // Receive response
    socklen_t len = sizeof(dest);
    int n = recvfrom(sock, buf, MAXBUF, 0, (struct sockaddr *)&dest, &len);

    if (n < 0)
    {
        perror("recvfrom failed");
        return 1;
    }

    // Skip header and question
    int offset = sizeof(struct DNSHeader);
    while (buf[offset] != 0) offset += buf[offset] + 1;
    offset += 1 + sizeof(struct DNSQuestion);

    // Process answer
    printf("\n[Client] Response Received:\n");
    for (int i = 0; i < ntohs(dns->an_count); i++)
    {
        offset += 2; // name pointer
        unsigned short type = ntohs(*(unsigned short *)(buf + offset));
        offset += 2;
        offset += 2; // class
        offset += 4; // TTL
        unsigned short data_len = ntohs(*(unsigned short *)(buf + offset));
        offset += 2;

        if (type == 1 && data_len == 4) { // A record
            struct in_addr addr;
            memcpy(&addr, buf + offset, 4);
            printf("  IP Address: %s\n", inet_ntoa(addr));
        }
        offset += data_len;
    }

    close(sock);

    printf("\n");
    return 0;
}
