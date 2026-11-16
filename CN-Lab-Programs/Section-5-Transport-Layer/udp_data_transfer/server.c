#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int port = DEFAULT_PORT;
    if (argc > 1) {
        port = atoi(argv[1]);
        if (port <= 0 || port > 65535) {
            printf("Error: Invalid port number. Using default port %d.\n", DEFAULT_PORT);
            port = DEFAULT_PORT;
        }
    }

    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    printf("============================================================\n");
    printf("                  UDP Server Active                         \n");
    printf("============================================================\n");
    printf("Server listening on 0.0.0.0:%d (UDP)...\n", port);
    printf("Waiting for datagrams from client...\n\n");

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = recvfrom(server_fd, buffer, sizeof(buffer) - 1, 0,
                                          (struct sockaddr *)&client_addr, &client_len);
        if (bytes_received < 0) {
            perror("recvfrom failed");
            break;
        }
        buffer[bytes_received] = '\0';

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
        int client_port = ntohs(client_addr.sin_port);

        printf("Received %zd bytes from [%s:%d]: \"%s\"\n", bytes_received, client_ip, client_port, buffer);

        if (strcmp(buffer, "exit") == 0 || strcmp(buffer, "quit") == 0) {
            printf("Exit signal received. Shutting down server.\n");
            const char *shutdown_ack = "Server shutting down. Goodbye!";
            sendto(server_fd, shutdown_ack, strlen(shutdown_ack), 0,
                   (const struct sockaddr *)&client_addr, client_len);
            break;
        }

        char ack_msg[BUFFER_SIZE + 64];
        snprintf(ack_msg, sizeof(ack_msg), "ACK: Received %zd bytes (\"%s\")", bytes_received, buffer);

        ssize_t bytes_sent = sendto(server_fd, ack_msg, strlen(ack_msg), 0,
                                    (const struct sockaddr *)&client_addr, client_len);
        if (bytes_sent < 0) {
            perror("sendto failed");
        } else {
            printf("Sent acknowledgment to [%s:%d]\n\n", client_ip, client_port);
        }
    }

    close(server_fd);
    printf("UDP Server closed successfully.\n");
    return 0;
}
