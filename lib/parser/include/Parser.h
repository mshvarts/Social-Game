#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "Game.h"

#include <nlohmann/json.hpp>

class Parser
{
private:
    std::string filePath;

public:
    Parser(std::string filePath) : filePath(filePath) {}
    void parseGameConfiguration(std::unique_ptr<Game> &game);
    bool validateGameJSON();
};

#endif