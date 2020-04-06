#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <memory>
#include "Game.h"
#include "GameParser.h"

std::string ValidJsonString =
"{\n"
"  \"configuration\": {\n"
"    \"name\": \"Rock, Paper, Scissors\",\n"
"    \"player count\": {\n"
"      \"min\": 2,\n"
"      \"max\": 4\n"
"    },\n"
"    \"audience\": false,\n"
"    \"setup\": {\n"
"      \"Rounds\": 10\n"
"    }\n"
"  },\n"
"  \"constants\": {\n"
"    \"weapons\": [\n"
"      {\n"
"        \"name\": \"Rock\",\n"
"        \"beats\": \"Scissors\"\n"
"      },\n"
"      {\n"
"        \"name\": \"Paper\",\n"
"        \"beats\": \"Rock\"\n"
"      },\n"
"      {\n"
"        \"name\": \"Scissors\",\n"
"        \"beats\": \"Paper\"\n"
"      }\n"
"    ]\n"
"    ,\n"
"    \"hands\": \"None\",\n"
"    \"size\":77\n"
"  },\n"
"  \"variables\": {\n"
"    \"winners\": [1,2,3]\n"
"  },\n"
"  \"per-player\": {\n"
"    \"wins\": 0\n"
"  },\n"
"  \"per-audience\": {}}";

std::string InvalidJsonString =
"{\n"
 "  \"confasdfasfiguration\": {\n"
 "    \"name\": \"Rock, Paper, Scissors\",\n"
 "    \"player count\": {\n"
 "      \"min\": 2,\n"
 "      \"max\": 4\n"
 "    },\n"
 "    \"audience\": false,\n"
 "    \"setup\": {\n"
 "      \"Rounds\": 10\n"
 "    }\n"
 "  },\n"
 "  \"constaasdfnts\": {\n"
 "    \"weapons\": [\n"
 "      {\n"
 "        \"name\": \"Rock\",\n"
 "        \"beats\": \"Scissors\"\n"
 "      },\n"
 "      {\n"
 "        \"name\": \"Paper\",\n"
 "        \"beats\": \"Rock\"\n"
 "      },\n"
 "      {\n"
 "        \"name\": \"Scissors\",\n"
 "        \"beats\": \"Paper\"\n"
 "      }\n"
 "    ]\n"
 "  },\n"
 "  \"variabasdfasdfles\": {\n"
 "    \"winners\": []\n"
 "  },\n"
 "  \"per-player\": {\n"
 "    \"wins\": 0\n"
 "  },\n"
 "  \"per-audience\": {}}";

std::string ValidJsonString2 = "{ \"configuration\": { \"name\": \"Zen Game\", \"player count\": {\"min\": 0, \"max\": 0}, \"audience\": false, \"setup\": { } }, \"constants\": {}, \"variables\": {}, \"per-player\": {}, \"per-audience\": {}, \"rules\": {} }";

TEST(ParseNameTest, ConfigurationTest)
{
    game::Game testGame;
    parser::GameParser parser(ValidJsonString);
    parser.parseGame(testGame);
    auto name = testGame.getGameName();
    ASSERT_EQ("Rock, Paper, Scissors", name);
}

TEST(ParsePlayerCountTest, ConfigurationTest)
{
    game::Game testGame;
    parser::GameParser parser(ValidJsonString);
    parser.parseGame(testGame);
    auto max = testGame.getMaxNumberOfPlayers();
    auto min = testGame.getMinNumberOfPlayers();
    ASSERT_EQ(4, max);
    ASSERT_EQ(2, min);
}

TEST(ParseAudienceTest, ConfigurationTest)
{
    game::Game testGame;
    parser::GameParser parser(ValidJsonString);
    parser.parseGame(testGame);
    auto audience = testGame.isAudienceAllowed();
    ASSERT_EQ(false, audience);
}

TEST(ParseSetupTest, ConfigurationTest)
{
    game::Game testGame;
    parser::GameParser parser(ValidJsonString);
    parser.parseGame(testGame);
    auto setup = testGame.getConfiguration().setup;

    // setup is of type --->  std::map<std::string, boost::variant<std::string, int>>;

    auto expSetupKeysIsFound = setup.find("Rounds") != setup.end();
    auto roundsValue = setup.at("Rounds");
    ASSERT_EQ(true, expSetupKeysIsFound);
    ASSERT_EQ(10, boost::get<int>(roundsValue));
}

TEST(ParseConstants, ConstantTests)
{
    game::Game testGame;
    parser::GameParser parser(ValidJsonString);
    game::Constants constants;
    json jsonFile = json::parse(ValidJsonString);
    parser.parseConstants(testGame, jsonFile);
    constants = testGame.getGameConstants();
    auto firstConst = constants.list.at(0);
    auto thirdConst = constants.list.at(2);
    auto weaponsList = boost::get<game::List_of_values>(thirdConst.value);
    auto firstWeapon = boost::get<game::Map_of_values>(weaponsList.at(0));
    std::string name = boost::get<std::string>(firstWeapon["name"]);
    std::string beats = boost::get<std::string>(firstWeapon["beats"]);
    ASSERT_EQ((unsigned)3, constants.list.size());
    ASSERT_EQ("hands", firstConst.name);
    ASSERT_EQ("Rock", name);
    ASSERT_EQ("Scissors", beats);
}

TEST(ParseVariables, ConstantTests)
{
    game::Game testGame;
    parser::GameParser parser(ValidJsonString);
    json jsonFile = json::parse(ValidJsonString);
    parser.parseVariables(testGame, jsonFile);
    auto variables = testGame.getGameVariables();
    auto firstVar = variables.list.at(0);
    auto winnersList = boost::get<game::List_of_values>(firstVar.value);
    auto firstWinner = boost::get<int>(winnersList.at(0));
    ASSERT_EQ((long unsigned)1, variables.list.size());
    ASSERT_EQ("winners", firstVar.name);
    ASSERT_EQ(1, firstWinner);
}

TEST(validateGameConfigJson, ConfigurationTest)
{
    game::Game testGame;
    parser::GameParser parser(ValidJsonString);
    json jsonFile = json::parse(ValidJsonString);
    auto validBool = parser.validateGameConfigJson(jsonFile);

	parser::GameParser parser2(ValidJsonString2);
	json jsonFile2 = json::parse(ValidJsonString2);
	auto validBool2 = parser.validateGameConfigJson(jsonFile2);

    parser::GameParser parserInvalid(InvalidJsonString);
    jsonFile = json::parse(InvalidJsonString);
    auto invalidBool = parser.validateGameConfigJson(jsonFile);

    ASSERT_EQ(true, validBool);
	ASSERT_EQ(true, validBool2);
    ASSERT_EQ(false, invalidBool);

}