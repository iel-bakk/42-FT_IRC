# 🌐 ft_IRC

**IRC :** stands for Internet Relay Chat. It's a protocol for real-time chat communication over the internet. It allows users to join chat rooms and have text-based conversations with other users in real-time. IRC has been around since the late 1980s and has been widely used for many years, although it has largely been supplanted by other chat platforms in recent years.

## Protocol 📜

IRC, an Application Layer protocol, is used by the World Wide Web (WWW). A protocol defines rules governing communication between entities. In the context of computer networking, it specifies how devices communicate over a network.

## WWW 🌐

"WWW" stands for World Wide Web, a system of interlinked hypertext documents accessed via the internet. It involves servers, computers, and devices allowing people to access and share information globally.

This project teaches network programming, socket programming, and the IRC protocol implementation in C++. It involves handling multiple clients simultaneously using multiple threads.

## IRC Network 🌐

**IRC nets** refer to collections of servers connected for Internet Relay Chat (IRC). Each IRC network has channels, rules, and user communities. Users connect to IRC networks using client software.

## EFnet 🚀

**EFnet**, one of the oldest IRC networks, operates as a decentralized network of servers. It offers extensive channel offerings, user communities, and supports various languages and topics.

## Channels 📢

In IRC, a **channel** is a virtual chat room where users communicate in real-time. Channels, public or private, facilitate group discussions on diverse topics.

## Create IRC Server 💻

Creating an IRC server involves selecting server software, setting up a server, installing the IRC server software, configuring the server, and testing it.

## Socket 🔗

A **socket** is a software structure facilitating communication between applications and network protocols. It serves as an endpoint for processes to communicate over a network.

## Network Programming 🌐

Network programming involves developing software for communication between devices over a network. It includes creating programs for web servers, email clients, online games, and file transfer.

## Usage Example 🚀

Here's a simplified example of client-side network programming in C++:

```cpp
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

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
