#include "../Classes/Server.hpp"

Server:: Server()
{
    Message();
}
Server:: ~Server()
{
}
Server:: Server(int port, std:: string password): port(port), password(password)
{
}
Server:: Server(std:: string localhost, int port, std:: string password)
{
    this->localhost  = localhost;
    this->port = port;
    this->password = password;
}

int Server:: get_sockfd(void)
{
    return (this->sockfd);
}

int Server:: get_client_length(void)
{
    return (this->client_lenght);
}

int Server:: get_Port(void)
{
    return (this->port);
}

std:: string Server:: get_Password(void)
{
    return (this->password);
}

int Server:: get_new_socket_fd(void)
{
    return (this->new_socket_fd);
}

void Server:: create_socket(void)
{
    int reuseport = 1;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd == -1)
        std:: cout << "Error: socket not created" << std:: endl;
    setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEPORT, &reuseport, sizeof(reuseport));
}

void Server:: bind_socket(void)
{
    memset((char*)&this->socker_addr, 0, sizeof(this->socker_addr));
    this->socker_addr.sin_family = AF_INET;
    this->socker_addr.sin_port = htons(this->port);
    this->socker_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(this->sockfd, (struct sockaddr *)&this->socker_addr, sizeof(this->socker_addr)) < 0)
    {
        std:: cout << "Failed to Bind the socket." << std:: endl;
        close (this->sockfd);
    }
}

void Server:: listen_socket(void)
{
    if (listen(this->sockfd, 5) < 0)
    {
        std:: cout << "Error: Failed to listen on socket." << std:: endl;
        close (this->sockfd);
    }
}

void Server:: accept_socket(void)
{
    size_t size;
    int num_fds;
    int count;
    int sock;
    int num;
    int check;
    std:: vector<std:: string> new_user;

    size = sizeof(this->socker_addr);
    memset(this->fds, 0, max_num_fds * sizeof(struct pollfd));
    this->fds[0].fd = this->sockfd;
    this->fds[0].events = POLLIN;
    num_fds = 1;
    count = 0;
    while (true)
    {
        int ret = poll(this->fds, num_fds, -1);
        if (ret < 0)
        {
            std:: cout << "Error: Poll not Created" << std:: endl;
            exit (-1);
        }
        for (int i = 0; i < num_fds; i++)
        {
            if (this->fds[i].revents & POLLIN)
            {
                if (this->fds[i].fd == this->sockfd)
                {
                    this->new_socket_fd = accept(this->sockfd, (struct sockaddr *)&this->socker_addr, (socklen_t *)&size);
                    if (this->new_socket_fd < 0)
                    {
                        std:: cout << "Failed to accept incoming connection\n" << std:: endl;
                        close (this->sockfd);
                        exit(0);
                    }
                    if (num_fds >= max_num_fds)
                        close (this->new_socket_fd);
                    else
                    {
                        std:: cout << "connection accepted" << std:: endl;
                        this->fds[num_fds].fd = this->new_socket_fd;
                        this->fds[num_fds].events = POLLIN;
                        num_fds++;
                        Message my_message(this->new_socket_fd);
                        this->file_vectors[count] = my_message;
                        count++;
                    }
                }
                else
                {
                    sock = this->fds[i].fd;
                    my_place = i - 1;
                    read_write_socket(sock, &num_fds, &this->file_vectors[my_place]);
                    if (my_place != 0)
                    {
                        if (this->file_vectors[my_place].get_my_user().size() != 0)
                        {
                                for (int i= 0; i != my_place; i++)
                                {
                                    if (this->file_vectors[i].get_my_user() == this->file_vectors[my_place].get_my_user())
                                    {
                                        std:: string _message = "436 ERR_NICKCOLLISION " + this->file_vectors[my_place].get_my_user() +  " :Nickname collision KILL\r\n";
                                        num = display_message(this->file_vectors[my_place].get_socket(), _message);
                                        this->file_vectors[my_place].erase_user();
                                    }
                                    check = HandleError(this->file_vectors[my_place].send_Message_identification(), this->file_vectors[my_place].get_socket());
                                }
                        }
                    }
                    else
                            check = HandleError(this->file_vectors[my_place].send_Message_identification(), this->file_vectors[my_place].get_socket());
                }
            }
        }
    }
}

void Server:: read_write_socket(int sockfd, int *num_fds, Message *new_user)
{
    int n;
    int check;
    char buffer[511];
    std:: string tab;

    bzero(buffer, 511);
    n = recv(sockfd, buffer, 510, 0);
    check = 0;
    if (n < 0)
    {
        std:: cout << "Error: Reading From Socket" << std:: endl;
        exit(1);
    }
    if (n == 0 || !strcmp(buffer, "QUIT Leaving...\r\n"))
    {
        (*num_fds)--;
        n = HandleError(check = 11, sockfd);
        return ;
    }
    tab = buffer;
    if (check_ctrl_D(tab))
        check = new_user->parse_message(this->password, this->_buffer);
    n = HandleError(check, sockfd);
    if (n < 0)
    {
        std:: cout << "Error: Writing From Socket" << std:: endl;
        exit(1);
    }
}

