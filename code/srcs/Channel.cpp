#include "../Classes/Channel.hpp"

Channel:: Channel()
{
}

Channel:: ~Channel()
{
}

std::string Channel::get_channel_name() {
    return (this->name);
}

std::string Channel::get_channel_password() {
    return (this->password);
}

int Channel:: parse_channel(std:: string channel, Channel& msg_channel)
{
    std:: string tab;
    std::string pass;

    if (channel.find('#') != std::string::npos) {
        tab = channel.substr(channel.find('#') + 1);
        if (tab.find(' ') != std::string::npos && tab.find(' ') + 1 < tab.length() && tab[1] != ' ') {
            pass = tab.substr(tab.find(' ') + 1, tab.find('\r') - 1);
            tab = tab.substr(1, tab.find(' ') - 1);
            if (!is_empty(pass))
                msg_channel.password = pass;
            msg_channel.name = tab;
            return (0);
        }
        else if (tab[1] != ' '){
            if (tab.find(' ') != std::string::npos)
                tab = tab.substr(0, tab.find(' '));
            else
                tab = tab.substr(0, tab.find('\r'));
            msg_channel.name = tab;
            return (0);
        }
        else
            return (461);//Used to indicate the given channel name is invalid.
    }
    return (461);
}

// int parse_mode(std:: string request, Server &server)
// {
    
// }

void    Channel::add_user_to_list(std::string user_nick) {
    this->users_list.push_back(user_nick);
}

void    Channel::print_users_list() {
    std::vector <std::string>::iterator it;

    for (it = this->users_list.begin(); it != this->users_list.end(); it++) {
        std::cout << *it << std::endl;
    }
}

std::vector<std::string> Channel::get_users_list() {
    return (this->users_list);
}

void    Channel::empty_channel() {
    this->name = "";
    this->password = "";
}

void    Channel::add_admin(std::string user_nick){
    this->admins.push_back(user_nick);
}

void Channel::remove_user_from_channel_list(std::string username) {
    if (this->users_list.empty()) {
        return;
    }
    std::vector<std::string>::iterator it = std::find(this->users_list.begin(), this->users_list.end(), username);
    if (it != this->users_list.end()) {
        this->users_list.erase(it);
    }
}

bool    Channel::is_admin(std::string username) {
    if (find(this->admins.begin(), this->admins.end(), username) != this->admins.end())
        return (true);
    return (false);
}

bool    Channel::is_empty(std::string check) {
    std::cout << "check : " << check << "." << std::endl;
    for (unsigned long i = 0; i != check.length() ; i++) {
        if (check[i] != ' ')
            return (false);
    }
    return (true);
}

void        Channel::set_topic(std::string _topic) {
    this->topic = _topic;
}

std::string Channel::get_topic() {
    return (this->topic);
}

void    Channel::add_user_to_invite_qeue(std::string user) {
    this->invited_list.push_back(user);
}

void    Channel::remove_user_to_invite_qeue(std::string user) {
    std::vector<std::string>::iterator it;
    size_t  index = 0;

    for (it = this->invited_list.begin(); it != this->invited_list.end(); it++)
    {
        if (this->invited_list[index] == user) {
            this->invited_list.erase(this->invited_list.begin() + index);
            std::cout << "remouved ." << std::endl;
        }
        index++;
    }
}

bool    Channel::have_an_invite(std::string user) {
    if (find(this->invited_list.begin(), this->invited_list.end(), user) != this->invited_list.end())
        return (true);
    return (false);
}
void Channel::set_channels_modes()
{
    channel_modes.insert (std::make_pair ('i',0));
    channel_modes.insert (std::make_pair ('k',0));
    channel_modes.insert (std::make_pair ('m',0));
    channel_modes.insert (std::make_pair('p',0));
    channel_modes.insert (std::make_pair('t',0));

}

int Channel::find_modes (char c)
{
    std::map<char, bool>::iterator it;
    for (it = channel_modes.begin(); it != channel_modes.end(); it++)
    {
        if (it->first == c)
            return (1);
    }
    return (0);
}

void Channel::set_modes(std::string modes)
{
    std::map<char, bool>::iterator it;
    size_t i = 0;
    // std::cout << param << std::endl;
    while (i < modes.length())
    {
        // if (modes[i] == 'o')
        //     if (param.empty())
        //         return ;
        if (find_modes(modes[i]))
        {
            for (it = channel_modes.begin(); it != channel_modes.end(); it++)
            {
                if (it->first == mode[i])
                {
                    if (it->second == true)
                        std::cout << "this mode is alredy set" << std::endl;
                    else if (it->second == false)
                        it->second = true;
                }

            }
   
        }
        i++;
    }
}

void Channel::unset_modes(std::string modes)
{
    std::map<char, bool>::iterator it;
    size_t i = 1;
    while (i < modes.length())
    {
        // if (modes[i] == 'o')
        //     if (param.empty())
        //         return ;
        if (find_modes(modes[i]))
        {
            for (it = channel_modes.begin(); it != channel_modes.end(); it++)
            {
                if (it->first == modes[i])
                {
                    if (it->second == false)
                        std::cout << "this mode is alredy unset" << std::endl;
                    else if (it->second == true)
                        it->second = false;
                }
            }
        }
        i++;
    }
}