#ifndef GAME_H
#define GAME_H

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
	//TODO: add arguments that we can fill once we initialize a new game. (Host, numPlayers, RoomId....)
	Game() {} 

	// getters
	std::string getGameName() const;
	std::string getHostName() const;
	std::vector<std::string> getPlayerNames() const;
	int getPlayerCount() const;
	int getMaxNumberOfPlayers() const;
	int getMinNumberOfPlayers() const;
	bool isGameBeingPlayed() const;
	bool isAudienceAllowed() const;
	map_strings getGameSetup() const;
	std::map<std::string, std::vector<map_strings>> getGameConstants() const;
	std::map<std::string, std::vector<map_strings>> getGameVairables() const;
	std::vector<map_strings> getPerPlayer();
	std::vector<map_strings> getPerAudience();

	//setters
	void setGameName(std::string gName);
	void setHostName(std::string hName);
	void setPlayerNames(std::vector<std::string> pNames);
	void setPlayerCount(int pCount);
	void setMaxNumberOfPlayers(int gMaxCount);
	void setMinNumberOfPlayers(int gMinCount);
	void setIsGameBeingPlayed(bool gIsPlaying);
	void setAudienceAllowed(bool gAudience);

	void setSetup(map_strings gSetup);
	void setConstants(std::map<std::string, std::vector<map_strings>> gConstants);
	void setVariables(std::map<std::string, std::vector<map_strings>> gVariables);
	void setPerPlayer(std::vector<map_strings> gPerPlayer);
	void setPerAudience(std::vector<map_strings> gPerPlayer);
};

#endif