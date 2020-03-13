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
	SHOW_ROOM_INFO,
	KICK_PLAYER,
	HELP
};

std::unordered_map<Actions, std::string> commands {
	{Actions::CREATE_ROOM, "/create"},
	{Actions::JOIN_ROOM, "/join"},
	{Actions::LEAVE_ROOM, "/leave"},
	{Actions::LIST_ROOMS, "/rooms"},
	{Actions::START_GAME, "/start"},
	{Actions::END_GAME, "/end"},
	{Actions::SHOW_ROOM_INFO, "/players"},
	{Actions::KICK_PLAYER, "/kick"},
	{Actions::HELP, "/help"}
};

std::unordered_map<std::string, std::function<void(ServerEngine*, UserId, const std::string&)>> MessageParser::commandFunctions {
	{commands[Actions::CREATE_ROOM], createRoom }
	// TODO: implement these later
	/*{commands[Actions::JOIN_ROOM], joinRoom },
	{commands[Actions::LEAVE_ROOM], leaveRoom },
	{commands[Actions::LIST_ROOMS], listRooms },
	{commands[Actions::START_GAME], startGame },
	{commands[Actions::END_GAME], endGame },
	{commands[Actions::SHOW_ROOM_INFO], showRoomInfo },
	{commands[Actions::KICK_PLAYER], kickPlayer },
	{commands[Actions::HELP], showHelp }*/
};

void MessageParser::parseMessage(const EngineMessage& message, ServerEngine *engine) {

	std::string outputMessage;

	if (isCommand(message.text)) {
		parseCommand(message.text, message.userId, engine);
	}
	else {
		outputMessage = std::to_string(message.userId) + " > " + message.text;
	}
	engine->sendMessageToAll(outputMessage);
}

void MessageParser::parseCommand(const std::string& commandText, UserId userId, ServerEngine *engine) {
	bool validCommand = false;

	for (auto command : commandFunctions) {
		if (commandText.find(command.first) == 0) {
			auto argument = extractArguments(commandText);
			commandFunctions[command.first](engine, userId, argument);
			validCommand = true;
		}
	}
	if (!validCommand) {
		engine->sendMessage(userId, "Error: Invalid command");
	}
}

void MessageParser::createRoom(ServerEngine *engine, UserId userId, const std::string& roomName) {
	if (roomName.empty()) {
		engine->sendMessage(userId, "Error: Room name is missing");
	}
	else {
		Room newroom{ roomName };
		engine->sendMessage(userId, "Room was created. To join, type " + commands[Actions::JOIN_ROOM] + " " + newroom.getRoomName());
	}
}

bool MessageParser::isCommand(const std::string& commandText) {
	return commandText.find(COMMAND_DELIMETER) == 0;
}

std::string MessageParser::extractArguments(const std::string& commandText) {
	std::string argument;
	// Todo: Check if space is following after the command name immidiately
	if (commandText.find(" ") != std::string::npos) {
		argument = commandText.substr(commandText.find(" ") + 1, commandText.length());
	}
	return argument;
}