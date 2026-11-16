#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define DEFAULT_SERVER_IP "127.0.0.1"
#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    const char *server_ip = DEFAULT_SERVER_IP;
    int port = DEFAULT_PORT;

    if (argc > 1) {
        server_ip = argv[1];
    }
    if (argc > 2) {
        port = atoi(argv[2]);
        if (port <= 0 || port > 65535) {
            printf("Error: Invalid port number. Using default port %d.\n", DEFAULT_PORT);
            port = DEFAULT_PORT;
        }
    }

    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        printf("Error: Invalid server IP address '%s'.\n", server_ip);
        close(client_fd);
        return 1;
    }

    printf("============================================================\n");
    printf("                  UDP Client Active                         \n");
    printf("============================================================\n");
    printf("Target server: %s:%d\n", server_ip, port);
    printf("Type messages to send to server (type 'exit' to quit):\n\n");

    char send_buffer[BUFFER_SIZE];
    char recv_buffer[BUFFER_SIZE];
    socklen_t server_len = sizeof(server_addr);

    while (1) {
        printf("Enter message: ");
        if (fgets(send_buffer, sizeof(send_buffer), stdin) == NULL) {
            break;
        }

        size_t len = strlen(send_buffer);
        if (len > 0 && send_buffer[len - 1] == '\n') {
            send_buffer[len - 1] = '\0';
        }

        if (strlen(send_buffer) == 0) {
            continue;
        }

        ssize_t bytes_sent = sendto(client_fd, send_buffer, strlen(send_buffer), 0,
                                    (const struct sockaddr *)&server_addr, server_len);
        if (bytes_sent < 0) {
            perror("sendto failed");
            break;
        }

        memset(recv_buffer, 0, sizeof(recv_buffer));
        ssize_t bytes_received = recvfrom(client_fd, recv_buffer, sizeof(recv_buffer) - 1, 0,
                                          (struct sockaddr *)&server_addr, &server_len);
        if (bytes_received < 0) {
            perror("recvfrom failed");
            break;
        }
        recv_buffer[bytes_received] = '\0';

        printf("Server Response: \"%s\"\n\n", recv_buffer);

        if (strcmp(send_buffer, "exit") == 0 || strcmp(send_buffer, "quit") == 0) {
            break;
        }
    }

    close(client_fd);
    printf("UDP Client closed successfully.\n");
    return 0;
}
