#ifndef SOCIALGAMING_USER_H
#define SOCIALGAMING_USER_H

#include <string>
#include <utility>
#include <ctime>
#include "Connections.h"

class User
{
private:
	networking::Connection connection;
    std::string displayName;
	int currentRoom = -1;
    bool isHost = false;
	bool isSpectator = false;
	int userId; /* a unique ID to be used by the backend to designate specific users. Generated randomly on initialization */
	static const int MAX_USER_ID = 65535;

public:
    // Constructor
    User(networking::Connection connection, std::string name) :
        connection{connection},
        displayName(std::move(name))
        {};

    User(std::string name, bool isHost, bool isSpectating) : displayName(name), isHost(isHost), isSpectator(isSpectating) {
		userId = rand() % MAX_USER_ID;
	}

    // Getters
    std::string getName() const;
    bool isHosting() const;
	bool isSpectating() const;
	networking::Connection getConnection() const;
	int getUserId() const;
	int getCurrentRoom() const;

    // Setters
    void setPlayerName(std::string pName);
	void setSpectating(bool isSpectating);
	void setHosting(bool isHosting);
	void setCurrentRoom(int roomId);
	bool operator==(const User& other);
};

#endif //SOCIALGAMING_USER_H
