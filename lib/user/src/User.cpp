#include "User.h"
#include "Connections.h"

std::string User::getName() const
{
    return displayName;
}


int User::getUserId() const {
	return userId;
}

void User::setPlayerName(std::string pName)
{
	displayName = pName;
}

networking::Connection User::getConnection() const {
	return connection;
}

bool User::operator==(const User& other)  {
	return userId == other.getUserId();
}
