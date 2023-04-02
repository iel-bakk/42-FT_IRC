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

int Channel:: parse_channel(std:: string channel)
{
    std:: string tab;
    std::string pass;

    tab = channel.substr(channel.find(' ') + 1);
    if (tab[0] == '#') {
        if (tab.find(' ') != std::string::npos && tab.find(' ') + 1 < tab.length()) {
            pass = tab.substr(tab.find(' ') + 1);
        }
        std::cout << "name : " << tab << std::endl;
        std::cout << "pass : " << pass << std::endl;
        return (0);
    }
    return (461);
}
