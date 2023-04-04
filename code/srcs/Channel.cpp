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
std::string Channel::get_mode() {
    return (this->mode);
}

int Channel:: parse_channel(std:: string channel, Channel& msg_channel)
{
    std:: string tab;
    std::string pass;
    std::string mode;

    tab = channel.substr(channel.find(' ') + 1);
    if ((tab[0] == '#' || tab[0] == '&' ) && tab.length() > 1 && tab[1] != ' '){
        if (tab.find(' ') != std::string::npos && tab.find(' ') + 1 < tab.length()) {
            std::cout << tab << std::endl;
            if (tab.find('+') != std::string::npos && tab.find('+') + 1 < tab.length())
            {

                mode = tab.substr(tab.find('+'));
                if (mode.find(' ') + 1 < mode.length() && mode[1] != ' ')
                {
                    pass = mode.substr(mode.find(' ') + 1);
                    std::cout <<"pass :" << pass << std::endl;
                    mode = mode.substr(0,mode.find(' '));
                    std::cout <<"MODE :" << mode << std::endl;
                    tab = tab.substr(1, tab.find(' ') - 1);
                    std::cout <<"TAB :" << tab << std::endl;
                    msg_channel.name = tab;
                    msg_channel.password = pass;
                    msg_channel.mode = mode;
                    return (0);

                }
                else 
                    return (461);
            }
            else{
                pass = tab.substr(tab.find(' ') + 1);
                tab = tab.substr(1, tab.find(' ') - 1);
            msg_channel.name = tab;
            msg_channel.password = pass;
            return (0);
            }
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