void Server:: send_socket(void)
{
    if (send(this->new_socket_fd, this->message, strlen(this->message), 0) < 0)
    {
        std:: cout << "Error: Message don't send" << std:: endl;
    }
}

int Server:: HandleError(int error_replies, int sockfd)
{
    int num = 0;
    std:: string handle_message;
    std:: string _message;

    switch (error_replies)
    {
        case 10:
            std:: cout << "Not Numeric" << std:: endl;
            break;
        case 11:
            close_socket(this->file_vectors[my_place].get_socket());
            break;
        case 12:
            std:: cout << "Invalid Command" << std:: endl;
            break;
        case 13:
            num = write_long_message(sockfd);
            break;
        case 14:
            num = send_private_message();
            break;
        case 412:
            num = write(sockfd, "412 ERR_NOTEXTTOSEND :No text to send\r\n", 39);
            break;
        case 431:
            num = write(sockfd, "431 ERR_NONICKNAMEGIVEN:No nickname given\r\n", 43);
            break;
        case 432:
            _message = "432 ERR_ERRONEUSNICKNAME " + this->file_vectors[my_place].get_my_user() +  " :Erroneous nickname\r\n";
            num = display_message(sockfd, _message);
            break;
        case 436:
            _message = "436 ERR_NICKCOLLISION " + this->file_vectors[my_place].get_my_user() +  " :Nickname collision KILL\r\n";
            num = display_message(sockfd, _message);
            break;
        case 451:
            num = write(sockfd, "451 ERR_NOTREGISTERED:You have not registered\r\n", 47);
            break;
        case 464:
            num = write(sockfd, "464 ERR_PASSWDMISMATCH:Password incorrect\r\n", 43);
            break;
        case 461:
            num = display_error();
            break;
        case 462:
            num = write(sockfd, "462 ERR_ALREADYREGISTRED USER :Unauthorized command (already registered)\r\n", 74);
            break;
        default:
            break;
    }
    return (num);
}

void Server:: close_socket(int socket)
{
    std:: cout << "Client is DISCONNECTED" << std:: endl;
    close(socket);
    this->file_vectors.erase(my_place);
}

int Server:: write_long_message(int sockfd)
{
    int num;

    num = 0;
    std:: string message;

    message = this->file_vectors[my_place].get_welcome_message() + "\r\n";
    if (message.size() != 0)
        num = display_message(sockfd, message);
    message = this->file_vectors[my_place].get_host_message() + "\r\n";
    if (message.size() != 0)
        num = display_message(sockfd, message);
    message = this->file_vectors[my_place].get_server_message() + "\r\n";
    if (message.size() != 0)
        num = display_message(sockfd, message);
    
    return (num);
}

int Server:: send_private_message(void)
{
    int num = 0;
    std:: string message;

    for (size_t i = 0; i != this->file_vectors.size(); i++)
    {
        if (this->file_vectors[i].get_my_user() == this->file_vectors[my_place].get_user_to_send())
        {
            message = ":" + this->file_vectors[my_place].get_my_user() + this->file_vectors[my_place].get_notice_private() + this->file_vectors[i].get_my_user() + " :" + this->file_vectors[my_place].get_message_to_send() + "\r\n";
            num = display_message(this->file_vectors[i].get_socket(), message);
            return (num);
        }
    }
    message = "401 ERR_NOSUCHNICK " + this->file_vectors[my_place].get_user_to_send() + " :No such nick/channel" + "\r\n";
    num = display_message(this->file_vectors[my_place].get_socket(), message);
    return num;
}

int Server:: display_message(int sockfd, std:: string message)
{
    int num;

    num = 0;
    for (size_t i = 0; i < message.size(); i++)
    {
        num = write(sockfd, &message[i], 1);
        if (num < 0)
            return (-1);
    }
    return (num);
}

int Server:: display_error(void)
{
    std:: string handle_message;
    std:: string message;
    int num;

    if (this->file_vectors[my_place].get_command().find('\n') != std:: string:: npos)
        handle_message = this->file_vectors[my_place].get_command().substr(0, this->file_vectors[my_place].get_command().size() - 2);
    else
        handle_message = this->file_vectors[my_place].get_command();
    message = "461 ERR_NEEDMOREPARAMS " + handle_message + " :Not enough parameters" + "\r\n";
    num = display_message(this->file_vectors[my_place].get_socket(), message);
    return (num);
}

bool Server:: check_ctrl_D(std:: string buffer)
{
    this->old_buffer += buffer;
    if (buffer.find("\n") != std:: string:: npos && buffer.find("\r") != std:: string:: npos)
    {
        this->_buffer = this->old_buffer;
        this->old_buffer.erase();
        return (true);
    }
    return (false);
}
