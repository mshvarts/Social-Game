#include "User.h"

std::string User::getName() const
{
    return name;
}

std::string User::getUserName() const
{
    return userName;
}

std::string User::getCode() const
{
    return inviteCode;
}

bool User::isHosting() const
{
    return isHost;
}

void User::setCode(std::string code)
{
    inviteCode = code;
}

void User::setPlayerName(std::string pName)
{
    name = pName;
}

void User::setUserName(std::string uName)
{
    userName = uName;
}