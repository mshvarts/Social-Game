#include "MessageParser.h"
#include <functional>
#include <string>
#include "Room.h"

enum Actions {
	CREATE_ROOM,
	JOIN_ROOM,
	LEAVE_ROOM,
	LIST_ROOMS,
	START_GAME,
	END_GAME,
	KICK_PLAYER, 
	SHOW_ROOM_INFO,
	HELP
};

std::unordered_map<Actions, std::string> commands {
	{Actions::CREATE_ROOM, "/create"},
	{Actions::JOIN_ROOM, "/join"},
	/*{Actions::LEAVE_ROOM, "/leave"},
	{Actions::LIST_ROOMS, "/rooms"},
	{Actions::START_GAME, "/start"},
	{Actions::END_GAME, "/end"},
	{Actions::KICK_PLAYER, "/kick"},*/
	{Actions::SHOW_ROOM_INFO, "/info"},
	{Actions::HELP, "/help"}
};

std::unordered_map<std::string, std::function<void(ServerEngine*, const EngineMessage&)>> MessageParser::commandFunctions {
	{commands[Actions::CREATE_ROOM], createRoom },
	// TODO: implement these later
	//{commands[Actions::JOIN_ROOM], joinRoom },
	//{commands[Actions::LEAVE_ROOM], leaveRoom },
	//{commands[Actions::LIST_ROOMS], listRooms },
	//{commands[Actions::START_GAME], startGame },
	//{commands[Actions::END_GAME], endGame },
	//{commands[Actions::KICK_PLAYER], kickPlayer },
	{commands[Actions::SHOW_ROOM_INFO], showRoomInfo },
	{commands[Actions::HELP], showHelp }
};

void MessageParser::parseMessage(const EngineMessage& message, ServerEngine *engine) {

	std::string outputMessage;

	if (isCommand(message.text)) {
		parseCommand(message, engine);
	}
	else {
		outputMessage = std::to_string(message.userId) + " > " + message.text;
	}
	engine->sendMessageToAll(outputMessage);
}

void MessageParser::parseCommand(const EngineMessage& message, ServerEngine *engine) {
	bool validCommand = false;
	auto userId = message.userId;

	for (auto command : commandFunctions) {
		auto commandText = command.first;
		if (isValidCommand(commandText, message)) {
			commandFunctions[commandText](engine, message);
			validCommand = true;
		}
	}
	if (!validCommand) {
		engine->sendMessage(userId, "Error: Invalid command. Type /help for a list of commands");
	}
}

bool MessageParser::isValidCommand(const std::string& commandText, const EngineMessage& message) {
	return message.text.find(commandText) == 0 
		&& (std::isspace(message.text[commandText.length()]) 
			|| message.text.length() == commandText.length());
}

void MessageParser::createRoom(ServerEngine *engine, const EngineMessage& message) {
	auto roomName = extractArguments(message.text);
	auto userId = message.userId;

	if (roomName.empty()) {
		engine->sendMessage(userId, "Error: Room name is missing");
	}
	else {
		Room newroom{ roomName };
		engine->sendMessage(userId, "Room was created. To join, type " + commands[Actions::JOIN_ROOM] + " " + newroom.getRoomName());
	}
}

void MessageParser::showHelp(ServerEngine *engine, const EngineMessage& message) {
	engine->sendMessage(message.userId, "Welcome to Fluffernutter's Social Gaming Platform!");
	engine->sendMessage(message.userId, "Command List:");
	for (auto command : commands) {
		engine->sendMessage(message.userId, command.second);
	}
}

void MessageParser::showRoomInfo(ServerEngine *engine, const EngineMessage& message) {
	auto roomName = extractArguments(message.text);
	//auto userId = message.userId; 
	
	if (roomName.empty()) {
		// Show info about user's current room 
		// TODO: Figure out where to store a list of rooms and a way to fetch a user by Id
	}
	else {
		// Show another room's info
	}
}

bool MessageParser::isCommand(const std::string& commandText) {
	return commandText.find(COMMAND_DELIMETER) == 0;
}

std::string MessageParser::extractArguments(const std::string& commandText) {
	std::string argument;
	if (commandText.find(" ") != std::string::npos) {
		argument = commandText.substr(commandText.find(" ") + 1, commandText.length());
	}
	return argument;
}