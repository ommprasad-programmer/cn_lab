/*
PR4_5_IPv4PacketFragmentationAndReassembly.c:
Program that performs IP Fragmentation and Reassembly with realistic IPv4 header fields.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HEADER_SIZE 20
#define MAX_FRAGMENTS 50
#define MAX_DATA_LEN 1000
#define IP_VERSION 4
#define IP_IHL 5
#define TTL 64
#define PROTOCOL_TCP 6

// IP Fragment structure simulating real IPv4 header
typedef struct
{
    int version;         // IPv4
    int ihl;             // Internet Header Length
    int total_length;    // Header + Data
    int identification;  // Unique ID for message
    int flags;           // 0x1 for MF (More Fragments)
    int frag_offset;     // Offset in 8-byte units
    int ttl;             // Time to Live
    int protocol;        // TCP = 6
    int checksum;        // Ignored for this simulation
    char src_ip[16];     // Simulated IP
    char dest_ip[16];    // Simulated IP
    char data[100];      // Payload data
} IPFragment;

int fragmentMessage(const char *message, int mtu, IPFragment fragments[], int identification)
{
    int message_len = strlen(message);
    int payload_size = mtu - HEADER_SIZE;

    if (payload_size <= 0)
    {
        printf("MTU too small for header.\n");
        return 0;
    }

    int offset = 0;
    int index = 0;
    int num_fragments = 0;

    while (index < message_len)
    {
        IPFragment *frag = &fragments[num_fragments];

        frag->version = IP_VERSION;
        frag->ihl = IP_IHL;
        frag->identification = identification;
        frag->frag_offset = offset / 8; // offset in 8-byte units
        frag->ttl = TTL;
        frag->protocol = PROTOCOL_TCP;
        frag->checksum = 0;
        strcpy(frag->src_ip, "192.168.0.1");
        strcpy(frag->dest_ip, "192.168.0.2");

        int copy_len = (message_len - index > payload_size) ? payload_size : message_len - index;
        strncpy(frag->data, message + index, copy_len);
        frag->data[copy_len] = '\0';

        frag->flags = (index + copy_len < message_len) ? 1 : 0; // MF = 1 if more fragments follow
        frag->total_length = HEADER_SIZE + copy_len;

        index += copy_len;
        offset += copy_len;
        num_fragments++;
    }

    return num_fragments;
}

void printFragmentHeader(IPFragment *frag, int index)
{
    printf("Fragment %d:\n", index + 1);
    printf("  Version: %d\n", frag->version);
    printf("  IHL: %d (Header size: %d bytes)\n", frag->ihl, frag->ihl * 4);
    printf("  Total Length: %d bytes\n", frag->total_length);
    printf("  ID: %d\n", frag->identification);
    printf("  Flags (MF): %d\n", frag->flags);
    printf("  Fragment Offset: %d (bytes: %d)\n", frag->frag_offset, frag->frag_offset * 8);
    printf("  TTL: %d\n", frag->ttl);
    printf("  Protocol: %d\n", frag->protocol);
    printf("  Source IP: %s\n", frag->src_ip);
    printf("  Destination IP: %s\n", frag->dest_ip);
    printf("  Data: \"%s\"\n\n", frag->data);
}

void reassembleMessage(IPFragment fragments[], int num_fragments, char *output)
{
    output[0] = '\0';
    for (int i = 0; i < num_fragments; i++)
    {
        strcat(output, fragments[i].data);
    }
}

int main()
{
    char message[MAX_DATA_LEN];
    int mtu;
    int id = 12345; // unique ID

    printf("\nEnter the message to be fragmented: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;

    printf("Enter the MTU size: ");
    scanf("%d", &mtu);

    if (mtu <= HEADER_SIZE)
    {
        printf("MTU must be greater than IPv4 header size (%d bytes).\n", HEADER_SIZE);
        return 1;
    }

    IPFragment fragments[MAX_FRAGMENTS];
    int count = fragmentMessage(message, mtu, fragments, id);

    printf("\n--- IP Fragments ---\n");
    for (int i = 0; i < count; i++)
    {
        printFragmentHeader(&fragments[i], i);
    }

    char reassembled[MAX_DATA_LEN];
    reassembleMessage(fragments, count, reassembled);
    printf("--- Reassembled Message ---\n");
    printf("%s\n", reassembled);

    printf("\n");
    return 0;
}
