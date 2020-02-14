#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <utility>
#include "Game.h"
#include <fstream> 
#include <nlohmann/json.hpp>

#define JSON_CONFIGURATION "configuration"
#define JSON_CONFIG_NAME "name"
#define JSON_CONFIG_PLAYERCOUNT "player count"
#define JSON_MAX "max"
#define JSON_MIN "min"
#define JSON_AUDIENCE "audience"
#define JSON_SETUP "setup"

using nlohmann::json;

namespace parser
{

class GameParser
{
private:
    std::string filePath;

public:
    explicit GameParser(std::string filePath) : filePath(std::move(filePath)) {}
    void parseGame(std::unique_ptr<game::Game> &game);
    void parseGameConfiguration(std::unique_ptr<game::Game> &game, const json &jsonFile);
    bool validateGameJSON();
};

} // namespace parser

#endif