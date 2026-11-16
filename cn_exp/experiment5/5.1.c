/*
PR5_1_UDPSimulation.c:
Program to simulate connectionless UDP Data Transfer.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PAYLOAD 50

struct Datagram
{
    int source_port;
    int dest_port;
    int total_length;
    int checksum;
    char payload[MAX_PAYLOAD];
};

int calculateSimpleChecksum(const char *data)
{
    int sum = 0;
    for (int i = 0; i < strlen(data); i++)
    {
        sum += (int)data[i];
    }
    return sum % 256;
}

int main()
{
    struct Datagram packet;
    srand(time(NULL));

    printf("\n=== Simulation of UDP Data Transfer (Connectionless) ===\n");
    printf("Enter Source Port (e.g., 8080): ");
    scanf("%d", &packet.source_port);
    printf("Enter Destination Port (e.g., 53): ");
    scanf("%d", &packet.dest_port);

    printf("Enter message payload text (no spaces): ");
    scanf("%s", packet.payload);

    packet.total_length = sizeof(packet.source_port) + sizeof(packet.dest_port) +
                          sizeof(packet.total_length) + sizeof(packet.checksum) +
                          strlen(packet.payload);
    packet.checksum = calculateSimpleChecksum(packet.payload);

    printf("\n--- Sender: Encapsulating UDP Datagram ---\n");
    printf("Header -> Src Port: %d | Dest Port: %d | Len: %d bytes | Checksum: 0x%02X\n",
           packet.source_port, packet.dest_port, packet.total_length, packet.checksum);
    printf("Transmitting message to the network medium...\n");

    // Simulate connectionless channel behavior (0 = Lost in Transit, 1 = Successfully Received)
    int channel_status = rand() % 4;

    if (channel_status == 0)
    {
        printf("\n!!! Network Drop: Datagram lost in transit. No error detection or feedback triggered (Unreliable Mode) !!!\n\n");
    }
    else
    {
        printf("\n--- Receiver: Processing Arrived Datagram ---\n");
        printf("Received Packet Content from Port %d: [ %s ]\n", packet.source_port, packet.payload);

        int rx_checksum = calculateSimpleChecksum(packet.payload);
        if (rx_checksum == packet.checksum)
        {
            printf("Integrity Validation: Checksum matches (0x%02X). Data accepted.\n\n", rx_checksum);
        }
        else
        {
            printf("Integrity Validation Error: Corrupted Checksum! Packet dropped.\n\n");
        }
    }

    return 0;
}
