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

    tab = channel.substr(channel.find(' ') + 1);
    if (tab.find(' ') != std:: string:: npos)
    {
        if (tab.find('&'))
            return 461;
        this->name = tab.substr(1, tab.find(' '));
        this->password = tab.substr(tab.find(' ') + 1);
        return (0);
    }
    else if (!tab.find('#'))
    {
        this->name = tab.substr(1);
        return (0);
    }
    return (461);
}
