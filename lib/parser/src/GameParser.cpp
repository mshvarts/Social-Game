#include "GameParser.h"
namespace parser
{

void createMapFromJson(game::Map_of_values& map, const json &jsonObj)
{
    std::transform(jsonObj.items().begin(), jsonObj.items().end(), std::inserter(map, map.end()),
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
}

template <typename T>
void createValueTypeFromJson(T& valueType, const json& jsonObj)
{
    std::transform(jsonObj.items().begin(), jsonObj.items().end(), std::inserter(valueType.list, valueType.list.end()),
                   [](const auto& element){
                       game::Value value;
                       game::GameValue currentGameValue;
                       if (element.value().is_number())
                       {
                           value = static_cast<int>(element.value());
                       }
                       else if (element.value().is_string())
                       {
                           value = static_cast<std::string>(element.value());
                       }
                       else if (element.value().is_array())
                       {
                           game::List_of_values currentList;
                           std::transform(element.value().items().begin(), element.value().items().end(),std::inserter(currentList, currentList.end()),
                                          [](const auto& el)
                                          {
                                              boost::variant<std::string, int, game::Map_of_values> arrayValue;
                                              if (el.value().is_number())
                                              {
                                                  arrayValue =  static_cast<int>(el.value());
                                              }
                                              else if (el.value().is_string())
                                              {
                                                  arrayValue =  static_cast<std::string>(el.value());
                                              }
                                              else if(el.value().is_object())
                                              {
                                                  game::Map_of_values map;
                                                  createMapFromJson(map, el.value());
                                                  arrayValue = std::move(map);
                                              }
                                              return arrayValue;
                                          });

                           value = currentList;
                       }
                       currentGameValue.name = element.key();
                       currentGameValue.value = value;
                       return currentGameValue;
                   });
}


void GameParser::parseGameConfiguration(game::Game &game, const json &jsonFile)
{
    auto configurationJson = jsonFile[CONFIGURATION_JSON];
    game::Configuration config;

    config.name = configurationJson[NAME_JSON];
    config.playerCount.max = configurationJson[PLAYER_COUNT_JSON][MAX_JSON];
    config.playerCount.min = configurationJson[PLAYER_COUNT_JSON][MIN_JSON];
    config.audience = configurationJson[AUDIENCE_JSON];

    //"setup" names a map of settings that can or must be configured by the owner of the game upon game creation. This can include such things as the numbers specifying the number of rounds to play. If the value for a setting is an integer, boolean, or string literal then that value constitutes the default value. These need not be changed by the owner upon creation but can be. Otherwise, the value must be a map of the form:
    // {
    //   "kind": <<data kind>>,
    //   "prompt": <<Description of what data the owner should provide>>
    // }

    game::Map_of_values setup;
    auto setupJson = configurationJson[SETUP_JSON];
    createMapFromJson(setup, setupJson);
    config.setup = std::move(setup);
    game.setConfiguration(config);
}

void GameParser::parseConstants(game::Game &game, const json &jsonFile){
    game::Constants constants;

    auto constantsJson = jsonFile[CONSTANTS_JSON];
    createValueTypeFromJson(constants, constantsJson);
    game.setConstants(constants);
}

void GameParser::parseVariables(game::Game &game, const json &jsonFile){
    game::Variables variables;
    auto constantsJson = jsonFile[VARIABLES_JSON];
    createValueTypeFromJson(variables, constantsJson);
    game.setVariables(variables);
}

void GameParser::parsePerAudience(game::Game &game, const json &jsonFile){
    game::PerAudience perAudience;
    auto constantsJson = jsonFile[PER_AUDIENCE_JSON];
    createValueTypeFromJson(perAudience, constantsJson);
    game.setPerAudience(perAudience);
}

void GameParser::parsePerPlayer(game::Game &game, const json &jsonFile){
    game::PerPlayer perPlayer;
    auto constantsJson = jsonFile[PER_PLAYER_JSON];
    createValueTypeFromJson(perPlayer, constantsJson);
    game.setPerPlayer(perPlayer);
}


void GameParser::parseGame(game::Game &game)
{
    //Get json from file and call the other parser functions.
//    std::ifstream ifs(jsonString);

    json jsonFile = json::parse(jsonString);

    parseGameConfiguration(game, jsonFile);
}

// TODO: might have to look into making this function static or not inside this class.
bool GameParser::validateGameConfigJson(const json &jsonConfigFile)
{
    std::vector<std::string> validKeyStrings = {
            CONFIGURATION_JSON,
            NAME_JSON,
            PLAYER_COUNT_JSON,
            MAX_JSON,
            MIN_JSON,
            AUDIENCE_JSON,
            SETUP_JSON,
            CONSTANTS_JSON,
            VARIABLES_JSON,
            PER_AUDIENCE_JSON,
            PER_PLAYER_JSON
    };

    // For now the validation will just be a simple check to see if the keys exist.
    auto found = std::all_of(jsonConfigFile.items().begin(), jsonConfigFile.items().end(), [validKeyStrings](const auto& element){
        //check if key exists in our KeyMap
        const std::string& key = element.key();
        return validKeyStrings.end() != std::find_if(validKeyStrings.begin(), validKeyStrings.end(), [key](auto& item)
        {
            return item == key;
        });
    } );

    return found;
}

} // namespace parser