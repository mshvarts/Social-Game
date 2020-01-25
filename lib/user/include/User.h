#include <string>

class User
{
private:
    std::string name;
    std::string userName;
    std::string inviteCode; // code used to connect to game
    bool isHost;

public:
    // Constructor
    User(std::string name, std::string username, bool isHost) : name(name), userName(username), isHost(isHost) {}

    // Getters
    std::string getName() const;
    std::string getUserName() const;
    std::string getCode() const;
    bool isHosting() const;

    // Setters
    void setCode(std::string code);
    void setPlayerName(std::string pName);
    void setUserName(std::string uName);
};