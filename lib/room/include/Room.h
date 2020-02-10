#ifndef SOCIALGAMING_ROOM_H
#define SOCIALGAMING_ROOM_H

#include "User.h"

class Room {

private:
	const size_t DEFAULT_MAX_ROOM_SIZE = 6;

	std::string roomName;
	size_t maxSize;
	bool locked;
	std::string password;
	std::vector<UserId> userList;

public:
	explicit Room(std::string roomName) :
		roomName(std::move(roomName)),
		maxSize(DEFAULT_MAX_ROOM_SIZE),
		locked(false)
	{}

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
