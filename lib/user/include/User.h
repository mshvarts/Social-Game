#ifndef SOCIALGAMING_USER_H
#define SOCIALGAMING_USER_H

#include <string>
#include <utility>
#include <ctime>
#include "Connections.h"

using UserId = int;

class User
{
private:
	networking::Connection connection;
    std::string displayName;
	UserId userId; /* a unique ID to be used by the backend to designate specific users. Generated randomly on initialization */
	static const int MAX_USER_ID = 65535;

public:
    // Constructor
    User(networking::Connection connection, std::string name) :
        connection{connection},
        displayName(std::move(name))
        {};

    User(std::string name) : displayName(name) {
		userId = rand() % MAX_USER_ID;
	}

    // Getters
    std::string getName() const;
	networking::Connection getConnection() const;
	int getUserId() const;

    // Setters
    void setPlayerName(std::string pName);
	bool operator==(const User& other);
};

#endif //SOCIALGAMING_USER_H
