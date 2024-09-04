#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>

#define SERVER_PORT 9999
#define BUFFER_SIZE 1024
#define TIMEOUT_SEC 1

typedef enum {
    SELECT,
    NO_RESPONSE,
    RESPONSE,
    IGNORED
} Is_Alive_t;

Is_Alive_t send_is_alive(int sock, struct sockaddr_in *server_addr);

int main() {
    int sock;
    struct sockaddr_in server_addr;
    Is_Alive_t response = SELECT;
    char parent_buffer[BUFFER_SIZE];
    pid_t pid;
    socklen_t addr_len = sizeof(server_addr);

    // Create a UDP socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use localhost for testing

    // Main loop to send "is_alive" message
    while (1) {
        if (SELECT == response) {
            printf("go to SELECT\n");
            response = send_is_alive(sock, &server_addr);
            continue;
        } else if (NO_RESPONSE == response) {
            // Fork a new process if no response
            pid = fork();
            if (pid == 0) {
                // Child process acts as the server
                printf("Child process created\n");
                close(sock);  // Close the socket in the child before creating a new one
                if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                    perror("Child: Socket creation failed");
                    exit(EXIT_FAILURE);
                }
                // Configure server address for binding
                memset(&server_addr, 0, sizeof(server_addr));
                server_addr.sin_family = AF_INET;
                server_addr.sin_port = htons(SERVER_PORT);
                server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Bind to any available interface

                // Bind the socket to the server address
                if (bind(sock, (struct sockaddr *)&server_addr, addr_len) < 0) {
                    perror("Child: Socket bind failed");
                    close(sock); // Close the socket before exiting
                    exit(EXIT_FAILURE);
                }

                printf("Child: Waiting for 'is_alive' message...\n");
                while (1) {   // Child process loop
                    // Non-blocking wait for "is_alive" message from parent
                    ssize_t received_bytes = recvfrom(sock, parent_buffer, BUFFER_SIZE, MSG_DONTWAIT, (struct sockaddr *)&server_addr, &addr_len);
                    if (received_bytes < 0) {
                        if (errno != EAGAIN && errno != EWOULDBLOCK) {
                            perror("Child: recvfrom() failed");
                        }
                    } else if (received_bytes > 0) {
                        parent_buffer[received_bytes] = '\0'; // Null-terminate the received string
                        if (strcmp(parent_buffer, "is_alive") == 0) {
                            printf("Child: Responding to 'is_alive' message.\n");
                            strcpy(parent_buffer, "alive");
                            if (sendto(sock, parent_buffer, strlen(parent_buffer), 0, (struct sockaddr *)&server_addr, addr_len) < 0) {
                                perror("Child: Failed to send 'alive' response");
                            }
                        }
                        break; // Exit the loop after handling the message
                    }
                }

                close(sock); // Close the socket in the child before exiting
                exit(EXIT_SUCCESS); // Exit the child process
            } else if (pid > 0) {
                // Parent process continues
                printf("Parent: Forked a child process with PID %d\n", pid);
            } else {
                // Fork failed
                perror("Fork failed");
                exit(EXIT_FAILURE);
            }
        } else if (RESPONSE == response) {
            int bytes_received = recvfrom(sock, parent_buffer, BUFFER_SIZE - 1, 0, (struct sockaddr *)&server_addr, &addr_len);
            if (bytes_received < 0) {
                perror("Failed to receive message");
            } else {
                parent_buffer[bytes_received] = '\0'; // Null-terminate the string
                printf("Parent: Received message: %s\n", parent_buffer);
                response = IGNORED;
            }
        } else if (IGNORED == response) {
            // Optionally handle ignored state
        }
    }

    close(sock);
    return 0;
}

Is_Alive_t send_is_alive(int sock, struct sockaddr_in *server_addr) {
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(*server_addr);
    struct timeval timeout;
    fd_set readfds;
    int retval;

    // Send "is_alive" message to the server
    strcpy(buffer, "is_alive");
    if (sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)server_addr, addr_len) < 0) {
        perror("Failed to send message");
        return SELECT;
    }

    // Set up timeout for 1 second
    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = 0;

    // Initialize the file descriptor set
    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);

    // Wait for a response with a timeout
    retval = select(sock + 1, &readfds, NULL, NULL, &timeout);
    if (retval == -1) {
        perror("select()");
        printf("Return SELECT\n");
        return SELECT;
    } else if (retval == 0) {
        // Timeout: no response received
        printf("No response from server, forking a new process.\n");
        return NO_RESPONSE;
    } else {
        // Response received
        printf("Return RESPONSE\n");
        return RESPONSE;
    }
}
