#include "Parser.h"

void Parser::parseGameConfiguration(std::unique_ptr<Game> &game)
{
    auto configurationJSON = R"(
        {
            "configuration": {
                "name": "Zen Game",
                "player count": {"min": 0, "max": 0},
                "audience": false,
                "setup": { }
            },
            "constants": {},
            "variables": {},
            "per-player": {},
            "per-audience": {},
            "rules": {}
        }
    )"_json;

    game->setGameName(configurationJSON["configuration"]["name"]);
}

bool Parser::validateGame()
{
    return true;
}

std::string Parser::Hello()
{
    return "Hello";
}