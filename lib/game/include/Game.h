#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <map>
#include <list>
#include <boost/variant.hpp>

namespace game
{

using map_variant = std::map<std::string, boost::variant<int, std::string>>;

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

	map_variant setup; // configuration by the owner on game creation
	std::map<std::string, std::vector<map_variant>> constants;
	std::map<std::string, std::vector<map_variant>> variables;
	std::vector<map_variant> perPlayer;
	std::vector<map_variant> perAudience;
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
	map_variant getGameSetup() const;
	std::map<std::string, std::vector<map_variant>> getGameConstants() const;
	std::map<std::string, std::vector<map_variant>> getGameVairables() const;
	std::vector<map_variant> getPerPlayer();
	std::vector<map_variant> getPerAudience();

	//setters
	void setGameName(std::string gName);
	void setHostName(std::string hName);
	void setPlayerNames(std::vector<std::string> pNames);
	void setPlayerCount(int pCount);
	void setMaxNumberOfPlayers(int gMaxCount);
	void setMinNumberOfPlayers(int gMinCount);
	void setIsGameBeingPlayed(bool gIsPlaying);
	void setAudienceAllowed(bool gAudience);

	void setSetup(map_variant gSetup);
	void setConstants(std::map<std::string, std::vector<map_variant>> gConstants);
	void setVariables(std::map<std::string, std::vector<map_variant>> gVariables);
	void setPerPlayer(std::vector<map_variant> gPerPlayer);
	void setPerAudience(std::vector<map_variant> gPerPlayer);
};

} // namespace game

#endif