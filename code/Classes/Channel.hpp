#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
# include <vector>
# include <map>

class Channel
{
private:
    std:: string name;
    std::vector <std::string> admins;
    std:: string password;
    std::vector <std::string>   users_list ;
    std::map<std::string, bool> channel_modes ;

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
    void    empty_channel();
    void    add_admin(std::string user_nick);
    void    remove_user_from_channel_list(std::string username);
    void set_channels_modes();
    bool    is_admin(std::string username);
    
};

#endif