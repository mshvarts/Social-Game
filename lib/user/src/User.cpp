#include "User.h"

std::string User::getName() const
{
    return displayName;
}

UserId User::getUserId() const {
	return userId;
}

std::string User::getCurrentRoom() const {
	return currentRoom;
}

void User::setName(std::string name)
{
	displayName = std::move(name);
}

bool User::operator==(const User& other)  {
	return userId == other.getUserId();
}
