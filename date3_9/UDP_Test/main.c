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
    SEND_IS_ALIVE,
    IGNORED
} Is_Alive_t;

Is_Alive_t send_is_alive(int sock, struct sockaddr_in *server_addr);
Is_Alive_t send_is_alive_after(int sock, struct sockaddr_in *server_addr);

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


    struct timeval timeout;
    int retval;
    timeout.tv_sec = TIMEOUT_SEC;  // 2 seconds
    timeout.tv_usec = 0; // 0 microseconds
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("setsockopt failed");
        close(sock);
        exit(EXIT_FAILURE);
    }
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
                break;  // Break the loop to enter the child server code
            } else if (pid > 0) {
                // Parent process continues
                printf("Parent: Forked a child process with PID %d\n", pid);
                response = SEND_IS_ALIVE;
            } else {
                // Fork failed
                perror("Fork failed");
                exit(EXIT_FAILURE);
            }
        } else if (RESPONSE == response) {
            
        }else if(SEND_IS_ALIVE == response){
            response = send_is_alive_after(sock, &server_addr);
        }else if(IGNORED == response){
            
        }

    }

    if (pid == 0) { // Child process code
        int server_sock;
        struct sockaddr_in client_addr;
        char buffer[BUFFER_SIZE];
        socklen_t len = sizeof(client_addr);

        // Create a new UDP socket
        if ((server_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            perror("Child: Socket creation failed");
            exit(EXIT_FAILURE);
        }

        // Bind the socket to the server address
        if (bind(server_sock, (struct sockaddr *)&server_addr, addr_len) < 0) {
            perror("Child: Socket bind failed");
            close(server_sock); // Close the socket before exiting
            exit(EXIT_FAILURE);
        }

        printf("Child: Waiting for 'is_alive' message...\n");
        while (1) {   // Child process loop
            // Non-blocking wait for "is_alive" message from parent
            ssize_t received_bytes = recvfrom(server_sock, buffer, BUFFER_SIZE, MSG_DONTWAIT, (struct sockaddr *)&client_addr, &len);
            if (received_bytes < 0) {
                if (errno != EAGAIN && errno != EWOULDBLOCK) {
                    perror("Child: recvfrom() failed");
                }
            } else if (received_bytes > 0) {
                buffer[received_bytes] = '\0'; // Null-terminate the received string
                if (strcmp(buffer, "is_alive") == 0) {
                    printf("Child: Responding to 'is_alive' message.\n");
                    strcpy(buffer, "alive");
                    if (sendto(server_sock, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, len) < 0) {
                        perror("Child: Failed to send 'alive' response");
                    }
                }
                //break; // Exit the loop after handling the message
            }
        }

        close(server_sock); // Close the socket in the child before exiting
        exit(EXIT_SUCCESS); // Exit the child process
    }

    close(sock);
    return 0;
}

Is_Alive_t send_is_alive(int sock, struct sockaddr_in *server_addr) {
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(*server_addr);

    strcpy(buffer, "is_alive");

    sendto(sock, buffer, strlen(buffer), 0, (const struct sockaddr *)server_addr, addr_len);
    // Wait for a response with a timeout
    int n = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)server_addr, &addr_len);
    if (n < 0) {
        perror("recvfrom failed or timed out");
        printf("Return NO RESPONSE\n");
        return NO_RESPONSE;
    } else {
        // Response received
        printf("Return REPONSE\n");
        return RESPONSE;
    }
}
Is_Alive_t send_is_alive_after(int sock, struct sockaddr_in *server_addr){
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(*server_addr);
    printf("Enter the send_is_alive_after\n");

    strcpy(buffer, "is_alive");

    sendto(sock, buffer, strlen(buffer), 0, (const struct sockaddr *)server_addr, addr_len);
    // Wait for a response with a timeout
    int n = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)server_addr, &addr_len);
    if (n < 0) {
        perror("recvfrom failed or timed out");
        printf("Return SEND_IS_ALIVE\n");
        return SEND_IS_ALIVE;
    } else {

            buffer[n] = '\0'; // Null-terminate the string
            printf("Parent: Received message: %s\n", buffer);
            printf("\n");
            return IGNORED;
        
    }
}