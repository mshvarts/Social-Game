#include "Game.h"

namespace game
{

// getters
std::string Game::getGameName() const
{
	return name;
}

std::string Game::getHostName() const
{
	return hostName;
}

std::vector<std::string> Game::getPlayerNames() const
{
	return playerNames;
}

int Game::getPlayerCount() const
{
	return playerCount;
}

int Game::getMaxNumberOfPlayers() const
{
	return maxPlayerCount;
}

int Game::getMinNumberOfPlayers() const
{
	return minPlayerCount;
}

bool Game::isGameBeingPlayed() const
{
	return isBeingPlayed;
}

bool Game::isAudienceAllowed() const
{
	return hasAudience;
}

// setters

void Game::setGameName(std::string gName)
{
	name = gName;
}

void Game::setHostName(std::string hName)
{
	hostName = hName;
}

void Game::setPlayerCount(int pCount)
{
	playerCount = pCount;
}

void Game::setPlayerNames(std::vector<std::string> pNames)
{
	playerNames = pNames;
}

void Game::setMaxNumberOfPlayers(int gMaxCount)
{
	maxPlayerCount = gMaxCount;
}

void Game::setMinNumberOfPlayers(int gMinCount)
{
	minPlayerCount = gMinCount;
}
void Game::setIsGameBeingPlayed(bool gIsPlaying)
{
	isBeingPlayed = gIsPlaying;
}

void Game::setAudienceAllowed(bool gAudience)
{
	hasAudience = gAudience;
}

} // namespace game