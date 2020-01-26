#include <string>

#include <boost/property_tree/json_parser.hpp>

// TODO: Add game object to add the parsed json file.
class Parser
{
private:
    std::string filePath;

public:
    Parser(std::string filePath) : filePath(filePath) {} //TODO: Add Game class
    void parse(boost::property_tree::ptree &pt);
    bool validateGame(boost::property_tree::ptree &pt);
};