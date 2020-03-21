#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <utility>
#include "Game.h"
#include <fstream>
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace parser
{

#define CONFIGURATION_JSON "configuration"
#define NAME_JSON "name"
#define PLAYER_COUNT_JSON "player count"
#define MAX_JSON "max"
#define MIN_JSON "min"
#define AUDIENCE_JSON "audience"
#define SETUP_JSON "setup"

class GameParser
{
private:
    std::string jsonString;

public:
    explicit GameParser(std::string jsonString) : jsonString(std::move(jsonString)) {}
    void parseGame(std::unique_ptr<game::Game> &game);
    void parseGameConfiguration(std::unique_ptr<game::Game> &game, const json &jsonFile);
    bool validateGameConfigJson(const json &jsonConfigFile);
};

} // namespace parser

#endif