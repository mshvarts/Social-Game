#include "Game.h"

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

std::string Game::getHostName() const
{
	return hostName;
}

std::vector<std::string> Game::getPlayerNames() const
{
	return playerNames;
}

void Game::setPlayerCount(int pCount)
{
	playerCount = pCount;
}

void Game::setHostName(std::string hName)
{
	hostName = hName;
}

void Game::setPlayerNames(std::vector<std::string> pNames)
{
	playerNames = pNames;
}
