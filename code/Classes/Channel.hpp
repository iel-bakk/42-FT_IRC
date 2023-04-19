#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
# include <vector>
# include <map>

class Channel
{
private:
    std:: string name;
    std::vector <std::string>   admins;
    std:: string password;
    std::string mode;
    std::vector <std::string>   users_list;
    std::string topic;
    std::vector <std::string>   invited_list;
    std::vector <std::string>   users_list ;
    std::map<std::string, bool> channel_modes ;

public:
    Channel();
    ~Channel();
    int             parse_channel(std:: string channel, Channel& msg_channel);
    std::string     get_channel_name();
    std::string     get_channel_password();
    void            add_user_to_list(std::string user_nick);
    void            print_users_list();
    std::vector<std::string> get_users_list();
    void            empty_channel();
    void            add_admin(std::string user_nick);
    void            remove_user_from_channel_list(std::string username);
    bool            is_admin(std::string username);
    bool            check_join_request(std::string request);
    bool            is_empty(std::string check);
    void            set_topic(std::string _topic);
    std::string     get_topic();
    void            add_user_to_invite_qeue(std::string user);
    void            remove_user_to_invite_qeue(std::string user);
    bool            have_an_invite(std::string user);
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