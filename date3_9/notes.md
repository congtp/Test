# Create a Client Socket (Parent Process)
## Parent Process
1) socket(AF_INET, SOCK_DGRAM, 0)   // IPv4, UDP 
2) Create Server Structure
3) setsockopt Timeout

while(1)
4) INIT
    - Send Message through socket
        - sendto(client_sock, buffer, buffer_size, option, struct server, sizeof(struct server))
        - revcfrom(client_sock, revbuff, buffer_size, option, struct server, sizeof struct server)
5) TIMEOUT
    - fork() new child
    - SEND_IS_ALIVE
    - break to the child loop
6) RECEIVED_ALIVE
    - MOVE TO SEND PACKAGE
7) SEND_PACKAGE
    - Do something


## Child Process

1) Create a new server socket
2) bind the address
while(1)
3) recvfrom(, , MSG_DONTWAIT, struct client, sizeof(struct clinet))   // MSG_DONTWAIT
4) MES_RECEIVE
    - strcmp("is_alive");
        - if equal:
            sendto(sock, transfer_buffer, size, option, struct client, len)



