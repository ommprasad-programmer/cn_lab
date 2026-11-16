/*
PR5_2_TCPHandshakeExchange.c:
Program to simulate TCP connection setup (Three-Way Handshake) and state exchange.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int client_isn, server_isn;
    int client_seq, client_ack;
    int server_seq, server_ack;

    srand(time(NULL));
    client_isn = rand() % 10000 + 1000; // Generate Initial Sequence Numbers
    server_isn = rand() % 20000 + 5000;

    printf("\n=== Simulation of TCP Three-Way Handshake Connection ===\n");

    // Step 1: SYN from Client
    client_seq = client_isn;
    printf("\n[STEP 1] Client -> Server: [SYN flag set]\n");
    printf("          Sequence Number (Seq) = %d\n", client_seq);

    // Step 2: SYN-ACK from Server
    server_seq = server_isn;
    server_ack = client_seq + 1;
    printf("\n[STEP 2] Server -> Client: [SYN + ACK flags set]\n");
    printf("          Sequence Number (Seq) = %d | Acknowledgment Number (Ack) = %d\n", server_seq, server_ack);

    // Step 3: Final Handshake ACK from Client
    client_seq = server_ack;
    client_ack = server_seq + 1;
    printf("\n[STEP 3] Client -> Server: [ACK flag set]\n");
    printf("          Sequence Number (Seq) = %d | Acknowledgment Number (Ack) = %d\n", client_seq, client_ack);

    printf("\n>>> STATUS: Connection Established successfully (ESTABLISHED state) <<<\n");

    // Simulate simple data exchange segment transfers
    printf("\n--- Data Segment Transmission Phase ---\n");
    int payload_size = 250; // simulated byte size
    printf("Client sends a data stream segment of size %d bytes:\n", payload_size);
    printf("-> Packet Info: Seq = %d, Ack = %d\n", client_seq, client_ack);

    // Server acknowledges data block size update
    server_seq = client_ack;
    server_ack = client_seq + payload_size;
    printf("Server responds with standard Acknowledgment:\n");
    printf("<- Packet Info: Seq = %d, Ack = %d (Ready to receive next byte stream boundary)\n\n", server_seq, server_ack);

    return 0;
}
