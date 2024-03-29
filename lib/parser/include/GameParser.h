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
#define CONSTANTS_JSON "constants"
#define VARIABLES_JSON "variables"
#define PER_PLAYER_JSON "per-player"
#define PER_AUDIENCE_JSON "per-audience"
#define RULES_JSON "rules"

class GameParser
{
private:
    std::string jsonString;

public:
    explicit GameParser(std::string jsonString) : jsonString(std::move(jsonString)) {}
    void parseGame(game::Game &game);
    void parseGameConfiguration(game::Game &game, const json &jsonFile);
    bool validateGameConfigJson(const json &jsonConfigFile);
    void parseConstants(game::Game &game, const json &jsonFile);
    void parseVariables(game::Game &game, const json &jsonFile);
    void parsePerPlayer(game::Game &game, const json &jsonFile);
    void parsePerAudience(game::Game &game, const json &jsonFile);
	void parseRules(game::Game &game, const json &jsonFile);
};





} // namespace parser

#endif