#ifndef SOCIALGAMING_USER_H
#define SOCIALGAMING_USER_H

#include <string>
#include <utility>

using UserId = unsigned long;

class User
{
private:
	UserId userId; /* a unique ID to be used by the backend to designate specific users. Generated randomly on initialization */
	std::string displayName;
	std::string currentRoom;

public:
    // Constructor
    User(UserId userId, std::string name) :
        userId(userId),
        displayName(std::move(name)),
		currentRoom("None")
        {};

    // Getters
    [[nodiscard]] std::string getName() const;
	[[nodiscard]] UserId getUserId() const;
	[[nodiscard]] std::string getCurrentRoom() const;

    // Setters
    void setName(std::string pName);
    void setCurrentRoom(const std::string& roomName);
	bool operator==(const User& other);
};

#endif //SOCIALGAMING_USER_H
