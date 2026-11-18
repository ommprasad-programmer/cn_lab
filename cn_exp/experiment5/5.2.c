/*
PR5_2_TCPMessageExchange.c:
Program to simulate TCP message exchange that comprises of the following three phases:
(1) Connection establishment
(2) Data transfer, and
(3) Connection termination.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define packet structure
typedef struct
{
    int seq;
    int ack;
    char flags[8]; // SYN, ACK, FIN, DATA
    char data[1024]; // for user input
} TCPPacket;

void print_packet(const char *stage, TCPPacket p)
{
    printf("%s Packet -> [SEQ: %d, ACK: %d, FLAGS: %s", stage, p.seq, p.ack, p.flags);
    if (strcmp(p.flags, "DATA") == 0)
    {
        printf(", DATA: %s", p.data);
    }
    printf("]\n");
}

void connection_establishment()
{
    printf("\n=== TCP CONNECTION ESTABLISHMENT (3-WAY HANDSHAKING) ===\n");

    TCPPacket client, server;

    // Step 1: Client sends SYN
    client.seq = rand() % 1000;
    strcpy(client.flags, "SYN");
    print_packet("Client ->", client);

    // Step 2: Server replies with SYN+ACK
    server.seq = rand() % 1000;
    server.ack = client.seq + 1;
    strcpy(server.flags, "SYN-ACK");
    print_packet("Server ->", server);

    // Step 3: Client replies with ACK
    client.ack = server.seq + 1;
    strcpy(client.flags, "ACK");
    print_packet("Client ->", client);

    printf("Connection Established Successfully!\n");
}

void data_transmission()
{
    printf("\n=== TCP DATA TRANSMISSION ===\n");

    TCPPacket client, server;
    char buffer[1024];
    int packet_count, i;

    printf("Enter number of packets to send: ");
    scanf("%d", &packet_count);
    getchar(); // clear newline

    int base_seq = rand() % 5000;

    for (i = 0; i < packet_count; i++)
    {
        printf("Enter data for packet %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0; // remove newline

        // Client sends data
        client.seq = base_seq + i;
        client.ack = 0;
        strcpy(client.flags, "DATA");
        strcpy(client.data, buffer);
        print_packet("Client ->", client);

        // Server replies with ACK
        server.seq = rand() % 9000;
        server.ack = client.seq + 1;
        strcpy(server.flags, "ACK");
        print_packet("Server ->", server);
    }

    printf("All data sent and acknowledged successfully!\n");
}

void connection_termination()
{
    printf("\n=== TCP CONNECTION TERMINATION (4-WAY HANDSHAKING -AN EXTENSION OF 3-WAY HANDSHAKING-) ===\n");

    TCPPacket client, server;

    // Step 1: Client sends FIN
    strcpy(client.flags, "FIN");
    print_packet("Client ->", client);

    // Step 2: Server replies with ACK
    strcpy(server.flags, "ACK");
    print_packet("Server ->", server);

    // Step 3: Server sends FIN
    strcpy(server.flags, "FIN");
    print_packet("Server ->", server);

    // Step 4: Client replies with ACK
    strcpy(client.flags, "ACK");
    print_packet("Client ->", client);

    printf("Connection Terminated Successfully!\n");
}

int main()
{
    int choice;
    printf("\n=== TCP MESSAGE EXCHANGE (CONNECTION) SIMULATION ===\n");
    do
    {
        printf("\nMenu:\n1. Establish Connection\n2. Send Data\n3. Terminate Connection\n4. Exit\n\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                connection_establishment();
                break;
            case 2:
                data_transmission();
                break;
            case 3:
                connection_termination();
                break;
            case 4:
                printf("Exited Successfully.\n\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while(choice != 4);

    printf("\n");
    return 0;
}
