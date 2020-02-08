#include "User.h"
#include "Connections.h"

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

void User::setCurrentRoom(int roomId) {
	currentRoom = roomId;
}

void User::setHosting(bool isHosting) {
	isHost = isHosting;
}

void User::setPlayerName(std::string pName)
{
	displayName = pName;
}

void User::setSpectating(bool isSpectating) {
	isSpectator = isSpectating;
}

int User::getCurrentRoom() const {
	return currentRoom;
}

networking::Connection User::getConnection() const {
	return connection;
}

bool User::operator==(const User& other)  {
	return userId == other.getUserId();
}
