/*
PR5_3_TCPCongestionControl.c:
Program to simulate TCP congestion control technique (Slow Start, Congestion Avoidance, and
Congestion Detection) over UDP.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define CHUNK_SIZE 5
#define PORT_DATA 9000
#define PORT_ACK 9001
#define LOSS_PROB 0.2
#define MAX_MSG 1024

typedef struct
{
    int seq;
    char data[CHUNK_SIZE];
} Packet;

int simulate_loss()
{
    return ((float)rand() / RAND_MAX) < LOSS_PROB;
}

void sender(char *message)
{
    int sockfd_data = socket(AF_INET, SOCK_DGRAM, 0);
    int sockfd_ack = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in recv_addr, ack_addr, sender_bind;
    socklen_t len = sizeof(struct sockaddr_in);

    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(PORT_DATA);
    recv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(&sender_bind, 0, sizeof(sender_bind));
    sender_bind.sin_family = AF_INET;
    sender_bind.sin_port = htons(PORT_ACK);
    sender_bind.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd_ack, (struct sockaddr *)&sender_bind, sizeof(sender_bind));

    int total_chunks = (strlen(message) + CHUNK_SIZE - 1) / CHUNK_SIZE;
    int base = 0, cwnd = 1, ssthresh = 4;
    int last_ack = -1, dup_acks = 0;

    srand(time(NULL));

    while (base < total_chunks)
    {
        printf("\n[Sender] cwnd = %d, ssthresh = %d\n", cwnd, ssthresh);
        for (int i = base; i < base + cwnd && i < total_chunks; i++)
        {
            Packet pkt;
            pkt.seq = i;
            memset(pkt.data, 0, CHUNK_SIZE);
            strncpy(pkt.data, &message[i * CHUNK_SIZE], CHUNK_SIZE);
            sendto(sockfd_data, &pkt, sizeof(pkt), 0, (struct sockaddr *)&recv_addr, len);
            printf("[Sender] Sent packet %d: %.*s\n", pkt.seq, CHUNK_SIZE, pkt.data);
        }

        struct timeval timeout = {1, 0};
        setsockopt(sockfd_ack, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

        int acked = 0;
        for (int i = 0; i < cwnd && base + i < total_chunks; i++)
        {
            int ack;
            int n = recvfrom(sockfd_ack, &ack, sizeof(ack), 0, NULL, NULL);
            if (n <= 0) break;
            printf("[Sender] Received ACK %d\n", ack);

            if (ack == last_ack)
                dup_acks++;
            else
            {
                dup_acks = 0;
                last_ack = ack;
            }

            if (dup_acks == 3)
            {
                printf("[Sender] Fast retransmit on packet %d\n", ack);
                ssthresh = cwnd / 2 > 1 ? cwnd / 2 : 1;
                cwnd = ssthresh + 3;
                break;
            }
            acked++;
        }

        if (acked == 0)
        {
            printf("[Sender] Timeout. Reducing cwnd.\n");
            ssthresh = cwnd / 2 > 1 ? cwnd / 2 : 1;
            cwnd = 1;
        }
        else
        {
            base += acked;
            cwnd = (cwnd < ssthresh) ? cwnd * 2 : cwnd + 1;
        }
    }

    close(sockfd_data);
    close(sockfd_ack);
}

void receiver(int expected_chunks)
{
    int sockfd_data = socket(AF_INET, SOCK_DGRAM, 0);
    int sockfd_ack = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in recv_addr, sender_addr;
    socklen_t len = sizeof(sender_addr);

    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(PORT_DATA);
    recv_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd_data, (struct sockaddr *)&recv_addr, sizeof(recv_addr));

    struct sockaddr_in ack_dest;
    ack_dest.sin_family = AF_INET;
    ack_dest.sin_port = htons(PORT_ACK);
    ack_dest.sin_addr.s_addr = inet_addr("127.0.0.1");

    char buffer[MAX_MSG] = {0};
    int received[MAX_MSG / CHUNK_SIZE] = {0};
    int chunks_received = 0;

    printf("[Receiver] Ready to receive.\n");

    while (chunks_received < expected_chunks)
    {
        Packet pkt;
        int n = recvfrom(sockfd_data, &pkt, sizeof(pkt), 0, (struct sockaddr *)&sender_addr, &len);
        if (n <= 0) continue;

        if (simulate_loss())
        {
            printf("[Receiver] Dropped packet %d\n", pkt.seq);
            continue;
        }

        if (!received[pkt.seq])
        {
            printf("[Receiver] Received packet %d: %.*s\n", pkt.seq, CHUNK_SIZE, pkt.data);
            strncpy(&buffer[pkt.seq * CHUNK_SIZE], pkt.data, CHUNK_SIZE);
            received[pkt.seq] = 1;
            chunks_received++;
        }
        else
        {
            printf("[Receiver] Duplicate packet %d\n", pkt.seq);
        }

        sendto(sockfd_ack, &pkt.seq, sizeof(pkt.seq), 0,
               (struct sockaddr *)&ack_dest, sizeof(ack_dest));
    }

    printf("\n[Receiver] Final Message: %s\n", buffer);

    close(sockfd_data);
    close(sockfd_ack);
}

int main()
{
    char msg[MAX_MSG];
    printf("\n=== TCP CONGESTION CONTROL SIMULATION ===\n");
    printf("\nEnter message to send: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = 0;

    int chunks = (strlen(msg) + CHUNK_SIZE - 1) / CHUNK_SIZE;

    pid_t pid = fork();
    if (pid == 0)
        receiver(chunks);
    else
        sender(msg);

    printf("\nThe message sent successfully from Sender to Receiver.\n\n");
    return 0;
}
