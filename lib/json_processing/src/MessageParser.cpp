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
	SET_NICKNAME,
	KICK_PLAYER, 
	SHOW_ROOM_INFO,
	COMMANDS
};

std::unordered_map<Actions, std::string> commands {
	{Actions::CREATE_ROOM, "/create"},
	{Actions::JOIN_ROOM, "/join"},
	{Actions::LEAVE_ROOM, "/leave"},
	{Actions::LIST_ROOMS, "/rooms"},
	/*{Actions::START_GAME, "/start"},
	{Actions::END_GAME, "/end"},
	{Actions::SET_NICKNAME, "/name"},*/
	{Actions::KICK_PLAYER, "/kick"},
	{Actions::SHOW_ROOM_INFO, "/info"},
	{Actions::COMMANDS, "/cmds"}
};

std::unordered_map<std::string, std::function<void(ServerEngine*, const EngineMessage&)>> MessageParser::commandFunctions {
	{commands[Actions::CREATE_ROOM], createRoom },
	{commands[Actions::JOIN_ROOM], joinRoom },
	{commands[Actions::LEAVE_ROOM], leaveRoom },
	{commands[Actions::LIST_ROOMS], listRooms },
	//{commands[Actions::START_GAME], startGame },
	//{commands[Actions::END_GAME], endGame },
	//{commands[Actions::END_GAME], setName },
	{commands[Actions::KICK_PLAYER], kickPlayer },
	{commands[Actions::SHOW_ROOM_INFO], showRoomInfo },
	{commands[Actions::COMMANDS], showCommands }
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
		engine->sendMessage(userId, "Error: Invalid command. Type /cmds for a list of commands");
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
		auto user = engine->findUserById(userId);
		if (!user->getCurrentRoom()) {
			Room newroom{ roomName };
			engine->registerRoom(newroom);
			engine->sendMessage(userId, "You have created room '" + roomName + "'. Type /join [room] to join.");
		}
		else {
			engine->sendMessage(userId, "You must leave a room before making a new one");
		}
	}
}

void MessageParser::showCommands(ServerEngine *engine, const EngineMessage& message) {
	auto userId = message.userId; 
	
	//engine->sendMessage(userId, "Welcome to Fluffernutter's Social Gaming Platform!");
	engine->sendMessage(userId, "Command List:");
	for (auto command : commands) {
		engine->sendMessage(userId, command.second);
	}
}

void MessageParser::listRooms(ServerEngine *engine, const EngineMessage& message) {
	auto roomName = extractArguments(message.text);
	auto userId = message.userId;

	auto roomList = engine->getRooms();
	if (!roomList.empty()) {
		engine->sendMessage(userId, "Room List: ");
		for (auto room : roomList) {
			engine->sendMessage(userId, "Room name: " + room.getRoomName() + ", # players: " + std::to_string(room.getNumOfPlayers())
				+ "/" + std::to_string(room.getRoomMaxSize()));
		}
	}
	else {
		engine->sendMessage(userId, "There are currently no rooms.");
	}
}

void MessageParser::kickPlayer(ServerEngine *engine, const EngineMessage& message) {
	auto kickPlayer = extractArguments(message.text);
	auto userId = message.userId;

	if (kickPlayer.empty())  {
		engine->sendMessage(userId, "You must specify a player id");
	}
	else {
		auto kickId = static_cast<UserId>(std::stoul(kickPlayer, nullptr, 0));
		auto user = engine->findUserById(userId);
		auto room = user->getCurrentRoom();
		if (room) {
			// TODO: need to check if the user has permission to kick players
			auto kickUser = engine->findUserById(kickId);
			if (kickUser) {
				if (room == kickUser->getCurrentRoom()) {
					engine->sendMessage(userId, "You have kicked player " + kickUser->getName());
					room->removeUser(kickId);
					kickUser->setCurrentRoom(nullptr);
				}
				else {
					engine->sendMessage(userId, "You cannot kick a player in another room");
				}
			}
			else {
				engine->sendMessage(userId, "Invalid user id");
			}
		}
		else {
			engine->sendMessage(userId, "You are not inside a room");
		}
	}
}

void MessageParser::leaveRoom(ServerEngine *engine, const EngineMessage& message) {
	auto userId = message.userId;

	auto user = engine->findUserById(userId);
	auto room = user->getCurrentRoom();
	if (room) {
		room->removeUser(userId);
		engine->sendMessage(userId, "You have left room '" + room->getRoomName() + "'");
		user->setCurrentRoom(nullptr);
	}
	else {
		engine->sendMessage(userId, "You are not in any room");
	}
}

void MessageParser::joinRoom(ServerEngine *engine, const EngineMessage& message) {
	auto userId = message.userId;
	auto roomName = extractArguments(message.text);
	
	auto user = engine->findUserById(userId);
	if (user->getCurrentRoom()) {
		engine->sendMessage(userId, "You must leave your room before joining another one");
	}
	else {
		auto room = engine->findRoomByName(roomName);
		if (room) {
			engine->sendMessage(userId, "You have joined room '" + room->getRoomName() + "'");
			auto user = engine->findUserById(userId);
			user->setCurrentRoom(room);
			room->addUser(userId);
		}
		else {
			engine->sendMessage(userId, "This room does not exist");
		}
	}
}

void MessageParser::showRoomInfo(ServerEngine *engine, const EngineMessage& message) {
	// Show info about user's current room 
	auto userId = message.userId;
	auto user = engine->findUserById(userId);
	if (user) {
		auto room = user->getCurrentRoom();
		if (room) {
			engine->sendMessage(userId, "Room name: " + room->getRoomName());
			engine->sendMessage(userId, "# of Players: " + std::to_string(room->getNumOfPlayers()) + "/" + std::to_string(room->getRoomMaxSize()));
			auto playerList = room->getUserList();
			if (!playerList.empty()) {
				engine->sendMessage(userId, "Player List:");
				for (auto player : playerList) {
					auto user = engine->findUserById(player);
					engine->sendMessage(userId, user->getName());
				}
			}
		}
		else {
			engine->sendMessage(userId, "You are not in a room");
		}
	}
}

bool MessageParser::isCommand(const std::string& commandText) {
	return commandText.find(COMMAND_DELIMETER) == 0;
}

std::string MessageParser::extractArguments(const std::string& commandText) {
	std::string argument;
	std::string commandTrimmed = commandText;

	// right trim
	commandTrimmed.erase(std::find_if(commandTrimmed.rbegin(), commandTrimmed.rend(), [](int ch) {
		return !std::isspace(ch); 
	}).base(), commandTrimmed.end());

	if (commandTrimmed.find(" ") != std::string::npos) {
		argument = commandText.substr(commandTrimmed.find(" ") + 1, commandTrimmed.length());
	}
	return argument;
}