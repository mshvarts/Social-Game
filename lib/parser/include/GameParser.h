#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "Game.h"
#include <nlohmann/json.hpp>
#include <utility>

#define JSON_CONFIGURATION "configuration"
#define JSON_CONFIG_NAME "name"
#define JSON_CONFIG_PLAYERCOUNT "player count"
#define JSON_MAX "max"
#define JSON_MIN "min"
#define JSON_AUDIENCE "audience"

using nlohmann::json;

namespace parser
{

class GameParser
{
private:
    std::string filePath;

public:
    explicit GameParser(std::string filePath) : filePath(std::move(filePath)) {}
    void parseGameConfiguration(std::unique_ptr<game::Game> &game, const std::string &configString = "");
    bool validateGameJSON();
};

} // namespace parser

#endif