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
    if (tab[0] == '#' || tab[0] == '&') {
        if (tab.find(' ') != std::string::npos && tab.find(' ') + 1 < tab.length()) {
            pass = tab.substr(tab.find(' ') + 1);
            tab = tab.substr(1, tab.find(' ') - 1);
            msg_channel.name = tab;
            msg_channel.password = pass;
            return (0);
        }
        else {
            tab = tab.substr(1, tab.find('\r') - 1);
            msg_channel.name = tab;
            return (0);
        }
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