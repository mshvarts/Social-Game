#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <memory>
// #include "GameParser.h"
#include "GameParser.h"
#include "Game.h"

std::string ValidJsonString ="{\n"
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
"  },\n"
"  \"variables\": {\n"
"    \"winners\": []\n"
"  },\n"
"  \"per-player\": {\n"
"    \"wins\": 0\n"
"  },\n"
"  \"per-audience\": {}}";


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

TEST(validateGameConfigJson, ConfigurationTest)
{
    game::Game testGame;
    parser::GameParser parser(ValidJsonString);
    json jsonFile = json::parse(ValidJsonString);
    auto actualBool = parser.validateGameConfigJson(jsonFile);

    ASSERT_EQ(true, actualBool);
}