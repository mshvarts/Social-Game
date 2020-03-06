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

enum class KeyNames{
    Configuration,
    Name,
    PlayerCount,
    Max,
    Min,
    Audience,
    Setup
};

std::unordered_map<KeyNames, std::string> KeyNameMap{
        {KeyNames::Configuration, "configuration"},
        {KeyNames::Name, "name"},
        {KeyNames::PlayerCount, "player count"},
        {KeyNames::Max, "max"},
        {KeyNames::Min, "min"},
        {KeyNames::Audience, "audience"},
        {KeyNames::Setup,"setup"},
};

class GameParser
{
private:
    std::string filePath;

public:
    explicit GameParser(std::string filePath) : filePath(std::move(filePath)) {}
    void parseGame(std::unique_ptr<game::Game> &game);
    void parseGameConfiguration(std::unique_ptr<game::Game> &game, const json &jsonFile);
    bool validateGameConfigJson(const json &jsonConfigFile);
};

} // namespace parser

#endif