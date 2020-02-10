#include "User.h"

std::string User::getName() const
{
    return displayName;
}

int User::getUserId() const {
	return userId;
}

void User::setName(std::string name)
{
	displayName = std::move(name);
}

bool User::operator==(const User& other)  {
	return userId == other.getUserId();
}
