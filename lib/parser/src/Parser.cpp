#include "Parser.h"

void Parser::parseGameConfiguration(std::unique_ptr<Game> &game)
{
    //TODO: Remove sample json once we know where to get the json from users.
    auto JsonFile = R"(
        {
            "configuration": {
                "name": "Rock, Paper, Scissors",
                "player count": {"min": 2, "max": 4},
                "audience": false,
                "setup": {
                "Rounds": 10
                }
            },

            "constants": {
                "weapons": [
                { "name": "Rock",     "beats": "Scissors"},
                { "name": "Paper",    "beats": "Rock"},
                { "name": "Scissors", "beats": "Paper"}
                ]
            },

            "variables": {
                "winners": []
            },

            "per-player": {
                "wins": 0
            },

            "per-audience": {}
        }
    )"_json;

    auto configurationJson = JsonFile["configuration"];

    game->setGameName(configurationJson["name"]);
    game->setMaxNumberOfPlayers(configurationJson["player count"]["max"]);
    game->setMinNumberOfPlayers(configurationJson["player count"]["min"]);
    game->setIsGameBeingPlayed(configurationJson["audience"]);

    //TODO: add more complex json items to the Game class.
}

bool Parser::validateGameJSON()
{
    return true;
}