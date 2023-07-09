# 42-FT_IRC
# ft_IRC

**IRC :** stands for Internet Relay Chat. It's a protocol for real-time chat communication over the internet. It allows users to join chat rooms and have text-based conversations with other users in real-time. IRC has been around since the late 1980s and has been widely used for m any years, although it has largely been supplanted by other chat platforms in recent years.

**IRC:** Application Layer protocol used by the World Wide Web (WWW)

- **Protocol**
    
    a protocol is a set of rules or guidelines that governs the communication between two or more entities. In the context of computer networking, a protocol refers to a specific set of rules that defines how computers and other devices communicate with each other over a network.
    
    Computer networking protocols define the rules for how data is transmitted, received, and interpreted between devices. They specify the format of data packets, the order in which packets are sent and received, and how errors and other issues are handled.
    
    Some common networking protocols include TCP/IP, HTTP, FTP, and DNS. Each of these protocols defines specific rules and procedures for communication between devices, and they are used to ensure that devices can communicate with each other effectively and reliably over a network.
    

"WWW" stands for World Wide Web, which is a system of interlinked hypertext documents accessed via the internet. It is not just servers, but a network of servers, computers, and other devices that allow people to access and share information and resources across the globe.

This project is intended to teach students about network programming, socket programming, and the IRC protocol, as well as how to implement these concepts in C++. It also involves working with multiple threads to handle multiple clients simultaneously.

Generally, the user (such as you) runs a program (called a “client”) to connect to a server on one of the IRC nets. The server relays information to and from other servers on the same net. Recommended clients:

