#include <string>
#include <utility>
#include <time>

class User
{
private:
    std::string displayName;
	int currentRoom;
    bool isHost = false;
	bool isSpectator = false;
	int userId; /* a unique ID to be used by the backend to designate specific users. Generated randomly on initialization */
	const int MAX_USER_ID = 65535;

public:
    // Constructor
    User(std::string  name) : displayName(std::move(name)) {};

    User(std::string name, bool isHost, bool isSpectating) : displayName(name), isHost(isHost), isSpectator(isSpectating) {
		std::srand(time(0));
		userId = rand() % MAX_USER_ID;
	}

    // Getters
    std::string getName() const;
    bool isHosting() const;
	bool isSpectating() const;
	int getUserId() const;

    // Setters
    void setPlayerName(std::string pName);
	void setUserId(int userId);
	void setSpectator(bool isSpectating);
	void setCurrentRoom(int roomId);
};