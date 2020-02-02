#include "Room.h"

bool Room::setRoomName(std::string roomName) {
	// TODO: check for duplicate, or invalid room names
	this->roomName = roomName;
	return true;
}

void Room::setNumOfPlayers(int numOfPlayers) {
	this->numOfPlayers = numOfPlayers;
}

void Room::setPassword(std::string roomPassword) {
	if (roomPassword.empty()) {
		locked = false;
	}
	else {
		locked = true;
		password = roomPassword;
	}
}
	
void Room::setMaxSize(int maxNumOfPlayers) {
	maxSize = maxNumOfPlayers;
}

/* - adds user to userList, increases numOfPlayers by one if numOfPlayers < maxSize, changes the currentRoom of the user with the ID int to this.roomID */
bool Room::addUser(User user) {
	// TODO: add password parameter and dont add user with a wrong password
	if (numOfPlayers < maxSize) {
		numOfPlayers += 1;
		userList.push_back(user);
		user.setCurrentRoom(roomId);
		return true;
	}
	return false;
}

/* removes user from userList, decreases numOfPlayers by one, changes currentRoom of the user with the ID int to that of the home room */
bool Room::removeUser(User user) {
	auto p = std::find(userList.begin(), userList.end(), user);
	userList.erase(p);

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