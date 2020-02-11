#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "Game.h"

#include <nlohmann/json.hpp>
#include <utility>

class GameParser
{
private:
    std::string filePath;

public:
    explicit GameParser(std::string filePath) : filePath(std::move(filePath)) {}
    void parseGameConfiguration(std::unique_ptr<Game> &game);
    bool validateGameJSON();
};

#endif