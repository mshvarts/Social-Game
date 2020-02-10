#ifndef SOCIALGAMING_ROOM_H
#define SOCIALGAMING_ROOM_H

#include "User.h"
#include "Game.h"

class Room {

private:
	std::string roomName;
	size_t maxSize;
	bool locked;
	std::string password;
	std::vector<UserId> userList;
	const int DEFAULT_MAX_ROOM_SIZE = 6;

public:
	explicit Room(std::string roomName) : roomName(std::move(roomName)) {
		locked = false;
		maxSize = DEFAULT_MAX_ROOM_SIZE;
	}

	[[nodiscard]] int getNumOfPlayers() const;
	[[nodiscard]] std::string getRoomName() const;
	[[nodiscard]] std::vector<UserId> getUserList() const;

	bool setRoomName(std::string name);
	void setPassword(std::string roomPassword);
	void setMaxSize(int maxNumOfPlayers);
	bool addUser(UserId user, const std::string& passEntered);
	bool addUser(UserId user);
	void removeUser(UserId user);
	void removePassword();
};

#endif //SOCIALGAMING_ROOM_H
