#include "User.h"

std::string User::getName() const {
    return displayName;
}

UserId User::getUserId() const {
	return userId;
}

Room* User::getCurrentRoom() const {
	return currentRoom;
}

void User::setName(std::string name) {
	displayName = std::move(name);
}

void User::setCurrentRoom(Room* room) {
	currentRoom = room;
}

bool User::operator==(const User& other) {
	return userId == other.getUserId();
}
