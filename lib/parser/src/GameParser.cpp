#include "GameParser.h"


void parser::GameParser::parseGameConfiguration(std::unique_ptr<game::Game> &game, const std::string &configString)
{
    json JsonFile = json::parse(configString);
    auto configurationJson = JsonFile[JSON_CONFIGURATION];

    game->setGameName(configurationJson[JSON_CONFIG_NAME]);
    game->setMaxNumberOfPlayers(configurationJson[JSON_CONFIG_PLAYERCOUNT][JSON_MAX]);
    game->setMinNumberOfPlayers(configurationJson[JSON_CONFIG_PLAYERCOUNT][JSON_MIN]);
    game->setIsGameBeingPlayed(configurationJson[JSON_AUDIENCE]);
}

bool parser::GameParser::validateGameJSON()
{
    return true;
}