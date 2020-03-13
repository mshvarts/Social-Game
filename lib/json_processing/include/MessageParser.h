#ifndef SOCIALGAMING_MESSAGEPARSER_H
#define SOCIALGAMING_MESSAGEPARSER_H

#include "ServerEngine.h"

#include <memory>
#include <string>
#include <utility>
#include <functional>

const long unsigned int SERVER_USER_ID = -1;
const char COMMAND_DELIMETER = '/';

class MessageParser {
private: 
	static std::unordered_map<std::string, std::function<void(ServerEngine*, UserId, const std::string&)>> commandFunctions;
public:
	static void parseMessage(const EngineMessage& message, ServerEngine *engine);
	static void parseCommand(const std::string& commandText, UserId userId, ServerEngine *engine);
	static void createRoom(ServerEngine *engine, UserId userId, const std::string& roomName);
	static bool isCommand(const std::string& commandText);
	static std::string extractArguments(const std::string& commandText);
};

#endif //SOCIALGAMING_MESSAGEPARSER_H
