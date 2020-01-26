#include <string>
#include <vector>

class Game
{

private:

	std::string gameType; 
	std::string gameCode; // each game has an individual game code
	int playerCount; // number of players in the game
	bool gameStatus; // this determines if the game is in play or not
	std::string hostName; 
	std::vector<std::string> playerNames;

public:

	Game(std::string gameType, std::string gameCode, int playerCount, bool gameStatus, std::string hostName, std::vector<std::string> playerNames)
		: gameType(gameType), gameCode(gameCode), playerCount(playerCount), gameStatus(gameStatus), hostName(hostName), playerNames(playerNames) {}

	// getters
	std::string getGameType() const;
	std::string getGameCode() const;
	int getPlayerCount() const;
	bool getGameStatus() const;
	std::string getHostName() const;
	std::vector<std::string> getPlayerNames() const;

	//setters
	void setGameType(std::string gType);
	void setGameCode(std::string gCode);
	void setPlayerCount(int pCount);
	void setGameStatus(bool gStatus);
	void setHostName(std::string hName);
	void setPlayerNames(std::vector<std::string> pNames);

};