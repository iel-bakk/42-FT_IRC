#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
# include <vector>

class Channel
{
private:
    std:: string name;
    std::string mode;
    std::string mode_param;
    std:: string password;
    std::vector <std::string>   users_list;

public:
    Channel();
    ~Channel();
    int parse_channel(std:: string channel, Channel& msg_channel);
    std::string get_channel_name();
    std::string get_channel_password();
    std::string get_mode();
    void    add_user_to_list(std::string user_nick);
    void    print_users_list();
    std::vector <std::string> get_users_list();
};

#endif