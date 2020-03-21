#ifndef SOCIALGAMING_USER_H
#define SOCIALGAMING_USER_H

#include <string>
#include <utility>
#include "Room.h"

using UserId = long unsigned int;

class User
{
private:
	UserId userId; /* a unique ID to be used by the backend to designate specific users. Generated randomly on initialization */
	std::string displayName;
	Room* currentRoom;

public:
    // Constructor
    User(UserId userId, std::string name) :
        userId(userId),
        displayName(std::move(name)),
		currentRoom(nullptr)
        {};

    // Getters
    [[nodiscard]] std::string getName() const;
	[[nodiscard]] UserId getUserId() const;
	[[nodiscard]] Room* getCurrentRoom() const;

    // Setters
    void setName(std::string pName);
    void setCurrentRoom(Room* roomName);
	bool operator==(const User& other);
};

#endif //SOCIALGAMING_USER_H
