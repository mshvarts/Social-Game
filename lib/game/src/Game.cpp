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
    return Configuration();
}

std::vector<Constant> Game::getGameConstants() const
{
    return std::vector<Constant>();
}

std::vector<Variable> Game::getGameVariables() const
{
    return variables;
}

std::vector<PerPlayer> Game::getPerPlayer() const
{
    return perPlayer;
}

std::vector<PerAudience> Game::getPerAudience() const
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

void Game::setConfiguration(Configuration &gConfiguration) {
    configuration = std::move(gConfiguration);
}

} // namespace game