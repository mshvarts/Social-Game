#ifndef SOCIALGAMING_USER_H
#define SOCIALGAMING_USER_H

#include <string>
#include <utility>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  

using UserId = unsigned long;
const unsigned long MAXIMUM_USER_ID = 65535;

class User
{
private:
	UserId userId; /* a unique ID to be used by the backend to designate specific users. Generated randomly on initialization */
	std::string displayName;
	
public:
    // Constructors
	User(std::string name) : User(rand() % MAXIMUM_USER_ID, std::move(name)) {}

	User(UserId userId, std::string name) :
		userId(userId),
		displayName(std::move(name))
	{};

    // Getters
    [[nodiscard]] std::string getName() const;
	[[nodiscard]] UserId getUserId() const;

    // Setters
    void setName(std::string pName);
	bool operator==(const User& other);
};

#endif //SOCIALGAMING_USER_H
