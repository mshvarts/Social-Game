#ifndef SOCIALGAMING_MESSAGEPARSER_H
#define SOCIALGAMING_MESSAGEPARSER_H

#include "ServerEngine.h"

#include <memory>
#include <string>
#include <utility>
#include <functional>

const char COMMAND_DELIMETER = '/';

class MessageParser {
private: 
	static std::unordered_map<std::string, std::function<void(ServerEngine*, const EngineMessage&)>> commandFunctions;
public:
	static void parseMessage(const EngineMessage& message, ServerEngine *engine);
	static void parseCommand(const EngineMessage& message, ServerEngine *engine);
	static void createRoom(ServerEngine *engine, const EngineMessage& message);
	static bool isCommand(const std::string& commandText);
	static std::string extractArguments(const std::string& commandText);
	static void showRoomInfo(ServerEngine *engine, const EngineMessage& message);
	static void joinRoom(ServerEngine *engine, const EngineMessage& message);
	static void leaveRoom(ServerEngine *engine, const EngineMessage& message);
	static void listRooms(ServerEngine *engine, const EngineMessage& message);
	static void kickPlayer(ServerEngine *engine, const EngineMessage& message);
	static void showCommands(ServerEngine *engine, const EngineMessage& message);
	static bool isValidCommand(const std::string& commandText, const EngineMessage& message);
};

#endif //SOCIALGAMING_MESSAGEPARSER_H
