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
    std::map<char, bool> channel_modes ;
    size_t limit;
    bool limite;
    bool  user_in_channel;
    std::vector    <std::string> ban_list;
    size_t limit_ban_list;

public:
    Channel();
    ~Channel();
    int             parse_channel(std:: string channel, Channel& msg_channel);
    std::string     get_channel_name();
    std::string     get_channel_password();
    int            add_user_to_list(std::string user_nick);
    void            print_users_list();
    std::vector<std::string> get_users_list();
    void            empty_channel();
    int             add_admin(std::string user_nick);
    void            remove_user_from_channel_list(std::string username);
    bool            is_admin(std::string username);
    bool            check_join_request(std::string request);
    bool            is_empty(std::string check);
    void            set_topic(std::string _topic);
    std::string     get_topic();
    void            add_user_to_invite_qeue(std::string user);
    void            remove_user_to_invite_qeue(std::string user);
    bool            have_an_invite(std::string user);
    void            set_channels_modes();
    int             find_modes(char c);
    int             set_modes(std::string,std::string);
    int             unset_modes(std::string);
    int            execute_mode(char,std::string);
    void            set_limit(int);
    bool            user_is_in_channels(std::string);
    int             add_to_ban_list(std::string);
};

#endif