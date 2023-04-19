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

    std::cout << "stoof : " << message << std::endl;
    // std::cout << "message : " << message << std::endl << "pass : " << std::endl;
    this->message = message;
        if (strncmp("LIST", message.c_str(), 4) == 0) {
        check = parse_list_command(message, server);
    }
    else {

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
            message = this->command + " " + this->message; // mafhemthach mzn ...
            this->params.push_back(message);
            break ;
        }
    }
    check = check_my_vector(this->params.back(), server);
    if (check != 0 && check != 13 && check != 14)
        this->params.erase(this->params.end() - 1);
    }
    return (check);
}

int Message:: check_my_vector(std:: string request, Server& server)
{
   int check;
    check = 0;

    std::cout << "cmd: " << this->command << std::endl;
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
    else if (this->command == "TOPIC")
        check = parse_topic(request, server);
    else if (this->command == "JOIN")
    {
        check = channel.parse_channel(request, this->channel);
        if (check == 0){
            if (!server.channel_exists(this->channel.get_channel_name())) {
                this->channel.add_admin(this->client.get_nick_name());
                server.add_new_channel(this->channel);
                server.add_user_to_channel(this->client.get_nick_name(), this->channel.get_channel_name());
                server.send_join_message(this->client.get_nick_name(), this->channel.get_channel_name());
                server.send_channel_users_list(this->channel.get_channel_name(), *this);
            }
            else {
                if (this->channel.get_channel_password() == server.get_channel_password(this->channel.get_channel_name())) {
                if (server.user_exist_in_channel(this->client.get_nick_name(), this->channel.get_channel_name()))
                    return (462);
                    server.add_user_to_channel(this->client.get_nick_name(), this->channel.get_channel_name());
                    server.send_join_message(this->client.get_nick_name(), this->channel.get_channel_name());
                    server.send_channel_users_list(this->channel.get_channel_name(), *this);
                    server.send_topic_message_for_new_members(this->socket, this->channel.get_channel_name());
                }
                else {
                    check = 464;
                }
            }
            this->add_a_channel_to_list(this->channel.get_channel_name());
            this->channel.empty_channel();
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
    else if (this->command == "PART")
    {
        check = parse_part_command(request, server);
        return (check);
    }
    else if (this->command == "INVITE")
    {
        check = parse_invite_command(request, server);
        return (check);
    }
    else if (this->command == "KICK")
    {
        check = parse_kick_command(request, server);
        return (check);
    }
    else if (this->command == "MODE") {
      check =  parse_Mode_command(request, server);
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
    if (command.find("PASS") != std:: string:: npos || command.find("USER") != std:: string:: npos
        || command.find("JOIN") != std:: string:: npos || command.find("PART") != std:: string:: npos
        || command.find("MODE") != std:: string:: npos || command.find("KICK") != std:: string:: npos
        || command.find("TOPIC") != std:: string:: npos || command.find("INVITE") != std:: string:: npos)
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
    if (command.find("USER") != std:: string:: npos || command.find("NICK") != std:: string:: npos || command.find("PASS") != std:: string:: npos)
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
        this->hostname = std::string(hostname);
        this->welcome_message = ":irc.1337.ma 001 " + client.get_nick_name() + " : Welcome to Internet Chat Relay";
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
    || command.find("JOIN") != std:: string :: npos || command.find("PART") != std:: string :: npos || command.find("MODE") != std:: string :: npos\
    || command.find("KICK") != std:: string :: npos || command.find("LIST") != std:: string :: npos || command.find("TOPIC") != std:: string:: npos\
    || command.find("INVITE") != std:: string:: npos)
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
    if (!server.user_exist_in_channel(this->client.get_nick_name(), channel_name))
        return (404);
    if (server.channel_exists(channel_name) == true)
    {
        server.send_message_to_channel(channel_name, message,this->client.get_nick_name());
    }
    return (0);
}

Client  Message::get_client() {
    return (this->client);
}

int Message::parse_part_command(std::string request, Server& server) {
    std::string channel_name;
    std::string message;

    channel_name = request.substr(request.find(' ') + 1);
    if (channel_name.find(':') != std::string::npos) {
        message = channel_name.substr(channel_name.find(':') + 1);
        channel_name = channel_name.substr(1, channel_name.find(' ') - 1);
        std::cout << "." << channel_name << "." << std::endl;
    }
    else {
        channel_name = channel_name.substr(channel_name.find('#') + 1, channel_name.find('\r') - 1);        
    }
    if (server.user_exist_in_channel(this->client.get_nick_name(), channel_name)) {
        server.send_part_message_to_channel(channel_name, message, this->client.get_nick_name());
        server.remove_user_from_channel(this->client.get_nick_name(), channel_name);
    }
    else
        return (403);
    return (0);
}

int Message::parse_kick_command(std::string request, Server& server) {
    std::string channel_name;
    std::string kicked_user;
    std::string reason;

    if (request.find('#') != std::string::npos) {
        channel_name = request.substr(request.find('#') + 1);
        if (channel_name.find(' ') != std::string::npos) {
            kicked_user = channel_name.substr(channel_name.find(' ') + 1);
            if (kicked_user.find(':') != std::string::npos) {
                reason = kicked_user.substr(kicked_user.find(":") + 1);
                channel_name = channel_name.substr(0, channel_name.find(' '));
                kicked_user = kicked_user.substr(0,kicked_user.find(' '));
                if (server.channel_exists(channel_name)) {
                    if (server.user_exist_in_channel(kicked_user, channel_name) && server.user_exist_in_channel(this->client.get_nick_name(), channel_name)) {
                        if (server.is_admin(channel_name, this->client.get_nick_name())) {
                            server.send_kick_message_to_channel(channel_name, kicked_user, reason, this->client.get_nick_name());
                            server.remove_user_from_channel(kicked_user, channel_name);
                        }
                        else
                            return (482);
                    }
                    else
                        return (401);
                }
                else
                    return (403);
            }
            else {
                channel_name = channel_name.substr(0, channel_name.find(' '));
                if (server.channel_exists(channel_name)) {
                    if (server.user_exist_in_channel(kicked_user, channel_name) && server.user_exist_in_channel(this->client.get_nick_name(), channel_name)) {
                        if (server.is_admin(channel_name, this->client.get_nick_name())) {
                            server.send_kick_message_to_channel(channel_name, kicked_user, "", this->client.get_nick_name());
                            server.remove_user_from_channel(kicked_user, channel_name);
                        }
                        else
                            return (482);
                    }
                    else
                        return (401);
                }
                else
                    return (403);
            }
        }
        else
            return (461);
    }
    else
        return (461);
    return (0);
}

void    Message::add_a_channel_to_list(std::string channel) {
    this->joined_channels.push_back(channel);
}

int Message::parse_list_command(std::string request, Server& server) {
    std::string command;
    std::string param;

    request = request.substr(0, request.find('\r'));
    if (request.find(" ") != std::string::npos && request.find(" ") + 1 != std::string::npos) {
        if (request.find("#") != std::string::npos) {
            command = request.substr(0, request.find(" "));
            param = request.substr(request.find("#") + 1);
            server.send_channels_list(this->socket, param, this->client.get_nick_name());
        }
        else if (check_list_param(request.substr(request.find(' '))))
            server.send_channels_list(this->socket, "", this->client.get_nick_name());
        else
            return (461);
    }
    else if (strncmp("LIST", request.c_str(), 4) == 0) {
        server.send_channels_list(this->socket, "", this->client.get_nick_name());
    }
    else
        return (461);
    return (0);
}

bool    Message::check_list_param(std::string param) {
    for (unsigned long i = 0; i != param.size(); i++) {
        if (param[i] != ' ')
            return (false);
    }
    return (true);
}

int Message::parse_topic(std::string request, Server& server){
    std::string first_param;
    std::string second_param;

    if (request.find("#") == std::string::npos)
        return (461);
    first_param = request.substr(request.find('#'));
    if (!this->channel.is_empty(first_param.substr(1)) && first_param.find(":") == std::string::npos)
        return (461);
    second_param = first_param.substr(first_param.find(":"), first_param.find('\r'));
    first_param = first_param.substr(1, first_param.find(' ') - 1);
    if (this->channel.is_empty(first_param) || this->channel.is_empty(second_param.substr(1)))
        return (461);
    second_param = second_param.substr(1, second_param.find('\r'));
    if (server.channel_exists(first_param)) {
        if (server.is_admin(first_param ,this->client.get_nick_name())) {
            server.send_topic_message(first_param, second_param);
            server.set_topic_to_channel(first_param, second_param);
        }
        else
            return (482);
    }
    else
        return (403);
    return (0);
}

int Message::parse_invite_command(std::string request, Server& server) {
    std::string first;
    std::string second;
    std::string last;

    (void)server;
    if (request.find(' ') != std::string::npos) {
        first = request.substr(request.find(' '));
        if (this->channel.is_empty(first))
            return (461);
        first = request.substr(request.find(' ') + 1);
        if (first.find('#') == std::string::npos)
            return (461);
        second = first.substr(first.find('#') + 1);
        if (this->channel.is_empty(second))
            return (461);
        if (second.find(' ') != std::string::npos) {
            last = second.substr(second.find(' '));
            second = second.substr(0, second.find(' '));
        }
        if (!this->channel.is_empty(last))
            return (461);
        first = first.substr(0, first.find(' '));
        if (server.channel_exists(second)) {
            if (server.user_exist_in_channel(first, second))
                return (443);
            server.get_channel(second).add_user_to_invite_qeue(first);
            server.send_invite_message(first, this->client.get_nick_name(), second);
        }
    }
    else
        return (461);
    return (0);
}

int Message::parse_Mode_command(std::string request, Server& server)
{
    std::string channel_name;
    std::string mode;
    std::string param;
    if (request.find('+') == std::string::npos && request.find('-') == std::string::npos)
        return (461);
    if (request.find(' ') != std::string::npos && request.find(' ') + 1 != std::string::npos)// find #
    {
        if (channel_name.find(' ') != std::string::npos)
        {
            channel_name = request.substr(request.find(' ') + 1);
            mode = channel_name.substr(channel_name.find(' ') + 1);
            if (mode.find(' ') != std::string::npos)
            {
                param = mode.substr(mode.find(' ') + 1);
                mode = mode.substr(1, mode.find(' '));
                channel_name = channel_name.substr(channel_name.find('#') + 1, channel_name.find(' '));
                if(mode[0] == '+')
                    add_mode_to_channel(mode, channel_name ,param,server);
                else if(mode[0] == '-')
                    remove_mode_from_channel(mode, channel_name,param,server);
                else 
                     return (461); 
                return (0);
            }
            else
            {
                mode = mode.substr(1, mode.find(' '));
                channel_name = channel_name.substr(channel_name.find('#') + 1, channel_name.find(' '));
                 if(mode[0] == '+')
                    add_mode_to_channel(mode, channel_name , NULL,server);
                else if(mode[0] == '-')
                    remove_mode_from_channel(mode, channel_name,NULL,server);
                else 
                     return (461); 
                return (0);
            }
        }
        else
            return (461);
    }
    return (461); 
}

void Message::check_mode (std::string mode, std::string channel_name,Server &server)
{
    if (server.channel_exists(channel_name) && server.user_exist_in_channel(channel_name,this->client.get_nick_name()))
    {
        
    }
}


void Message::add_mode_to_channel(std::string mode, std::string channel_name, std::string params,Server &server)
{
    if (!check_mode (mode, channel_name,server));
        return (std::cout << "Unrecognized mode received: " << mode ,0);
    
}