#include "User.h"
#include "Game.h"

class Room {

private:
	int roomId;
	std::string roomName;
	const User& hostUser;
	int numOfPlayers;
	int maxSize;
	std::string password;
	bool locked;
	std::vector<User> userList;
	const int DEFAULT_MAX_ROOM_SIZE = 6;
	const int MAX_ROOM_ID = 65535;
	const int HOME_ROOM_ID = -1;

public:
	Room(std::string roomName, const User& hostUser) : roomName(roomName), hostUser(hostUser) {
		std::srand(time(0));
		roomId = rand() % MAX_ROOM_ID;
		locked = false;
		maxSize = DEFAULT_MAX_ROOM_SIZE;
		numOfPlayers = 0;
	}

	int getNumOfPlayers() const;
	std::string getRoomName() const;

	bool setRoomName(std::string roomName);
	void setNumOfPlayers(int numOfPlayers);
	void setPassword(std::string roomPassword);
	void setMaxSize(int maxNumOfPlayers);
	bool addUser(User userId);
	bool removeUser(User userId);
};