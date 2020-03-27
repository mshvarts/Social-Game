#include "GameParser.h"

namespace parser
{

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
    game.setConfiguration(config);
}

void GameParser::parseConstants(game::Game &game, const json &jsonFile)
{
    auto constantsJson = jsonFile[CONSTANTS_JSON];

    game::Constants constants;
    std::transform(constantsJson.items().begin(), constantsJson.items().end(), std::inserter(constants.list, constants.list.end()),
                   [](const auto& element){
                       game::Value value;
                       game::Constant currentConstant;
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
                         ; //TODO handle arrays and maps
                       }
                       currentConstant.name = element.key();
                       currentConstant.value = value;
                       return currentConstant;
                   });

    game.setConstants(constants);
}

void GameParser::parseVariables(game::Game &game, const json &jsonFile)
{
    auto variablesJson = jsonFile[VARIABLES_JSON];

    game::Variables variables;
    std::transform(variablesJson.items().begin(), variablesJson.items().end(), std::inserter(variables.list, variables.list.end()),
                   [](const auto& element){
                       game::Value value;
                       game::Variable currentVariable;
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
                       }
                       currentVariable.name = element.key();
                       currentVariable.value = value;
                       return currentVariable;
                   });

    game.setVariables(variables);
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