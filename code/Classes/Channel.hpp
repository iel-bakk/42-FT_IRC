#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
# include <vector>

class Channel
{
private:
    std:: string name;
    std::vector <std::string> admins;
    std:: string password;
    std::vector <std::string>   users_list;

public:
    Channel();
    ~Channel();
    int parse_channel(std:: string channel, Channel& msg_channel);
    std::string get_channel_name();
    std::string get_channel_password();
    void    add_user_to_list(std::string user_nick);
    void    print_users_list();
    std::vector <std::string> get_users_list();
    void    empty_channel();
    void    add_admin(std::string user_nick);
    void    remove_user_from_channel_list(std::string username);
};

#endif