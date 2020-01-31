#include <string>
#include <vector>
#include <map>
#include <list>

typedef std::map<std::string, std::string> map_strings;

class Game
{

private:
	std::string name; // name of the game
	std::string hostName;
	std::vector<std::string> playerNames;
	int playerCount; // number of players in the game
	int maxPlayerCount;
	int minPlayerCount;

	bool isBeingPlayed; // this determines if the game is in play or not
	bool hasAudience;   // if other people can join the game and watch others play

	map_strings setup; // configuration by the owner on game creation
	std::map<std::string, std::vector<map_strings>> constants;
	std::map<std::string, std::vector<map_strings>> variables;
	std::vector<map_strings> perPlayer;
	std::vector<map_strings> perAudience;
	// TODO: add Rule rules class which will contain all the rules of the game.;

public:
	//constructor
	Game(
		std::string name,
		std::string hostName,
		std::vector<std::string> playerNames,
		int playerCount,
		int maxPlayerCount,
		int minPlayerCount,
		bool isBeingPlayed,
		bool hasAudience,
		map_strings setup,
		std::map<std::string, std::vector<map_strings>> constants,
		std::vector<map_strings> perPlayer,
		std::vector<map_strings> perAudience) : name(name),
												hostName(hostName),
												playerNames(playerNames),
												playerCount(playerCount),
												maxPlayerCount(maxPlayerCount),
												minPlayerCount(minPlayerCount),
												isBeingPlayed(isBeingPlayed),
												hasAudience(hasAudience),
												setup(setup),
												constants(constants),
												perPlayer(perPlayer),
												perAudience(perAudience) {}

	// getters
	int getPlayerCount() const;
	int getMaxNumberOfPlayers() const;
	int getMinNumberOfPlayers() const;

	bool isGameBeingPlayed() const;
	bool isAudienceAllowed() const;

	std::string getHostName() const;
	std::vector<std::string> getPlayerNames() const;

	//setters
	void setPlayerCount(int pCount);
	void setGameStatus(bool gStatus);
	void setHostName(std::string hName);
	void setPlayerNames(std::vector<std::string> pNames);
};