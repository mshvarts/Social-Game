#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <map>
#include <list>
#include <boost/variant.hpp>

namespace game {

using Map_of_values = std::map<std::string, boost::variant<std::string, int>>;
using List_of_values = std::vector<boost::variant<std::string, int, Map_of_values>>;

// Values may themselves be (1) maps from names to values, (2) lists of values, or (3) literal strings, numbers, or booleans
using Value = boost::variant<List_of_values, std::string, int, bool>;

struct PlayerCount {
    int max;
    int min;
};

struct Configuration {
    std::string name;
    PlayerCount playerCount;
    bool audience;
    Map_of_values setup;
};

// Constants and variables look the same now but that might change in the
// future so i am keeping them separate. Same goes for perPlayer and perAudience
struct GameValue
{
    std::string name;
    Value value;
};

struct Rules {
	std::vector<GameValue> list;
};

struct Constants {
    std::vector<GameValue> list;
};

struct Variables {
    std::vector<GameValue> list;
};

struct PerPlayer {
    std::vector<GameValue> list;
};

struct PerAudience {
    std::vector<GameValue> list;
};


class Game {

private:
    std::string hostName;
    std::vector<std::string> playerNames;
    bool isBeingPlayed; // this determines if the game is in play or not

    Configuration configuration;
    Constants constants;
    Variables variables;
    PerPlayer perPlayer;
    PerAudience perAudience;

    // TODO: add Rule rules class which will contain all the rules of the game.;

public:
    // constructors
    Game(){}
    Game(Configuration configuration,
         Constants constants,
         Variables variables,
         PerPlayer perPlayer,
         PerAudience perAudience ) :
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

    [[nodiscard]] Constants getGameConstants() const;

    [[nodiscard]] Variables getGameVariables() const;

    [[nodiscard]] PerPlayer getPerPlayer() const;

    [[nodiscard]] PerAudience getPerAudience() const;

    //setters
    void setHostName(std::string& hName) noexcept;

    void setPlayerNames(std::vector<std::string>& pNames) noexcept;

    void setIsGameBeingPlayed(bool gIsPlaying) noexcept;

    void setConfiguration(Configuration configuration);

    void setConstants(Constants constants);

    void setVariables(Variables variables);

    void setPerPlayer(PerPlayer gPerPlayer);

    void setPerAudience(PerAudience gPerAudience);
};

}
#endif