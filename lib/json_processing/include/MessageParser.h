#ifndef SOCIALGAMING_MESSAGEPARSER_H
#define SOCIALGAMING_MESSAGEPARSER_H

#include "ServerEngine.h"

#include <memory>
#include <string>
#include <utility>
#include <functional>

void parseMessage(const EngineMessage& message, ServerEngine *engine);
void parseCommand(const EngineMessage& message, ServerEngine *engine);
bool isCommand(const std::string& commandText);
std::string extractArguments(const std::string& commandText);
bool isValidCommand(const std::string& commandText, const EngineMessage& message);

void createRoom(ServerEngine *engine, const EngineMessage& message);
void showRoomInfo(ServerEngine *engine, const EngineMessage& message);
void joinRoom(ServerEngine *engine, const EngineMessage& message);
void leaveRoom(ServerEngine *engine, const EngineMessage& message);
void listRooms(ServerEngine *engine, const EngineMessage& message);
void startGame(ServerEngine *engine, const EngineMessage& message);
void endGame(ServerEngine *engine, const EngineMessage& message);
void setName(ServerEngine *engine, const EngineMessage& message);
void kickPlayer(ServerEngine *engine, const EngineMessage& message);
void showCommands(ServerEngine *engine, const EngineMessage& message);
void setRoomGame(ServerEngine *engine, const EngineMessage& message);

#endif //SOCIALGAMING_MESSAGEPARSER_H
