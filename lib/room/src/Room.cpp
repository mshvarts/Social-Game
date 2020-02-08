#include "Room.h"
#include <algorithm>

bool Room::setRoomName(std::string roomName) {
	// TODO: check for duplicate, or invalid room names
	this->roomName = roomName;
	return true;
}

void Room::setNumOfPlayers(int numOfPlayers) {
	this->numOfPlayers = numOfPlayers;
}

void Room::removePassword() {
	locked = false;
	password = "";
}

void Room::setPassword(std::string roomPassword) {
	locked = true;
	password = roomPassword;
}
	
void Room::setMaxSize(int maxNumOfPlayers) {
	maxSize = maxNumOfPlayers;
}

/* Adds user to userList, increases numOfPlayers by one if numOfPlayers < maxSize, changes the currentRoom of the user with the ID int to this.roomID */
/* Returns false if password was incorrect */
bool Room::addUser(User user, std::string passEntered) {

	if (!locked || (locked && !passEntered.compare(password))) { // Correct Password
		if (numOfPlayers < maxSize) {
			userList.push_back(user);
			user.setHosting(false);
			user.setSpectating(false);
		}
		else if (numOfPlayers == 0) {
			userList.push_back(user);
			user.setHosting(true);
			user.setSpectating(false);
		}
		else {
			spectatorList.push_back(user);
			user.setHosting(false);
			user.setSpectating(true);
		}
		user.setCurrentRoom(roomId);
		numOfPlayers += 1;
		return true;
	}
	return false;
}

/* removes user from userList, decreases numOfPlayers by one, changes currentRoom of the user with the ID int to that of the home room */
bool Room::removeUser(User user) {
	
	if (user.isSpectating()) {
		auto p = std::find(spectatorList.begin(), spectatorList.end(), user);
		spectatorList.erase(p);
		user.setSpectating(false);
	}
	else {
		auto p = std::find(userList.begin(), userList.end(), user);
		userList.erase(p);

		// Set a new host
		if (user.isHosting()) {
			user.setHosting(false);
			if(!userList.empty()) { 
				auto nextUser = userList.begin();
				nextUser->setHosting(true);
			}
		}
	}
	numOfPlayers -= 1;
	user.setCurrentRoom(HOME_ROOM_ID);
	return true;
}

Game Room::getRoomGame() const {
	return roomGame;
}

void Room::setRoomGame(Game game) {
	roomGame = game;
}

std::string Room::getRoomName() const {
	return roomName;
}

int Room::getNumOfPlayers() const {
	return numOfPlayers;
}

std::vector<User> Room::getUserList() const {
	return userList;
}
