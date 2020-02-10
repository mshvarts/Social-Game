#include "User.h"
#include "Connections.h"

std::string User::getName() const
{
    return displayName;
}

int User::getUserId() const {
	return userId;
}

void User::setName(std::string pName)
{
	displayName = pName;
}

bool User::operator==(const User& other)  {
	return userId == other.getUserId();
}
