#include "Game.h"

namespace game
{

// getters
std::string Game::getGameName() const
{
	return configuration.name;
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
	return playerNames.size();
}

int Game::getMaxNumberOfPlayers() const
{
	return configuration.playerCount.max;
}

int Game::getMinNumberOfPlayers() const
{
	return configuration.playerCount.min;
}

bool Game::isGameBeingPlayed() const
{
	return isBeingPlayed;
}

bool Game::isAudienceAllowed() const
{
	return configuration.audience;
}

Configuration Game::getConfiguration() const
{
    return configuration;
}

Constants Game::getGameConstants() const
{
    return constants;
}

Variables Game::getGameVariables() const
{
    return variables;
}

PerPlayer Game::getPerPlayer() const
{
    return perPlayer;
}

PerAudience Game::getPerAudience() const
{
    return perAudience;
}

//setters

void Game::setHostName(std::string& hName) noexcept
{
    hostName = hName;
}

void Game::setPlayerNames(std::vector<std::string>& pNames) noexcept
{
    playerNames = std::move(pNames);
}

void Game::setIsGameBeingPlayed(bool gIsPlaying) noexcept
{
    isBeingPlayed = gIsPlaying;
}

void Game::setConfiguration(Configuration gConfiguration) {
    configuration = gConfiguration;
}

void Game::setConstants(Constants gConstants)
{
    constants = gConstants;
}

void Game::setVariables(Variables gVariables)
{
    variables = gVariables;
}

void Game::setPerPlayer(PerPlayer gPerPlayer)
{
    perPlayer = gPerPlayer;
}

void Game::setPerAudience(PerAudience gPerAudience)
{
    perAudience = gPerAudience;
}


} // namespace game