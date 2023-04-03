#include "../Classes/Message.hpp"

Message:: Message()
{
}

Message:: Message(int socket)
{
    this->socket = socket;
    client = Client();
    this->enter = false;
    this->params = create_vector();
}

Message:: Message(std:: string message): message(message)
{
}

Message:: ~Message()
{
}

std:: string Message:: get_message(void)
{
    return (this-> message);
}

int Message:: get_socket(void)
{
    return (this->socket);
}

std:: string Message:: get_command(void)
{
    return (this->command);
}

std:: string Message:: get_message_to_send(void)
{
    return (this->message_to_send);
}

std:: string Message:: get_user_to_send(void)
{
    return (this->user_to_send);
}

std:: string Message:: get_password(void)
{
    return (this->password);
}

std:: string Message:: get_welcome_message(void)
{
    return (this->welcome_message);
}

std:: string Message:: get_host_message(void)
{
    return (this->host_message);
}

std:: string Message:: get_server_message(void)
{
    return (this->server_message);
}

std:: string Message:: get_my_user(void)
{
    return (this->my_user);
}

std:: string Message:: get_notice_private(void)
{
    return (this->notice_private);
}

void Message:: set_message(std:: string message)
{
    this->message = message;
}

int Message:: parse_message(std:: string password, std:: string message, Server& server)
{
    int check = 0;

    // std::cout << "message : " << message << std::endl << "pass : " << std::endl;
    this->message = message;
    if (this->message[0] == ':')
    {
        size_t prefix_end = this->message.find(' ');
        if (prefix_end == std::string::npos)
            return check = 12;
        this->prefix = this->message.substr(1, prefix_end - 1);
        this->message = this->message.substr(prefix_end + 1);
    }
    size_t command_end = this->message.find(' ');
    this->command = this->message.substr(0, command_end);
    this->message = this->message.substr(command_end + 1);
    if (this->message == "QUIT\r\n")
        return 11;
    if (check_command(this->command))
        return check = 12;
    if (command_end == std:: string:: npos)
    {
        check = check_Error_Space(this->command);
        return (check);
    }
    if (this->message.find(' ') != std:: string:: npos)
        this->message = handle_space(this->message, this->command);
    check = check_Password_Space(this->params.size(), this->command, this->message, password);
    if (check_upper(this->command))
        return check = 12;
    if (check != 0)
        return check;
    while (!this->message.empty())
    {
        if (message[0] == ':')
        {
            this->params.push_back(this->message.substr(1));
            break ;
        }
        else
        {
            message = this->command + " " + this->message;
            this->params.push_back(message);
            break ;
        }
    }
    check = check_my_vector(this->params.back(), server);
    if (check != 0 && check != 13 && check != 14)
        this->params.erase(this->params.end() - 1);
    return (check);
}

int Message:: check_my_vector(std:: string request, Server& server)
{
   int check;
    check = 0;

    if (this->command == "NICK")
    {
        if (this->message.empty())
            return (461);
        check = client.parse_nickname(request, this->enter);
        this->my_user = client.get_nick_name();
        if (check != 0)
            return check;
        check = check_message(this->message);
    }
    else if (this->command == "USER")
        check = client.parse_username(request);
    else if (this->command == "JOIN")
    {   
        check = channel.parse_channel(request, this->channel);
        if (check == 0){
            if (!server.channel_exists(this->channel.get_channel_name())) {
                server.add_new_channel(this->channel);
                server.add_user_to_channel(this->client.get_nick_name(), this->channel.get_channel_name());
                server.send_channel_users_list(this->channel.get_channel_name(), *this);
                server.send_message_to_channel(this->channel.get_channel_name(), "joined.", this->client.get_nick_name());
            }
            else {
                server.add_user_to_channel(this->client.get_nick_name(), this->channel.get_channel_name());
                server.send_channel_users_list(this->channel.get_channel_name(), *this);
                server.send_message_to_channel(this->channel.get_channel_name(), "joined.", this->client.get_nick_name());
            }
        }
    }
    else if (this->command == "PRIVMSG")
    {
        if (request[request.find(' ') + 1] == '#')
        {
            std::cout << "channel message." << std::endl;
            check = parse_channel_message(request, server);
        }
        else if (client.get_nick_name().size() != 0 && client.get_user_name().size() != 0)
        {
            check = parse_private_message(request);
            this->notice_private = " PRIVMSG ";
        }
        else
            check = 451;
    }   
    else if (this->command == "NOTICE")
    {
        if (client.get_nick_name().size() != 0 && client.get_user_name().size())
        {
            check = parse_private_message(request);
            this->notice_private = " NOTICE ";
        }
        else
            check = 451;
    }
   check = send_Message_identification(check);
   return (check);
}

