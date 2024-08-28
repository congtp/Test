

## IPv4 Address
- there are 32 bits represent the ip address, so it is possible to have around 4 billions
addresses

## IPv6 Address
- Use 6 bytes

## Local IP Address
- Because, Nowadays, the components which need to use the Network is over 4 billions, 
so if we just use the IP Address, there is no way to allocate for these components.
- That 's the reason why the Global IP Address come into play.
- 

## Global IP Address
- To group the those local components, we will use the Global IP
- But in case of a LAN(Local Area Network) router, every port has its own Local IP Address,
So every components connects to the port of the LAN router will be marked with the specific
address.
- But , if these components want to communicate to outside, they will use these Global IP.

## Port 
- The computer use the Port Number to specify which Application will use this port.
- Example we have a App Gmail, it will receive a mail in the internet, so when the computer
receive the mail package from the internet, it will use this Port Number to specify the 
Application.

## Client and Server
- When 2 Application in the computer want to communicate with each other, there are some 
ways to achieve this, however, the popular Model are Client and Server
### Client
- The Client have to connect to the Server <actively>
- To connect to the Server, it has to know the IP of the Server
- When the Client know the IP, it will actively send the request connect to the Server
### Server
- Server acts as the actively Listener, so the Server dont care about the IP of the Client
- When has the request connect from the Client, Server will decide whether if accept or not
- If Server accept the connect, it will create a communication channel

#### 
- So when the communication channel is established, the package datas will be send on that
channel

# Socket
- Every embedded system have their own network system
- We can treat the socket like the door to go outside, every way want to go outside
has to through the socket.

## So What exactly is Socket?
- Socket can be thought of as an endpoint for communication between two devices over the
network. When we use the socket to write data from oneside, the data will be sent to 
the socket on the other side of the connection.
- Each side of the communication typically has its own socket, and they use these socket 
to send and receive data between them.

### Why Socket as an Endpoint?
- A Sockets acts as an endpoint in a network communication link. It represents one commucation
channel. Typically, there are two sockets involved in a communication session: one on a client
side, another on the serverside
### Communication Direction
- Data written to a socket by one application(e.g... client) is transmitted over network and received by the
socket on the other end (e.g ... server). This communication can be one-to-one (unicast). 
- Where data is sent to specific receiver, or it can be broadcast/multicast to multiple 
receivers.
### Why File-like behavior?
- Socket can behave similarly to file descriptors that you can read from or write to them 
using standard I/O operations. This is why they are often compared to file handles, as
both provide a way to handle streams of data

## So how to code with Socket?
- Because Socket is File-like behave, so we can treat it as the file, so how to manipulate with file?
  - we have to open the file (fopen):
  - choose that mode to will do with the file (fread, fwrite)
  - then fclose
- So with Socket we can do the same:
  - We have to create a socket  <int socket(int domain, int type, int protocol)>
    - <domain> will identify whether the socket will transmitter and receive internally, or 
    go outside the system. (Like TCP/IP, ...)
    - <type> identity what method is used to transmit
    - <protocol> identity the protocol will be used (TCP/IP, ...)
    - detailed can be serach in ___ Advanced Programing in the UNIX environment ___

### Notes about network:
- In network, they use the BigEndian to standard the data be sent in the network
- So that means any devices want to communicate by Network, have to translate its data to Big Endian
- There are some API support for these works:
  - in_addr_t inet_addr(const char *cp);  <this API will convert a string of IPv4 Address to network format>
    - prefer use int inet_aton(const char *cp, struct in_addr *inp) 
    <this API convert IPv4 Address and store it in struct in_addr>
    - because inet_addr has valid address is -1 which mean 255.255.255.255
  - uint32_t htonl(uint32_t hostint32)  <this API means convert host to network standard>
  - uint16_t ntohs(uint16_t netint16) <this API means convert network standard to host>

- So the sequence which may use to code the socket:
  - # 1 Open/Create the socket
    - We have to create a socket  <int socket(int domain, int type, int protocol)>
  - # 2 Create a Struct Sockaddr_in
    - struct sockaddr_in_server_addr:
      struct sockaddr_in {
          sa_family_t     sin_family;     /* AF_INET */ (AF_INET)
          in_port_t       sin_port;       /* Port number */ (htons(5000))
          struct in_addr  sin_addr;       /* IPv4 address */  (inet_addr("127.0.0.1"))
      };
  - # 3 Bind the address for the Socket
    - When we bind the address for the Socket, everytime we write a data to the socket,
    data will be packaged with the address of the socket.
      - int bind(int socketfd, const struct sockaddr* addr, socklen_t len);
      <socketfd: the socket we created> 
      <addr: the struct sockaddr we created>
      <len: length of the struct sockaddr>
  - # 4 Establish the communication
    ## From Client
      - The Client will use the API connect to sent a request connect to the Server
      - ___ int connect (int sockfd, struct sockaddr *addr, socklen_t length) ___
      <sockfd: the Client socket>
      <struct sockaddr: the Server IP addr, ...>
      - Because the Client will have to actively request a connect to the server so it must
      know the address of the Server
      - The Client will send a quest connect to the Server have the IP in the <struct sockaddr>
    ## From Server:
      - ___ int listen (int sockfd, int backlog) ___
      <sockfd: Server socket>
      <backlog: will determine the size of the waiting queue>
      - so whenever the Server receive the request connect, it will push it in the waiting queue
    ## IF the Server accept the request
      - So if the Server accept the request, it will use the API:
      - <new socket =  int accept(int sockfd, struct sockaddr *_Nullable restrict addr, socklen_t *_Nullable restrict addrlen); >
      - This API will create a <new socket> to communicate point-to-point the the Cilent
      ### From Server
        - Server will use write to write the data, and read to read the data from the <new socket> which created by the accept
        ___ ssize_t write(int fd, const void buf[.count], size_t count); ___
        <fd: new socket>

      ### From Client
        - Client will use the read to read the data from its socket
        ___ ssize_t read(int fd, void buf[.count], size_t count); ___
        <fd: old Client Socket>
    # 5 Both Client and Server can be close the socket the terminate the communicate


# Summary
## Steps to Program Socket on the Client and Server model
### From Client
  - <1>
    - Create Socket (socket())
  - <2>
    - Init <struct sockadd_in of the Server> with the IP_Address of the Server 
  - <3>
    - Bind the socket (bind())
  - <4> 
    - Request a connect to the Server (connect())

### From Server
  - <1>
    - Create a Socket (socket())
  - <2>
    - Init <struct sockadd_in of itself>
  - <3>
    - Bind the socket (bind())
  - <4>
    - Listen to the request connect (listen())
  - <5>
    - Determine whether it accept or not 
### When the communicate establish
  - <1>
    - The Server will create a new to socket to connect point-to-point with the Client (accept())
  - <2>
    - send the data (send())
  - <3>
    - read the data (read())
  - <4>
    - close the stream (close())
  