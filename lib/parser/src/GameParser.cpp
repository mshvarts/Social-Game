#include "GameParser.h"

namespace parser
{

void GameParser::parseGameConfiguration(std::unique_ptr<game::Game> &game, const json &jsonFile)
{
    auto configurationJson = jsonFile[KeyNameMap[KeyNames::Configuration]];
    game::Configuration config;

    config.name = configurationJson[KeyNameMap[KeyNames::Name]];
    config.playerCount.max = configurationJson[KeyNameMap[KeyNames::PlayerCount]][KeyNameMap[KeyNames::Max]];
    config.playerCount.min = configurationJson[KeyNameMap[KeyNames::PlayerCount]][KeyNameMap[KeyNames::Min]];
    config.audience = configurationJson[KeyNameMap[KeyNames::Audience]];

    //"setup" names a map of settings that can or must be configured by the owner of the game upon game creation. This can include such things as the numbers specifying the number of rounds to play. If the value for a setting is an integer, boolean, or string literal then that value constitutes the default value. These need not be changed by the owner upon creation but can be. Otherwise, the value must be a map of the form:
    // {
    //   "kind": <<data kind>>,
    //   "prompt": <<Description of what data the owner should provide>>
    // }

    game::Map_of_values setup;
    auto setupJson = configurationJson[KeyNameMap[KeyNames::Setup]];
    std::transform(setupJson.items().begin(), setupJson.items().end(), std::inserter(setup, setup.end()),
                   [](const auto& element){
                        boost::variant<std::string, int> value;
                       if (element.value().is_number())
                       {
                           value = static_cast<int>(element.value());
                       }
                       else
                       {
                           value = static_cast<std::string>(element.value());
                       }

                       return std::make_pair(element.key(),value);
    });
    config.setup = std::move(setup);
    game->setConfiguration(config);
}

void GameParser::parseGame(std::unique_ptr<game::Game> &game)
{
    //Get json from file and call the other parser functions.
    std::ifstream ifs(filePath);
    json jsonFile = json::parse(ifs);

    parseGameConfiguration(game, jsonFile);
}

bool GameParser::validateGameConfigJson(const json &jsonConfigFile)
{
    // For now the validation will just be a simple check to see if the keys exist.
    auto found = std::all_of(jsonConfigFile.items().begin(), jsonConfigFile.items().end(), [](const auto& element){
        //check if key exists in our KeyMap
        std::string key = element.key();
        return KeyNameMap.end() != std::find_if(KeyNameMap.begin(), KeyNameMap.end(), [key](auto& pair) {return pair.second == key;});
    } );

    return found;
}
} // namespace parser