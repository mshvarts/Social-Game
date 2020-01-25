#include "Game.h"

std::string Game::getGameType() const
{
	return gameType;
}

std::string Game::getGameCode() const
{
	return gameCode;
}

int Game::getPlayerCount() const
{
	return playerCount;
}

bool Game::getGameStatus() const
{
	return gameStatus;
}

std::string Game::getHostName() const
{
	return hostName;
}

std::vector<std::string> Game::getPlayerNames() const
{
	return playerNames;
}

void Game::setGameType(std::string gType)
{
	gameType = gType;
}

void Game::setGameCode(std::string gCode)
{
	gameCode = gCode;
}

void Game::setPlayerCount(int pCount)
{
	playerCount = pCount;
}

void Game::setGameStatus(bool gStatus)
{
	gameStatus = gStatus;
}

void Game::setHostName(std::string hName)
{
	hostName = hName;
}

void Game::setPlayerNames(std::vector<std::string> pNames)
{
	playerNames = pNames;
}



