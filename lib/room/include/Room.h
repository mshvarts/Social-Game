#ifndef SOCIALGAMING_ROOM_H
#define SOCIALGAMING_ROOM_H

#include <vector>
#include <iostream>
#include "Game.h"

using UserId = long unsigned int;
using RoomId = long unsigned int;

const int INVALID_HOST_ID = -1;
const size_t DEFAULT_MAX_ROOM_SIZE = 6;

class Room {

private:
	
	std::string roomName;
	size_t maxSize;
	bool locked;
	std::string password;
	std::vector<UserId> userList;
	game::Game* currentGame;
	UserId hostUserId;
    RoomId room_Id;

public:
	explicit Room(std::string roomName) :
		roomName(std::move(roomName)),
		maxSize(DEFAULT_MAX_ROOM_SIZE),
		locked(false),
		currentGame(nullptr),
		hostUserId(INVALID_HOST_ID)
	{}

	[[nodiscard]] int getNumOfPlayers() const;
	[[nodiscard]] std::string getRoomName() const;
	[[nodiscard]] std::vector<UserId> getUserList() const;
	[[nodiscard]] size_t getRoomMaxSize() const;
	[[nodiscard]] game::Game* getGame() const;
	[[nodiscard]] UserId getHostId();

	bool setRoomName(std::string name);
	void setPassword(std::string roomPassword);
	void setMaxSize(int maxNumOfPlayers);
	bool addUser(UserId user, const std::string& passEntered);
	bool addUser(UserId user);
	void removeUser(UserId user);
	void removePassword();
	void setGame(game::Game* game);
	void setHost(UserId user);
	void setRoomId(RoomId newId);
	RoomId getRoomId() const;
};

#endif //SOCIALGAMING_ROOM_H