int Message:: check_Password_Space(int size, std:: string command, std:: string message, std:: string password)
{
    int check;
    size_t found_new_line;
    std:: string my_password;

    check = 0;
    found_new_line = message.find('\n');
    if (found_new_line != std:: string:: npos)
    {
        my_password = message.substr(0, found_new_line - 1);
        if (my_password.empty())
        {
            check = check_Error_Space(command);
            return (check);
        }
    }
    else
        my_password = message;
    if (size == 0)
    {
        if (command != "PASS")
            return check = 464;
        if (my_password != password)
            return check = 464;
        else
            this->password = my_password;
    }
    else
    {
        if (command == "PASS" && my_password != password)
            return check = 464;
        else
            this->password = my_password;
    }
    return (check);
}

int Message:: check_upper(std:: string command)
{
    for (size_t i = 0; i < command.size() - 2; i++)
    {
        if (!std::isupper(command[i]))
            return (1);
    }
    return (0);
}

int Message:: check_Error_Space(std:: string command)
{
    int check;
   
    check = 0;
    if (command.find("PASS") != std:: string:: npos || command.find("USER") != std:: string:: npos || command.find("JOIN") != std:: string:: npos)
        return check = 461;
    else if (command.find("NICK") != std:: string:: npos)
        return check = 431;
    return (check);
}

int Message:: check_message(std:: string command)
{
    int check;
   
    check = 0;
    if (command.find("USER") != std:: string:: npos || command.find("NICK") != std:: string:: npos || command.find("NICK") != std:: string:: npos)
    {
        if (this->command == "NICK")
            return check = 432;
    }
    return (check);
}

int Message:: send_Message_identification(int check)
{
    std:: string message;
    char hostname[256];
    char time_str[11];
    std:: time_t    now = std::time(NULL);
    std:: tm    *local_time = std:: localtime(&now);

    std::strftime(time_str, sizeof(time_str), "%d/%m/%Y", local_time);
    gethostname(hostname, sizeof(hostname));
    if (client.get_nick_name().size() != 0 && client.get_user_name().size() != 0 && this->enter == false)
    {
        this->welcome_message = ": 001 " + client.get_nick_name() + " Welcome to Internet Chat Relay";
        this->host_message = ": 002 " + client.get_nick_name() + " Your Host is " + std:: string(hostname) + ", running version 1.0";
        this->server_message = ": 003 " + client.get_nick_name() + " Ther server was created on " + std:: string(time_str);
        this->enter = true;
        return (check = 13);
    }
    return (check);
}

std:: string Message:: handle_space(std:: string message, std:: string command)
{
    std:: string str;
    size_t size;
    int count;

    size = message.size();
    count = 0;
    bool previous_was_space = true;
    for (size_t i = 0; i != size - 2; i++)
    {
        if(std::isspace(message[i]))
        {
            if (!previous_was_space)
            {
                str += ' ';
                previous_was_space = true;
                ++count;
            }
        }
        else
        {
            str += message[i];
            if (command == "PASS")
                previous_was_space = true;
            else
                previous_was_space = false;
        }
    }
    return str; 
}

int Message:: parse_private_message(std:: string message)
{
    int check;
    int count;
    std:: string user;
    std:: string _message;

    check = 14;
    count = 0;
    for (size_t i = 0; i != message.size(); i++)
    {
        if (message[i] == ' ')
            ++count;
        if (count == 1)
        {
            if (message[i] != ' ')
                user += message[i];
        }
        else if (count >= 2)
        {
            if (_message.find(":") != std:: string:: npos)
                _message += message[i];
            else
            {
                if (count == 2)
                    _message += message[i];
            }
        }
    }
    if (_message.find(":") != std:: string:: npos)
        _message.erase(0, 2);
    else
        _message.erase(0, 1);
    if (message[message.size() - 1] == ' ')
        --count;
    if (count < 2)
        return check = 412;
    this->user_to_send = user;
    this->message_to_send = _message;
    return check;
}

bool Message:: check_command(std:: string command)
{
     if (command.find("PASS") != std:: string :: npos || command.find("NICK") != std:: string :: npos \
    || command.find("USER") != std:: string :: npos || command.find("PRIVMSG") != std:: string :: npos || command.find("NOTICE") != std:: string :: npos \
    || command.find("JOIN") != std:: string :: npos)
        return false;
    return true;
}

std:: vector<std:: string> Message:: create_vector(void)
{
    return std:: vector<std:: string>();
}

void    Message::add_new_channel() {
    channels.insert(std::pair<std::string, Channel>(this->channel.get_channel_name(), this->channel));
}

int Message::parse_channel_message(std::string request, Server& server) {
    std::string channel_name;
    std::string message;

    channel_name = request.substr(request.find(' ') + 1);
    if (channel_name.find(':') + 1 != std::string::npos) {
        message = channel_name.substr(channel_name.find(':') + 1);
        channel_name = channel_name.substr(1, channel_name.find(' ') - 1);
    }
    else
        channel_name = channel_name.substr(1, channel_name.find('\r'));
    if (server.channel_exists(channel_name) == true)
    {
        server.send_message_to_channel(channel_name, message,this->client.get_nick_name());
        // message = this->client.get_nick_name() + " : " + message;
        // if (send(this->socket, message.c_str(), message.size(), 0) < 0)
        // {
        //     std::cout << "error : couldn't send message." << std::endl;
        // }
    }
    return (0);
}

Client  Message::get_client() {
    return (this->client);
}