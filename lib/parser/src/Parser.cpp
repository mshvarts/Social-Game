#include "Parser.h"
#include <iostream>

void Parser::parse(boost::property_tree::ptree &pt)
{
    boost::property_tree::ptree pt;
    try
    {
        boost::property_tree::read_json(filePath, pt);
    }
    catch (std::exception const &e)
    {
        std::cerr << e.what << std::endl;
    }
}