- [UNIX/Linux Clients](https://www.irchelp.org/clients/unix/)
    - [irssi](https://www.irchelp.org/irchelp/clients/unix/irssi/) - terminal-mode client
    - [xchat](https://www.irchelp.org/irchelp/clients/unix/xchat.html) - X11 (graphical) client
- [Windows Clients](https://www.irchelp.org/clients/windows/)
    - [mIRC](https://www.irchelp.org/irchelp/clients/windows/mirc/)
- [Macintosh clients](https://www.irchelp.org/clients/mac/)

# IRC Network :

**IRC nets**, or IRC networks, refer to collections of servers that are connected together to allow users to communicate with each other through the Internet Relay Chat (IRC) protocol. Each IRC network can have its own set of channels, rules, and user communities, and users can connect to them using an IRC client software. Some of the most popular IRC networks include Freenode, QuakeNet, and EFnet, among others. Each network has its own unique characteristics and features, but all share the common goal of enabling real-time communication between users around the world.

Once connected to an IRC server on an IRC network, you will usually join one or more “channels” and converse with others there. On EFnet, there often are more than 12,000 [channels](https://www.irchelp.org/irchelp/chanlist/), each devoted to a different topic. Conversations may be **public** (where everyone in a channel can see what you type) or **private** (messages between only two people, who may or may not be on the same channel).

**EFnet**, or Eris Free network, is one of the oldest and largest Internet Relay Chat (IRC) networks in existence. It was founded in 1990 as a fork of the original IRC network, and quickly grew in popularity due to its high capacity and open nature, attracting many users from around the world. EFnet operates as a decentralized network of servers, with no central authority or governance, and is known for its extensive channel offerings, user communities, and support for various languages and topics. While its usage has declined in recent years with the rise of newer chat and messaging platforms, it remains a popular choice for many IRC users, especially in certain niche communities.

In the context of Internet Relay Chat (IRC), a **channel** refers to a virtual chat room where users can communicate with each other in real-time. Channels are designated by names that begin with a '#' symbol (e.g., #music, #games, #news), and users can join them by typing the channel name into their IRC client software. Once in a channel, users can chat with each other, exchange files, share links, and participate in group discussions on a variety of topics. Channels can be public or private, depending on their settings, and can be moderated by one or more channel operators who have the ability to kick or ban users from the channel if necessary. Overall, channels are a central feature of IRC that allow users to connect with others who share similar interests and engage in online conversations in real-time.

Channel names usually begin with a #, as in #irchelp . The same channels are shared among all IRC servers on the same net, so you do not have to be on the same IRC server as your friends. (There are also channels with names beginning with a & instead of a #. These channels are not shared by all servers on the net but exist locally on that server only.)

The IRC protocol is a text-based communication protocol that was developed in the late 1980s as a way for people to communicate with each other in real-time over the internet.

- **Internet**
    
    In programming, the internet refers to a global network of computers and servers that communicate with each other using standard protocols and technologies. The internet allows computers and other devices to exchange data and information across geographical locations and time zones.
    
    From a programming perspective, the internet is used to create, develop, and deploy web applications and websites that are accessible through web browsers. This involves using various programming languages, frameworks, and technologies such as HTML, CSS, JavaScript, PHP, Python, Ruby on Rails, and many others.
    
    Programming for the internet involves developing software that interacts with remote servers and databases, retrieves data from various sources, and processes it to provide meaningful information to users. It also involves building user interfaces, designing APIs, and implementing security measures to protect sensitive information from unauthorized access.
    
    Overall, the internet has revolutionized the way we interact with technology, and programming for the internet has become an essential skill for software developers and programmers in today's digital age.
    

An **IRC serve**r acts as a central hub for the network of IRC clients and other servers that connect to it. When users connect to an IRC server, they can join channels or chat rooms, send private messages to other users, and share files and other information.

IRC servers typically have a number of built-in features, such as user authentication, access control, message logging, and various modes and settings that can be customized to suit the needs of the server's users. Some IRC servers are open to the public, while others may be restricted to specific groups or organizations.

### IRC Concepts

This section describes concepts behind the implementation and organisation of the IRC protocol, which are useful in understanding how it works.

### Architectural

A typical IRC network consists of servers and clients connected to those servers, with a good mix of IRC operators and channels. This section goes through each of those, what they are and a brief overview of them.

## Servers

Servers form the backbone of IRC, providing a point to which clients may connect and talk to each other, and a point for other servers to connect to, forming an IRC network.

The most common network configuration for IRC servers is that of a spanning tree [see the figure below], where each server acts as a central node for the rest of the network it sees. Other topologies are being experimented with, but right now there are none widely used in production.

There have been several terms created over time to describe the roles of different servers on an IRC network. Some of the most common terms are as follows:

- **Hub**: A ‘hub’ is a server that connects to multiple other servers. For instance, in the figure above, Server 2, Server 3, and Server 4 would be examples of hub servers.
- **Core Hub**: A ‘core hub’ is typically a hub server that connects fairly major parts of the IRC network together. What is considered a core hub will change depending on the size of a network and what the administrators of the network consider important. For instance, in the figure above, Server 1, Server 2, and Server 3 may be considered core hubs by the network administrators.

• **Leaf**: A ‘leaf’ is a server that is only connected to a single other server on the network. Typically, leafs are the primary servers that handle client connections. In the figure   above, Servers 7, 8, 10, 13, 14, and others would be considered leaf servers.

• **Services**: A ‘services’ server is a special type of server that extends the capabilities of the server software on the network (ie, they provide *services* to the network). Services are not used on all networks, and the capabilities typically provided by them may be built-into server software itself rather than being provided by a separate software package. Features usually handled by services include client account registration (as are typically used for *[SASL authentication](https://modern.ircdocs.horse/#authenticate-message)*), channel registration (allowing client accounts to ‘own’ channels), and further modifications and extensions to the IRC protocol. ‘Services’ themselves are **not** specified in any way by the protocol, they are different from the *[services](https://modern.ircdocs.horse/#services)* defined by the RFCs. What they provide depends entirely on the software packages being run.

# Network programming :

Network programming is the process of developing software applications that communicate with each other over a network. It involves the creation of programs that can send and receive data over a network connection, as well as the implementation of network protocols and communication standards.

Network programming can be used to create a wide range of applications, such as web servers, email clients, online games, and file transfer programs. These applications rely on networking protocols such as TCP/IP (Transmission Control Protocol/Internet Protocol), UDP (User Datagram Protocol), HTTP (Hypertext Transfer Protocol), and FTP (File Transfer Protocol) to enable communication between devices on the network.

To develop network programming applications, programmers must have a solid understanding of networking concepts, protocols, and communication standards. They must also be proficient in programming languages commonly used in network programming, such as C, C++, Python, and Java.

Overall, network programming plays a critical role in enabling communication and collaboration between devices on the network, making it a crucial aspect of modern computing.

According to the protocol specifications, an IRC network is a group of servers connected to each other. The simplest network is a single server. The network should have the form of a connected tree, in which each server is the central node for the rest of the network. A **client** is anything that is connected to the server, except for other servers. There are two types of customers:

- custom settings;
- service stations.

### Forwarding messages in the IRC network

IRC provides both group and private communication. There are several possibilities for group communication. A user can send a message to a list of users, and a list is sent to the server, the server selects individual users from it, and sends a copy of the message to each of them. More efficient is the use of channels. In this case, the message is sent directly to the server, and the server sends it to all users in the channel. In both group and private communication, messages are sent to clients via the shortest path and are visible only to the sender, recipient, and incoming servers. It is also possible to send a **broadcast message**. Client messages regarding changes in the network state (for example, channel mode or user status) must be sent to all servers that are part of the network. All messages originating from the server must also be sent to all other servers.

# Create IRC server :

Creating an IRC server can be a complex and involved process, and it requires a good understanding of server administration and networking. Here are some general steps that you can follow to create an IRC server:

1. Choose the IRC server software you want to use: There are many different IRC server software options available, such as ircd-hybrid, UnrealIRCd, InspIRCd, and more. Choose the one that best suits your needs and that you're most comfortable working with. (in This Project you need to program a IRC server)
2. Set up a server: You will need a computer or a virtual private server (VPS) with a stable internet connection to host your IRC server. You will also need to ensure that the server has enough resources to handle the number of clients you expect to connect.
3. Install the IRC server software: Follow the installation instructions for the software you've chosen. These will vary depending on the software you've chosen and the operating system you're running.
4. Configure your server: This involves setting up your server to handle connections from clients, configuring the server settings, and setting up any necessary channels or chat rooms.
5. Test your server: Once your server is configured, test it to make sure it's working correctly. Connect to the server using an IRC client, create a new channel, and ensure that you can send messages and that they're visible to other users.

Creating an IRC server is a complex process, and there are many factors to consider. If you're new to server administration or networking, it's recommended to seek out resources and guides that can help you get started. Additionally, it's important to ensure that you're aware of any legal and ethical considerations that may apply to running an IRC server.

# Socket :

**socket** is a software structure that provides an interface between applications and the network protocols, allowing communication between them.

a socket is an endpoint that allows different processes or programs to communicate over a network.

An endpoint can be any device that is capable of communicating over a network, such as a computer, smartphone, server, or router.

**endpoint** refers to a device or software application that is either the source or destination of data transmitted over a network.

Endpoints are often identified by their network address, such as an IP address or a domain name. When data is transmitted over a network, it is sent from one endpoint to another. For example, in a client-server architecture, a client endpoint may send a request to a server endpoint, which then processes the request and sends a response back to the client endpoint.

An endpoint can also refer to a process or service running on a device that listens for incoming requests or sends outgoing requests. For example, a web server can be considered an endpoint because it listens for incoming HTTP requests from clients and sends responses back to them.

In summary, an endpoint can refer to both a device and a process in the context of computer networking, depending on the specific usage and context.

Endpoints can communicate with each other using various protocols, such as TCP/IP, HTTP, FTP, and SMTP (Simple Mail Transfer Protocol). The choice of protocol depends on the type of communication and the specific requirements of the application.

A socket is identified by an IP address and a port number. An IP address is a unique identifier for a device on the network, and a port number is used to specify a particular application or process running on that device.

When an application needs to communicate over the network, it creates a socket and specifies the destination IP address and port number. The socket then establishes a connection with the destination socket, allowing data to be exchanged between the two applications.

Sockets allow communication between two different processes on the same or different machines. To be more precise, it's a way to talk to other computers using standard Unix file descriptors. In Unix, every I/O action is done by writing or reading a file descriptor. A file descriptor is just an integer associated with an open file and it can be a network connection, a text file, a terminal, or something else.

Sockets can be used for a variety of networking protocols, including TCP (Transmission Control Protocol) and UDP (User Datagram Protocol). They are a fundamental building block of network programming and are used extensively in client-server applications, such as web browsers, email clients, and online games.

To a programmer, a socket looks and behaves much like a **low-level file descriptor**. This is because commands such as read() and write() work with sockets in the same way they do with files and pipes.

- **file descriptor**
    
    the kernel's open file table is a system-wide resource, which means that all processes on the system share the same table. However, each process has its own set of file descriptors that refer to entries in the open file table, and these file descriptors are specific to each process.
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/bbce31c9-4d22-4697-8f00-e4426485b178/Untitled.png)
    

Sockets were first introduced in 2.1BSD and subsequently refined into their current form with 4.2BSD. The sockets feature is now available with most current UNIX system releases.

When two processes want to communicate, they each create a socket and specify the IP address and port number of the other endpoint. Once the sockets are created, the processes can exchange data using various protocols, such as TCP or UDP.

Sockets are used extensively in networking applications, such as web servers, email clients, and online games.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/78aed1d2-3103-4944-854d-b1f6833c26a0/Untitled.png)

## **Where is Socket Used?**

A Unix Socket is used in a client-server application framework. A server is a process that performs some functions on request from a client. Most of the application-level protocols like FTP, SMTP, and POP3 make use of sockets to establish connection between client and server and then for exchanging data.

## **Socket Types**

There are four types of sockets available to the users. The first two are most commonly used and the last two are rarely used.

Processes are presumed to communicate only between sockets of the same type but there is no restriction that prevents communication between sockets of different types.

- **Stream Sockets** −  Stream sockets are a type of communication protocol that is used for **reliable**, connection-oriented data transfer over a network. Stream sockets are implemented using the Transmission Control Protocol (TCP) in the Internet Protocol (IP) suite.
    
    Stream sockets provide a virtual, bidirectional byte stream between two endpoints in a network. The endpoints are identified by their IP address and port number. Stream sockets guarantee that data will be delivered in the order in which it was sent, and that no data will be lost or duplicated.
    
    With stream sockets, data is sent as a continuous stream of bytes, without any inherent message boundaries. The TCP protocol, which is used by stream sockets, ensures that data is transmitted reliably and in the correct order, even if packets are lost or arrive out of order.
    
    Stream sockets are widely used in client-server architectures, where a client process connects to a server process over a network and exchanges data. The client and server communicate by sending and receiving data in a stream of bytes, which is read and written to the socket as a continuous sequence of data. The socket API provides a set of functions for creating, binding, listening, accepting, connecting, reading, and writing data to stream sockets.
    
- **Datagram Sockets** −Datagram sockets, also known as UDP sockets, are a type of socket used for unreliable, connectionless communication between applications over a network. which does not provide any guarantees about whether data packets will arrive at their destination or arrive in the correct order. This makes datagram sockets more suitable for applications that require fast, low-latency communication, such as video and audio streaming, online gaming, and network discovery.
- **Raw Sockets** − These provide users access to the underlying communication protocols, which support socket abstractions. These sockets are normally datagram oriented, though their exact characteristics are dependent on the interface provided by the protocol. Raw sockets are not intended for the general user; they have been provided mainly for those interested in developing new communication protocols, or for gaining access to some of the more cryptic facilities of an existing protocol.
- **Sequenced Packet Sockets** − They are similar to a stream socket, with the exception that record boundaries are preserved. This interface is provided only as a part of the Network Systems (NS) socket abstraction, and is very important in most serious NS applications. Sequenced-packet sockets allow the user to manipulate the Sequence Packet Protocol (SPP) or Internet Datagram Protocol (IDP) headers on a packet or a group of packets, either by writing a prototype header along with whatever data is to be sent, or by specifying a default header to be used with all outgoing data, and allows the user to receive the headers on incoming packets.

**The key differences between datagram sockets and stream sockets are :**

- **Reliability**: Stream sockets provide reliable, ordered delivery of data, while datagram sockets provide unreliable, unordered delivery of data.
- **Connection-oriented vs connectionless**: Stream sockets are connection-oriented, meaning that a **connection must be established** before data can be exchanged, while datagram sockets are connectionless, meaning that data can be sent and received without any prior setup or teardown.
- **Packet size**: Stream sockets have no inherent message boundaries, meaning that data is sent as a continuous stream of bytes, while datagram sockets have a fixed maximum packet size, usually determined by the network protocol or hardware.
- **Overhead**: Stream sockets have more **overhead** than datagram sockets, since they require a three-way handshake to establish a connection, and use additional headers to ensure reliable delivery and ordering of data.

Datagram sockets can be created using the **socket**() system call in **Unix-like** operating systems, or the **WSASocket()** function in **Windows**. Once a socket is created, the application can use the sendto() and recvfrom() functions to send and receive datagrams, and close the socket when the communication is finished.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/17f2f317-144a-4a64-86c9-18222283d605/Untitled.png)

## ****State diagram for server and client model****

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/282d92c1-812b-42a1-8460-972a8b23251a/Untitled.png)

### Create Socket **:**

Creating a socket in a programming language requires different steps depending on the language and operating system you are using. However, a general overview of the steps involved in creating a socket:

1. **Create a socke**t: Use the socket() function in your programming language to create a socket. The function typically takes two arguments, **the address family** (such as AF_INET for IPv4 or AF_INET6 for IPv6) and **the socket type** (such as SOCK_STREAM for a stream socket or SOCK_DGRAM for a datagram socket).
2. **Bind the socket to an address and port**: Use the bind() function to associate the socket with a specific network address and port. This step is necessary for servers that are listening for incoming connections.
3. **Connect the socket**: If your application is a client that needs to connect to a server, use the connect() function to establish a connection to the server.
4. **Send and receive data**: Once the socket is created and connected, you can use functions such as send() and recv() to send and receive data over the network.
5. **Close the socket**: When your application is finished using the socket, use the close() function to release the socket resources and free up memory.

```jsx
int sockfd = socket(domain, type, protocol)
```

- **sockfd:** socket descriptor, an integer (like a file-handle)

In network programming, a socket descriptor is an integer value that uniquely identifies an open socket in a process. When a socket is created, the operating system assigns it a socket descriptor, which is used by the process to reference the socket in subsequent socket-related function calls, such as send(), recv(), connect(), listen(), and accept().

- **server**
    
    server can be considered as a program running on a computer. The server program runs continuously and waits for requests from clients, which it then responds to by providing the requested information or performing some action.
    
    A server program can be any software application that performs a specific task or provides a specific service, such as a web server, mail server, file server, database server, and so on. These programs are designed to operate in the background and provide a reliable and efficient service to clients, often running 24/7.
    
    However, it's worth noting that a server typically requires more resources than a regular program, such as processing power, memory, and network bandwidth, to handle a large number of requests and clients simultaneously. Servers may also have additional security features and monitoring tools to ensure their availability and protect them from cyber threats.
    

Socket descriptors are typically small, non-negative integer values, and they are managed by the operating system's kernel. When a process no longer needs a socket, it can close the socket descriptor, which releases any resources associated with the socket and makes the descriptor available for reuse.

- **domain:** integer, specifies communication domain. We use **AF_ LOCAL** as defined in the POSIX standard for communication between processes on the same host. For communicating between processes on different hosts connected by IPV4, we use **AF_INET** and AF_I NET 6 for processes connected by IPV6.
- **type:** communication type **SOCK_STREAM**: TCP(reliable, connection oriented)**SOCK_DGRAM**: UDP(unreliable, connectionless)
- **protocol:** Protocol value for Internet Protocol(IP), which is 0. This is the same number which appears on protocol field in the IP header of a packet.

The **`protocol`** parameter is an integer value that specifies the protocol to be used. The actual value passed to this parameter depends on the **`domain`** and **`type`** parameters used in the **`socket()`** function.

Here are some examples of protocols that can be specified in the **`socket()`** function:

- For **`AF_INET`** (IPv4) sockets with **`SOCK_STREAM`** type (TCP), the **`protocol`** parameter is typically set to **`IPPROTO_TCP`**.
- For **`AF_INET`** (IPv4) sockets with **`SOCK_DGRAM`** type (UDP), the **`protocol`** parameter is typically set to **`IPPROTO_UDP`**.
- For **`AF_UNIX`** (local) sockets with **`SOCK_STREAM`** type, the **`protocol`** parameter is typically set to **`0`** (default) since there is only one protocol defined for local sockets.
- For **`AF_INET6`** (IPv6) sockets, the **`protocol`** parameter can be set to **`IPPROTO_TCP`**, **`IPPROTO_UDP`**, or **`IPPROTO_IPV6`** depending on the desired protocol.

The **`protocol`** parameter is not always necessary as the default protocol for the given **`domain`** and **`type`** can be used by passing a value of **`0`**.

```cpp
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
```

- **`sys/socket.h`**: This library provides definitions and functions for working with sockets, including creating, binding, connecting, and closing sockets.
- **`netinet/in.h`**: This library provides definitions for the **`sockaddr_in`** struct and related functions for working with Internet protocol addresses.
- **`arpa/inet.h`**: This library provides functions for converting between network byte order and host byte order, and for working with Internet protocol addresses in string form.
- **`unistd.h`**: This library provides the **`close()`** function for closing file descriptors, including socket file descriptors.
- **`errno.h`**: This library provides access to the **`errno`** variable, which contains the last error code generated by a system call.
- **`stdlib.h`**: This library provides general-purpose functions such as memory allocation and string manipulation that are commonly used in socket programming.

```cpp
int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        std::cerr << "Failed to create socket.\n";
        return 1;
    }
```

This code creates a socket file descriptor using the socket() function. The code then checks if the socket was created successfully by checking if sockfd is equal to -1, which indicates an error.

```cpp
sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(12345);
server_addr.sin_addr.s_addr = INADDR_ANY;
if (bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
{
   std::cerr << "Failed to bind socket to address.\n";
   close(sockfd);
   return 1;
 }
```

This code creates a sockaddr_in struct that represents the server address and port to bind the socket to. The struct is initialized with the IP address and port number that the server should listen on. The code then calls the bind() function to bind the socket to the specified address and port. The function takes three arguments: the socket file descriptor, a pointer to a sockaddr struct that contains the server address and port, and the size of the struct. The code checks if the bind() function call was successful by checking if the return value is less than 0, which indicates an error.

The code I provided earlier creates a simple TCP server in C++ that listens for incoming connections from clients. When a client connects to the server, the server sends a welcome message to the client and then closes the connection.

In network programming, **`htons`** is a function that is used to convert a 16-bit integer from host byte order to network byte order.

Host byte order refers to the byte order used by the computer's CPU to store data in memory. The byte order can be either big-endian (most significant byte first) or little-endian (least significant byte first). Network byte order, on the other hand, is defined to be big-endian, which is the byte order used by most network protocols.The **`htons`**function takes a 16-bit integer value as an argument and returns the converted value in network byte order. If the host byte order is already big-endian, **`htons`**does nothing and returns the original value.

- **sockaddr_in**
    
    ```cpp
    struct sockaddr_in {
        short int sin_family;          // Address family (AF_INET)
        unsigned short int sin_port;   // Port number
        struct in_addr sin_addr;       // IP address
        unsigned char sin_zero[8];     // Padding to make the struct the same size as sockaddr
    };
    ```
    
    - **`sin_family`**: This field specifies the address family, which is always set to **`AF_INET`** for IP addresses.
    - **`sin_port`**: This field specifies the port number that the socket will be bound to. The port number is an unsigned 16-bit integer in network byte order.
    - **`sin_addr`**: This field specifies the IP address that the socket will be bound to. It is a struct of type **`in_addr`** that contains the IP address in network byte order.
    - **`sin_zero`**: This field is used to pad the struct to the same size as the **`sockaddr`** struct, which is used in other socket functions.

**`server_addr.sin_addr.s_addr = INADDR_ANY`** is a line of code used to set the IP address of a socket to a wildcard address, which means the socket can bind to any available IP address on the host machine.

The constant **`INADDR_ANY`**is defined in the header file **`netinet/in.h`**and represents a **wildcard IP address** that allows a server socket to bind to any available IP address on the host machine . When the **`sin_addr.s_addr`**field of the **`server_addr`**struct is set to **`INADDR_ANY`**, it means that the server socket can accept connections from any network interface or IP address of the host machine.

```cpp
if (listen(sockfd, 1) < 0) 
{
  std::cerr << "Failed to listen on socket.\n";
  close(sockfd);
  return 1;
}
```

**listen()** : is used to set up a passive socket that can accept incoming client connections. It takes two arguments: the socket file descriptor returned by socket() and the maximum number of connections that can be queued up for the server to handle. It tells the operating system that the socket is ready to receive incoming client connections.

The **`listen`** function is called on the server socket to enable the socket to accept incoming connections from clients.

This code sets the socket to listen for incoming connections using the listen() function. . When a client tries to connect to the server, the **`listen()`**function queues up the connection request and returns a socket file descriptor representing the connection.  The code checks if the listen() function call was successful by checking if the return value is less than 0, which indicates an error.

```cpp
while (true) 
{
  int client_sockfd = accept(sockfd, nullptr, nullptr);
  if (client_sockfd < 0) 
	{
    std::cerr << "Failed to accept incoming connection.\n";
    close(sockfd);
    return 1;
  }
  // Handle incoming connection
   std::cout << "Incoming connection accepted.\n";
   close(client_sockfd);
} 
```

This code waits for incoming connections using the accept() function This function is used to accept an incoming connection request from a client. When the server receives a connection request, it calls **`accept()`**to accept the request. When a connection is accepted, the function returns a new socket file descriptor that represents the connection. The code checks if the accept() function call was successful by checking if the return value is less than 0, which indicates an error. If the function call was successful, the code handles the incoming connection by performing any necessary actions. In this example, it simply prints a message to the console and closes the socket.

```cpp
close(sockfd);
    return 0;
}
```

This code closes the socket file descriptor when the program is finished using it.

```cpp
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    // Create a socket file descriptor
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Create a sockaddr_in struct for the server address and port
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Send a message to the server
    const char *message = "Hello, server!";
    send(sockfd, message, strlen(message), 0);

    // Receive a message from the server
    char buffer[1024] = {0};
    int bytes_received = recv(sockfd, buffer, 1024, 0);
    std::cout << "Received from server: " << buffer << std::endl;

    // Close the connection
    close(sockfd);

    return 0;
}
```

The `**connect()**` function is used in client-side network programming to establish a connection to a remote server. It has the following syntax:

```cpp
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

Here is what each argument does:

- **`sockfd`**: This is the file descriptor of the socket returned by the socket() function.
- **`addr`**: This is a pointer to a sockaddr structure that contains the IP address and port number of the remote server to connect to.
- **`addrlen`**: This is the length of the sockaddr structure.

The connect() function returns an integer value. If the connection is successful, it returns 0. Otherwise, it returns -1 and sets the **`errno`** variable to indicate the error.

The **`recv()`** function in network programming is used to receive data from a socket. It has the following syntax:

```cpp

#include <sys/types.h>
#include <sys/socket.h>
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

The **`sockfd`** parameter is the socket file descriptor returned by the **`socket()`** function. The **`buf`** parameter is a pointer to the buffer where the received data will be stored. The **`len`** parameter is the size of the buffer in bytes. The **`flags`** parameter is used to specify optional flags for the operation.

In a socket-based communication, **data** is transmitted between two endpoints using a stream of bytes. When data is sent through a socket, it is broken down into small pieces called packets, which are transmitted over the network to the receiving end.

Once the packets arrive at the receiving end, they are reassembled into the original data stream. The socket then makes the received data available to the application by storing it in a **buffer**.

The **buffer** is a temporary storage area used by the socket to hold the data received from the network until the application is ready to process it. The size of the buffer can be configured by the application when the socket is created, using the **`setsockopt()`**system call.The application can retrieve the data from the socket buffer using a system call such as **`recv()`**or **`recvfrom()`**. These functions allow the application to read data from the socket buffer and process it as needed. Once the data has been read from the buffer, the socket buffer is cleared, and new data can be stored in it.

It's worth noting that the socket buffer is a finite resource, and if the application does not read data from the socket buffer quickly enough, the buffer may become full, resulting in the loss of incoming data. Therefore, it's important for the application to read data from the socket buffer in a timely manner to avoid losing data.

The **`recv()`**function blocks until data is available to be received. When data is received, the function returns the number of bytes received, which may be less than the requested **`len`**. A return value of 0 indicates that the remote side has closed the connection.

 **`read()`**  is a system call in Unix and Unix-like operating systems that is used to read data from a file descriptor. It takes three arguments: the file descriptor to read from, a buffer to store the data read, and the number of bytes to read.

In network programming, the **`read`** function can be used to read data from a socket file descriptor. However, it is more common to use the **`recv`** function instead, as it provides more options for handling network errors and protocol-specific data.

The **`read`** function returns the number of bytes read, which may be less than the number of bytes requested if the end of file is reached or if an error occurs. It can be used in conjunction with other system calls, such as **`select`** or **`poll`**, to wait for data to become available before reading from a socket.

**`write()`** function is a system call in Unix and Unix-like operating systems that is used to write data to a file descriptor. It takes three arguments: the file descriptor to write to, a buffer containing the data to be written, and the number of bytes to write.

In network programming, the **`write`** function can be used to send data over a socket file descriptor. However, it is more common to use the **`send`** function instead, as it provides more options for handling network errors and protocol-specific data.

The **`write`** function returns the number of bytes written, which may be less than the number of bytes requested if an error occurs. It can be used in conjunction with other system calls, such as **`select`** or **`poll`**, to ensure that all data is written before continuing to the next operation.

The **`inet_pton`**function is used to convert an IPv4 or IPv6 address from a text string format to a binary format that can be used in network programming. It takes two arguments: the address family (either **`AF_INET`**for IPv4 or **`AF_INET6`**for IPv6), and a pointer to the text string containing the address.

- **file descriptors in non-blocking**
    
    File descriptors are numerical identifiers that are used by operating systems to access and manipulate files or other input/output (I/O) resources, such as sockets or pipes.
    
    Non-blocking I/O refers to a mode of operation where the I/O operations do not block the execution of the program. This means that the program can continue to execute while it waits for I/O operations to complete.
    
    In the context of non-blocking I/O, file descriptors are typically used to monitor the status of I/O operations. When a file descriptor is set to non-blocking mode, any read or write operation on that descriptor will return immediately with an error code if there is no data available to be read or if the output buffer is full.
    
    To avoid blocking on I/O operations, programs can use functions like **`select`**, **`poll`**, or **`epoll`** to monitor the status of multiple file descriptors simultaneously and perform I/O operations only when data is available. By using non-blocking I/O and file descriptors, programs can achieve higher performance and better scalability.
    
    The program can then continue executing other tasks, while periodically checking the status of the non-blocking socket to determine if the operation has completed.
    
    In a non-blocking socket, when an I/O operation is initiated (e.g., **`send()`**or **`recv()`**), the function immediately returns with a result indicating whether the operation was successfully initiated or not, without waiting for the operation to complete
    

## **nc command :**

The **`nc`**(or "netcat") command in Linux is a powerful utility that allows you to perform various networking tasks such as creating TCP/UDP connections, sending and receiving data over the network, port scanning, and more.

Here are some common use cases of the **`nc`** command in Linux:

- Creating a simple network server to listen for incoming connections and data
- Connecting to a remote server or service and sending data
- Port scanning to check which ports are open on a network host
- Proxying network connections to a different host or port
- Transferring files between two hosts over a network using the **`nc`** file transfer mode (**`nc -l [port] > [file]`** on the receiving end and **`nc [host] [port] < [file]`** on the sending end)

**`nc`** can act as both a server and a client.

As a server, **`nc`** can listen on a specific port for incoming connections and data. You can start a simple TCP server with the following command:

```
nc -l [port]
```

This will listen on the specified **`[port]`** for incoming TCP connections. Once a connection is established, you can communicate with the connected client by typing in the terminal.

As a client, **`nc`** can connect to a remote server or service and send data. You can establish a TCP connection to a remote server with the following command:

```
nc [host] [port]
```

This will connect to the specified **`[host]`** and **`[port]`** and allow you to send data to the remote server.

```cpp
nc -c localhost 6667
```

When you use **`nc -c localhost 6667`**, **`nc`**creates a TCP connection to the **`localhost`** host on port **`6667`**. The **`-c`** option tells **`nc`** to close the connection when the input ends.

Once the TCP connection is established, **`nc`**will send any input from standard input to the remote host through the socket. If the remote host sends any data back, **`nc`** will display it on standard output. Since the **`-c`** option is used, the connection will be closed when the input ends (i.e., when you press **`Ctrl+D`**
 to signal the end of input).

In addition to the default port number **`6667`**, IRC servers may also use other port numbers, such as **`6660`**to **`6669`**, **`7000`**, or **`8000`**. Some IRC networks may also use SSL/TLS encryption to secure the IRC communication, in which case the server port number would be different, such as **`6697`**.

## Poll function :

The **`poll()`** function is a system call that is used in C++ and other programming languages to monitor multiple file descriptors for events, such as incoming data, end-of-file conditions, and errors. The **`poll()`** function is part of the POSIX standard and is used for I/O multiplexing, which allows multiple I/O operations to be performed in a single thread.

Here are some reasons why you might choose to use **`poll()`** instead of **`read()`** and **`write()`**:

1. **`poll()`** allows you to monitor multiple file descriptors at once: Unlike **`read()`** and **`write()`**, which only work with a single file descriptor at a time, **`poll()`** can be used to monitor multiple file descriptors simultaneously. This makes it useful in applications that need to handle multiple connections or events at once.
2. **`poll()`** can wait for multiple events: **`poll()`** can be used to wait for multiple events on a file descriptor, such as reading, writing, or error events. This allows an application to monitor for different types of events without having to use separate functions like **`select()`** or **`epoll()`**.
3. **`poll()`** can avoid busy-waiting: Busy-waiting, where an application repeatedly checks for events on a file descriptor without sleeping or waiting, can be inefficient and waste CPU resources. **`poll()`** can be used to wait for events without busy-waiting, allowing the application to be more efficient.
4. **`poll()`** can be used with timeouts: **`poll()`** can be called with a timeout value, which causes it to wait for a specified amount of time before returning. This can be useful in applications that need to periodically check for events, but don't want to wait indefinitely.
5. **`poll()`** can be used with non-blocking file descriptors: **`poll()`** can be used with non-blocking file descriptors, allowing an application to monitor for events without blocking on I/O operations. This can be useful in applications that need to handle I/O operations asynchronously.

The **`poll`**function takes an array of **`struct pollfd`**structures, which specify the file descriptors to monitor and the events to wait for. The function blocks until one or more of the specified events occur, or until a timeout expires.

In **`ft_irc`** project, you use the **`poll()`** function to monitor multiple sockets for incoming data. When a socket is ready to be read, the **`poll()`** function will return with the appropriate event flag set, and you can then read the incoming data from the socket.

```cpp
#include <iostream>
#include <poll.h>
#include <unistd.h>

int main() {
    // Create an array of pollfd structures
    const int num_fds = 2;
    struct pollfd fds[num_fds];

    // Set up the first file descriptor to monitor for incoming data
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    // Set up the second file descriptor to monitor for incoming data
    fds[1].fd = socket_fd;
    fds[1].events = POLLIN;

    // Wait for data to be available on either file descriptor
    const int timeout_ms = -1;
    const int result = poll(fds, num_fds, timeout_ms);
    if (result < 0) {
        std::cerr << "poll() failed\n";
        return 1;
    }

    // Check which file descriptor has data available
    if (fds[0].revents & POLLIN) {
        std::cout << "Data is available on STDIN\n";
        // Read the data from STDIN
        // ...
    }

    if (fds[1].revents & POLLIN) {
        std::cout << "Data is available on socket_fd\n";
        // Read the data from socket_fd
        // ...
    }

    return 0;
}
```

In this example, the **`poll()`**function is used to monitor two file descriptors: **`STDIN_FILENO`**and **`socket_fd`**. The **`POLLIN`**event flag is set for each file descriptor, which means that the **`poll()`**function will return when there is data available to be read.(it waits for one of set of file descriptors to become ready to perform I/O.)

The **`poll()`**function blocks until data is available on one of the file descriptors or the specified timeout expires. When the function returns, you can check the **`revents`**field of each **`pollfd`**structure to determine which file descriptor has data available.

In the **`poll`**function, the **`revents`**field in each **`pollfd`**structure is used to indicate which events have occurred for a particular file descriptor. The **`revents`**field is a bit mask that can have one or more of the following values:

- **`POLLIN`**: Data is available to be read from the file descriptor.
- **`POLLOUT`**: Data can be written to the file descriptor without blocking.
- **`POLLERR`**: An error occurred on the file descriptor.
- **`POLLHUP`**: The file descriptor has been hung up (the remote end has closed the connection).
- **`POLLNVAL`**: The file descriptor is not open or is not valid.

When the **`poll`** function returns, the program can check the **`revents`** field in each **`pollfd`** structure to determine which events occurred for each file descriptor that was being monitored.

For example, if **`fds[0].revents & POLLIN`** is true, it means that data is available to be read from the file descriptor **`fds[0].fd`**. If **`fds[1].revents & POLLOUT`** is true, it means that data can be written to the file descriptor **`fds[1].fd`** without blocking.

In the **`poll`** function, **`POLLIN`** is a flag that is used to indicate that there is data available to be read from a file descriptor without blocking.

When a file descriptor is monitored for **`POLLIN`** events, it means that the program is interested in knowing when data becomes available to be read from that file descriptor. This is typically used for reading from sockets, pipes, or other input streams.

 **`int ret = poll(this->fds, num_fds, -1);`**: This line calls the **`poll()`** function to wait for events on the file descriptors being monitored. The **`-1`** parameter indicates that **`poll()`** should wait indefinitely until an event occurs.

**`if (this->fds[i].fd == this->sockfd)` :** 

## Setsockopt function :

**`setsockopt`** function **allows you to set various options for a socket**, such as the socket's level, the option name, and the option value. The level parameter specifies the protocol level at which the option resides, and the option name parameter identifies the specific option to be set. The option value parameter specifies the new value to be set for the option.

The **`SO_REUSEPORT`**option is similar to the **`SO_REUSEADDR`**option, but it **allows multiple sockets to bind to the same IP address and port number**. With **`SO_REUSEPORT`**, each socket receives incoming connections in a round-robin fashion, spreading the load among the sockets.

```cpp
#include <sys/socket.h>
#include <netinet/in.h>

int sockfd = socket(AF_INET, SOCK_STREAM, 0);
int reuseport = 1;
setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &reuseport, sizeof(reuseport));

struct sockaddr_in servaddr;
memset(&servaddr, 0, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(8080);
bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
```

In this example, the **`SO_REUSEPORT`**option is set on the **`sockfd`**socket using **`setsockopt`**. Then, a **`struct sockaddr_in`**is initialized to represent the server's address and port number. Finally, the **`bind`**function is called to bind the socket to the specified port number. With **`SO_REUSEPORT`**set, multiple sockets can bind to the same port number and receive incoming connections in a round-robin fashion.

```cpp
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
```

The parameters are:

- **`sockfd`**: the socket file descriptor to set the option on.
- **`level`**: the protocol level at which the option resides. This is typically one of the socket option levels defined in the **`sys/socket.h`** header file, such as **`SOL_SOCKET`** or **`IPPROTO_TCP`**.
- **`optname`**: the specific option to be set. This is typically one of the socket options defined in the **`sys/socket.h`** header file, such as **`SO_REUSEADDR`** or **`SO_KEEPALIVE`**.
- **`optval`**: a pointer to the new value to be set for the option.
- **`optlen`**: the size of the new option value.

## message format :

The IRC protocol is text-based and uses a simple message format. Each message consists of a prefix, a command, and zero or more parameters, separated by spaces and terminated by a carriage return and line feed (CRLF) sequence.

Here's an example of an IRC message:

```cpp
:irc.example.com PRIVMSG #channel :Hello, world!
```

In this example, the message consists of:

- **Prefix**: the server or user that sent the message. In this case, the server **`irc.example.com`** is the sender.
- **Command**: the action that the client wants the server to perform. In this case, the command is **`PRIVMSG`**, which is used to send a message to a channel or user.
- **Parameters**: additional information that the server needs to perform the action. In this case, there are two parameters:
    - #channel: the channel that the message is being sent to.
    - Hello, world!: the text of the message itself.

When the server receives the message, it processes it based on the command and parameters, and sends back a response, which can also be an IRC message.

For example, if the client sends the **`NICK`**command to change their nickname, the server might respond with a **`NICK`**message to confirm the change:

```cpp
:NICKNAME!user@host NICK new_nickname
```

In this example, the message consists of:

- **Prefix**: the old nickname of the client, followed by the user and host information.
- **Command**: **`NICK`**, indicating that the client's nickname has been changed.
- **Parameter**: the new nickname that the client has changed to.

To extract the prefix, command, and parameters from the received message, you need to parse the string that you received.

One way to do this is to split the message into its components using a delimiter, such as a space character. You can then extract the prefix, command, and parameters from the resulting tokens.

```cpp
// Assuming that the received message is stored in the 'message' variable
std::string prefix, command;
std::vector<std::string> params;

// Split the message into tokens using a space delimiter
std::istringstream iss(message);
std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>{}};

// Extract the prefix, command, and parameters from the tokens
if (!tokens.empty()) {
    if (tokens[0][0] == ':') {
        prefix = tokens[0].substr(1); // Remove the colon from the prefix
        tokens.erase(tokens.begin()); // Remove the prefix from the tokens
    }
    if (!tokens.empty()) {
        command = tokens[0];
        tokens.erase(tokens.begin()); // Remove the command from the tokens
    }
    if (!tokens.empty()) {
        params = tokens;
    }
}
```

**more details :** 

https://www.bogotobogo.com/cplusplus/sockets_server_client.php 

https://datatracker.ietf.org/doc/html/rfc2812

https://modern.ircdocs.horse/#client-to-server-protocol-structure

https://beej.us/guide/bgnet/html/
