#include "User.h"

std::string User::getName() const
{
    return displayName;
}

bool User::isHosting() const
{
    return isHost;
}

int User::getUserId() const {
	return userId;
}

bool User::isSpectating() const
{
	return isSpectator;
}

void User::setUserId(int userId) {
	userId = userId;
}

void User::setCurrentRoom(int roomId) {
	currentRoom = roomId;
}

void User::setPlayerName(std::string pName)
{
	displayName = pName;
}

void User::setSpectator(bool isSpectating) {
	isSpectator = isSpectating;
}
