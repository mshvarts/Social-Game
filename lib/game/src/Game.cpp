#include "Game.h"

// getters
std::string game::Game::getGameName() const
{
	return name;
}

std::string game::Game::getHostName() const
{
	return hostName;
}

std::vector<std::string> game::Game::getPlayerNames() const
{
	return playerNames;
}

int game::Game::getPlayerCount() const
{
	return playerCount;
}

int game::Game::getMaxNumberOfPlayers() const
{
	return maxPlayerCount;
}

int game::Game::getMinNumberOfPlayers() const
{
	return minPlayerCount;
}

bool game::Game::isGameBeingPlayed() const
{
	return isBeingPlayed;
}

bool game::Game::isAudienceAllowed() const
{
	return hasAudience;
}

// setters

void game::Game::setGameName(std::string gName)
{
	name = gName;
}

void game::Game::setHostName(std::string hName)
{
	hostName = hName;
}

void game::Game::setPlayerCount(int pCount)
{
	playerCount = pCount;
}

void game::Game::setPlayerNames(std::vector<std::string> pNames)
{
	playerNames = pNames;
}

void game::Game::setMaxNumberOfPlayers(int gMaxCount)
{
	maxPlayerCount = gMaxCount;
}

void game::Game::setMinNumberOfPlayers(int gMinCount)
{
	minPlayerCount = gMinCount;
}
void game::Game::setIsGameBeingPlayed(bool gIsPlaying)
{
	isBeingPlayed = gIsPlaying;
}

void game::Game::setAudienceAllowed(bool gAudience)
{
	hasAudience = gAudience;
}
