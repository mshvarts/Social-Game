#include "Room.h"

#include <algorithm>

bool Room::setRoomName(std::string name) {
	// TODO: check for duplicate, or invalid room names
	this->roomName = std::move(name);
	return true;
}

void Room::removePassword() {
	locked = false;
	password = "";
}

void Room::setPassword(std::string roomPassword) {
	locked = true;
	password = std::move(roomPassword);
}

void Room::setMaxSize(int maxNumOfPlayers) {
	maxSize = maxNumOfPlayers;
}

/* Adds user to userList if there is room and the password is correct */
/* Returns false if password was incorrect */
bool Room::addUser(UserId user, const std::string& passEntered) {

	if (!locked || (locked && passEntered == password)) { // Correct Password
		if (userList.size() < maxSize) {
			userList.push_back(user);
		}
		return true;
	}
	return false;
}

/* Adds user to userList if there is room */
bool Room::addUser(UserId user) {
	return addUser(user, "");
}

/* removes user from userList, decreases numOfPlayers by one, changes currentRoom of the user with the ID int to that of the home room */
void Room::removeUser(UserId user) {
	auto p = std::find(userList.begin(), userList.end(), user);
	userList.erase(p);
}

std::string Room::getRoomName() const {
	return roomName;
}

int Room::getNumOfPlayers() const {
	return userList.size();
}

std::vector<UserId> Room::getUserList() const {
	return userList;
}
