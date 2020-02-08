#ifndef SOCIALGAMING_ROOM_H
#define SOCIALGAMING_ROOM_H
#include "User.h"
#include "Game.h"

class Room {

private:
	int roomId;
	std::string roomName;
	Game roomGame;
	int hostId;
	int numOfPlayers;
	int maxSize;
	std::string password;
	bool locked;
	std::vector<User> userList;
	std::vector<User> spectatorList;
	const int DEFAULT_MAX_ROOM_SIZE = 6;
	const int MAX_ROOM_ID = 65535;
	const int HOME_ROOM_ID = -1;

public:
	Room(std::string roomName, User hostUser, Game game) : roomName(roomName), roomGame(game), hostId(hostUser.getUserId()) {
		std::srand(time(0));
		roomId = rand() % MAX_ROOM_ID;
		locked = false;
		maxSize = DEFAULT_MAX_ROOM_SIZE;
		numOfPlayers = 0;
	}

	Game getRoomGame() const;
	int getNumOfPlayers() const;
	std::string getRoomName() const;
	std::vector<User> getUserList() const;

	bool setRoomName(std::string roomName);
	void setNumOfPlayers(int numOfPlayers);
	void setPassword(std::string roomPassword);
	void setMaxSize(int maxNumOfPlayers);
	bool addUser(User user, std::string passEntered);
	bool removeUser(User user);
	void setRoomGame(Game game);
	void removePassword();
};

#endif //SOCIALGAMING_ROOM_H
