/*
PR5_1_UDPDataTransfer.c:
Program to simulate data transfer using UDP.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define CHUNK_SIZE 16    // 128 bits = 16 bytes
#define MAX_MSG 1024
#define PORT_SENDER 4000
#define PORT_RECEIVER 5000
#define LOSS_PROB 0.25   // 25% chance to lose a packet

// Simulated UDP packet structure
typedef struct
{
    unsigned short src_port;
    unsigned short dest_port;
    unsigned short length;
    unsigned short checksum;
    char data[CHUNK_SIZE];
} UDP_Packet;

int simulate_loss()
{
    return ((float)rand() / RAND_MAX) < LOSS_PROB;
}

void sender(const char *message)
{
    int sockfd;
    struct sockaddr_in receiver_addr;
    socklen_t len = sizeof(receiver_addr);

    int total_chunks = (strlen(message) + CHUNK_SIZE - 1) / CHUNK_SIZE;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT_RECEIVER);
    receiver_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("\n=== SENDER ===\n");

    for (int i = 0; i < total_chunks; i++)
    {
        UDP_Packet pkt = {0};
        strncpy(pkt.data, &message[i * CHUNK_SIZE], CHUNK_SIZE);

        pkt.src_port = PORT_SENDER;
        pkt.dest_port = PORT_RECEIVER;
        pkt.length = sizeof(pkt);
        pkt.checksum = 0; // placeholder

        printf("\n[Sender] Packet %d Header:\n", i + 1);
        printf("  Source Port:      %d\n", pkt.src_port);
        printf("  Destination Port: %d\n", pkt.dest_port);
        printf("  Length:           %d bytes\n", pkt.length);
        printf("  Checksum:         %d (dummy)\n", pkt.checksum);
        printf("  Data:             \"%.*s\"\n", CHUNK_SIZE, pkt.data);

        sendto(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&receiver_addr, len);
        usleep(50000); // simulate network delay
    }

    close(sockfd);
}

void receiver(int expected_chunks)
{
    int sockfd;
    struct sockaddr_in receiver_addr, sender_addr;
    socklen_t len = sizeof(sender_addr);
    UDP_Packet pkt;
    char message[MAX_MSG] = {0};

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT_RECEIVER);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr));
    srand(time(NULL));

    printf("\n=== RECEIVER ===\n");

    int received = 0;
    while (received < expected_chunks)
    {
        int n = recvfrom(sockfd, &pkt, sizeof(pkt), 0,
                         (struct sockaddr *)&sender_addr, &len);
        if (n <= 0) continue;

        if (simulate_loss())
        {
            printf("[Receiver] Dropped packet %d\n", received + 1);
            continue;
        }

        printf("[Receiver] Received packet %d: \"%.*s\"\n", received + 1, CHUNK_SIZE, pkt.data);
        strncat(message, pkt.data, CHUNK_SIZE);
        received++;
    }

    printf("\n[Receiver] Full Reconstructed Message: %s\n", message);
    close(sockfd);
}

int main()
{
    char message[MAX_MSG];
    printf("\n=== UDP DATA TRANSFER SIMULATION ===\n");
    printf("\nEnter your message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;

    int chunks = (strlen(message) + CHUNK_SIZE - 1) / CHUNK_SIZE;

    pid_t pid = fork();
    if (pid == 0)
    {
        sleep(1); // ensure receiver binds first
        sender(message);
    }
    else
    {
        receiver(chunks);
    }

    printf("\nEnd of Simulation.\n\n");
    return 0;
}
