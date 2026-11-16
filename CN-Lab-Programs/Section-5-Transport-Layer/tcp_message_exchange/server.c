#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define DEFAULT_PORT 8081
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

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(server_fd);
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        return 1;
    }

    printf("============================================================\n");
    printf("                  TCP Server Active                         \n");
    printf("============================================================\n");
    printf("Server listening on 0.0.0.0:%d (TCP)...\n", port);
    printf("Waiting for incoming client connection...\n\n");

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket < 0) {
        perror("Accept failed");
        close(server_fd);
        return 1;
    }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
    int client_port = ntohs(client_addr.sin_port);
    printf("Connected to client at [%s:%d]\n\n", client_ip, client_port);

    char buffer[BUFFER_SIZE];

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

        if (bytes_received < 0) {
            perror("recv failed");
            break;
        }
        if (bytes_received == 0) {
            printf("Client disconnected gracefully.\n");
            break;
        }

        buffer[bytes_received] = '\0';
        printf("Client: \"%s\"\n", buffer);

        if (strcmp(buffer, "exit") == 0 || strcmp(buffer, "quit") == 0) {
            printf("Exit requested by client. Terminating session.\n");
            const char *bye_msg = "Goodbye!";
            send(client_socket, bye_msg, strlen(bye_msg), 0);
            break;
        }

        char server_reply[BUFFER_SIZE + 64];
        snprintf(server_reply, sizeof(server_reply), "Server Echo: %s", buffer);

        ssize_t bytes_sent = send(client_socket, server_reply, strlen(server_reply), 0);
        if (bytes_sent < 0) {
            perror("send failed");
            break;
        }
    }

    close(client_socket);
    close(server_fd);
    printf("TCP Server closed successfully.\n");
    return 0;
}
