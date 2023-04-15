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

    tab = channel.substr(channel.find(' ') + 1);
    if ((tab[0] == '#' || tab[0] == '&') && !is_empty(tab.substr(0, tab.find('\r') - 1))) {
        if (tab.find(' ') != std::string::npos && tab.find(' ') + 1 < tab.length() && tab[1] != ' ') {
            pass = tab.substr(tab.find(' ') + 1, tab.find('\r') - 1);
            tab = tab.substr(1, tab.find(' ') - 1);
            msg_channel.name = tab;
            msg_channel.password = pass;
            return (0);
        }
        else if (tab[1] != ' '){
            tab = tab.substr(1, tab.find('\r') - 1);
            msg_channel.name = tab;
            return (0);
        }
        else
            return (461);//Used to indicate the given channel name is invalid.
    }
    return (461);
}

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