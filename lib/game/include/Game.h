#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <map>
#include <list>
#include <boost/variant.hpp>

namespace game {

using Map_of_strings = std::map<std::string, std::string>;
using List_of_values = std::vector<boost::variant<std::string, int>>;

// Values may themselves be (1) maps from names to values, (2) lists of values, or (3) literal strings, numbers, or booleans
using Value = boost::variant<Map_of_strings, List_of_values, std::string, int, bool>;

struct PlayerCount {
    int max;
    int min;
};

struct Configuration {
    std::string name;
    PlayerCount playerCount;
    bool audience;
    Map_of_strings setup;
};

// Constants and variables look the same now but that might change in the
// future so i am keeping them separate. Same goes for perPlayer and perAudience
struct Constant {
    std::string name;
    std::vector<Map_of_strings> values;
};

struct Variable {
    std::string name;
    std::vector<Map_of_strings> values;
};

struct PerPlayer {
    std::string name;
    Value value;
};

struct PerAudience {
    std::string name;
    Value value;
};

class Game {

private:
    std::string hostName;
    std::vector<std::string> playerNames;
    bool isBeingPlayed; // this determines if the game is in play or not

    Configuration configuration;
    std::vector<Constant> constants;
    std::vector<Variable> variables;
    std::vector<PerPlayer> perPlayer;
    std::vector<PerAudience> perAudience;

    // TODO: add Rule rules class which will contain all the rules of the game.;

public:
    //constructor
    Game(Configuration configuration,
            std::vector<Constant> constants,
            std::vector<Variable> variables,
            std::vector<PerPlayer> perPlayer,
            std::vector<PerAudience> perAudience ) :
                configuration{std::move(configuration)},
                constants{std::move(constants)},
                variables{std::move(variables)},
                perPlayer{std::move(perPlayer)},
                perAudience{std::move(perAudience)} {}

    // getters
    [[nodiscard]] std::string getGameName() const;

    [[nodiscard]] std::string getHostName() const;

    [[nodiscard]] std::vector<std::string> getPlayerNames() const;

    [[nodiscard]] int getPlayerCount() const;

    [[nodiscard]] int getMaxNumberOfPlayers() const;

    [[nodiscard]] int getMinNumberOfPlayers() const;

    [[nodiscard]] bool isGameBeingPlayed() const;

    [[nodiscard]] bool isAudienceAllowed() const;

    [[nodiscard]] Configuration getConfiguration() const;

    [[nodiscard]] std::vector<Constant> getGameConstants() const;

    [[nodiscard]] std::vector<Variable> getGameVariables() const;

    [[nodiscard]] std::vector<PerPlayer> getPerPlayer() const;

    [[nodiscard]] std::vector<PerAudience> getPerAudience() const;

    //setters
    void setHostName(std::string hName) noexcept;

    void setPlayerNames(std::vector<std::string> pNames) noexcept;

    void setIsGameBeingPlayed(bool gIsPlaying) noexcept;
};

}
#endif