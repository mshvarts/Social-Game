#include "GameParser.h"

namespace parser
{

void GameParser::parseGameConfiguration(std::unique_ptr<game::Game> &game, const json &jsonFile)
{
    auto configurationJson = jsonFile[JSON_CONFIGURATION];

    game->setGameName(configurationJson[JSON_CONFIG_NAME]);
    game->setMaxNumberOfPlayers(configurationJson[JSON_CONFIG_PLAYERCOUNT][JSON_MAX]);
    game->setMinNumberOfPlayers(configurationJson[JSON_CONFIG_PLAYERCOUNT][JSON_MIN]);
    game->setIsGameBeingPlayed(configurationJson[JSON_AUDIENCE]);

    //"setup" names a map of settings that can or must be configured by the owner of the game upon game creation. This can include such things as the numbers specifying the number of rounds to play. If the value for a setting is an integer, boolean, or string literal then that value constitutes the default value. These need not be changed by the owner upon creation but can be. Otherwise, the value must be a map of the form:
    // {
    //   "kind": <<data kind>>,
    //   "prompt": <<Description of what data the owner should provide>>
    // }
    auto setupJson = configurationJson[JSON_SETUP];
    game::map_strings setupMap = setupJson.get<game::map_strings>();

}

void GameParser::parseGame(std::unique_ptr<game::Game> &game)
{
    //Get json from file and call the other parser functions.
    std::ifstream ifs(filePath);
    json jsonFile = json::parse(ifs);

    parseGameConfiguration(game, jsonFile);
}

bool GameParser::validateGameJSON()
{
    return true;
}
} // namespace parser