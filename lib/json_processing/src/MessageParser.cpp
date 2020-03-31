#include "MessageParser.h"
#include <functional>
#include <string>
#include "Room.h"
#include "GameParser.h"

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
	COMMANDS,
	SETGAME
};

std::unordered_map<Actions, std::string> commands {
	{Actions::CREATE_ROOM, "/create"},
	{Actions::JOIN_ROOM, "/join"},
	{Actions::LEAVE_ROOM, "/leave"},
	{Actions::LIST_ROOMS, "/rooms"},
	{Actions::START_GAME, "/start"},
	{Actions::END_GAME, "/end"},
	{Actions::SET_NICKNAME, "/name"},
	{Actions::KICK_PLAYER, "/kick"},
	{Actions::SHOW_ROOM_INFO, "/info"},
	{Actions::COMMANDS, "/cmds"},
	{Actions::SETGAME, "/setgame"}
};

std::unordered_map<std::string, std::function<void(ServerEngine*, const EngineMessage&)>> commandFunctions{
	{commands[Actions::CREATE_ROOM], createRoom },
	{commands[Actions::JOIN_ROOM], joinRoom },
	{commands[Actions::LEAVE_ROOM], leaveRoom },
	{commands[Actions::LIST_ROOMS], listRooms },
	{commands[Actions::START_GAME], startGame },
	{commands[Actions::END_GAME], endGame },
	{commands[Actions::SET_NICKNAME], setName },
	{commands[Actions::KICK_PLAYER], kickPlayer },
	{commands[Actions::SHOW_ROOM_INFO], showRoomInfo },
	{commands[Actions::COMMANDS], showCommands },
	{commands[Actions::SETGAME], setRoomGame }
};

void parseMessage(const EngineMessage& message, ServerEngine *engine) {

	std::string outputMessage;
    auto user = engine->findUserById(message.userId);
    auto room = user->getCurrentRoom();
	if (isCommand(message.text)) {
		parseCommand(message, engine);
	}

	else {
		outputMessage = user->getName() + " > " + message.text;
	}
	engine->sendRoomMessage(room,outputMessage);
    //engine->sendMessageToAll(outputMessage);
}

void parseCommand(const EngineMessage& message, ServerEngine *engine) {
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

bool isValidCommand(const std::string& commandText, const EngineMessage& message) {
	return message.text.find(commandText) == 0 
		&& (std::isspace(message.text[commandText.length()]) 
			|| message.text.length() == commandText.length());
}

void createRoom(ServerEngine *engine, const EngineMessage& message) {
	auto roomName = extractArguments(message.text);
	auto userId = message.userId;
	auto user = engine->findUserById(userId);

	if (roomName.empty()) {
		engine->sendMessage(userId, "Error: Room name is missing");
	}
	else if (user->getCurrentRoom()->getRoomId()==engine->mainRoomId) {
		Room newRoom{ roomName };
		engine->registerRoom(newRoom,userId);
		engine->sendMessage(userId, "You have created a room. Type /join " + roomName + " to join.");

	}
	else {
	    std::cout<<"You're in room: "<<user->getCurrentRoom()->getRoomId()<<"\n";
		engine->sendMessage(userId, "You must leave a room before making a new one");
	}
}

// TODO: need to test if it actually works 
void setRoomGame(ServerEngine *engine, const EngineMessage& message) {
	auto gameConfig = extractArguments(message.text);
	auto userId = message.userId;
	auto user = engine->findUserById(userId);
	auto room = user->getCurrentRoom();
	 
	if (!room || room->getHostId() != userId) {
		engine->sendMessage(userId, "Error: You are not the host of this room.");
	}
	else if (gameConfig.empty()) {
		engine->sendMessage(userId, "Error: Game config is missing.");
	}
	else {
		game::Game newGame;
		parser::GameParser parser(gameConfig);
		auto validConfig = parser.validateGameConfigJson(gameConfig);
		if (validConfig) {
			parser.parseGame(newGame);
			room->setGame(&newGame);
		}
		else {
			engine->sendMessage(userId, "Error: Game config is invalid or not a JSON");
		}
	}
}

void showCommands(ServerEngine *engine, const EngineMessage& message) {
	auto userId = message.userId;
	engine->sendMessage(userId, "Command List: ");
	for(auto command : commands) {
		engine->sendMessage(userId, command.second);
	}
}

void listRooms(ServerEngine *engine, const EngineMessage& message) {
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

void kickPlayer(ServerEngine *engine, const EngineMessage& message) {
	auto kickPlayer = extractArguments(message.text);
	auto userId = message.userId;
	auto user = engine->findUserById(userId);
	auto room = user->getCurrentRoom();

	if (kickPlayer.empty())  {
		engine->sendMessage(userId, "You must specify a player id");
	}
	else if (room->getRoomId()!=engine->mainRoomId) {
		auto kickId = static_cast<UserId>(std::stoul(kickPlayer, nullptr, 0));
		auto kickUser = engine->findUserById(kickId);
		if (userId != room->getHostId()) {
			engine->sendMessage(userId, "You are not the host of this room.");
		}
		else if (kickUser) {
			if (room == kickUser->getCurrentRoom()) {
				engine->sendRoomMessage(room, kickUser->getName() + " has been kicked from the room.");
				room->removeUser(kickId);
				kickUser->setCurrentRoom(engine->main);
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

void setName(ServerEngine *engine, const EngineMessage& message) {
	auto userId = message.userId;
	auto user = engine->findUserById(userId);
	auto newName = extractArguments(message.text);
	auto oldName = user->getName();

	if (newName.empty()) {
		engine->sendMessage(userId, "Error: Name is missing");
	}
	else if (newName.length() < MAX_NAME_LENGTH) {
		engine->sendMessageToAll(oldName + " has changed his name from to " + newName);
		user->setName(newName);
	}
	else {
		engine->sendMessage(userId, "Your name cant be longer than " + std::to_string(MAX_NAME_LENGTH) + "  characters.");
	}
}

void startGame(ServerEngine *engine, const EngineMessage& message) {
	auto userId = message.userId;
	auto user = engine->findUserById(userId);
	auto room = user->getCurrentRoom();

	if (room->getRoomId()!=engine->mainRoomId) {
		auto game = room->getGame();
		if (game) {
			game->setIsGameBeingPlayed(true);
			engine->sendRoomMessage(room, user->getName() + " has started the game.");
		}
	}
	else {
		engine->sendMessage(userId, "You are not in any room");
	}
}

void endGame(ServerEngine *engine, const EngineMessage& message) {
	auto userId = message.userId;
	auto user = engine->findUserById(userId);
	auto room = user->getCurrentRoom();

	if (room->getRoomId()!=engine->mainRoomId) {
		auto game = room->getGame();
		if (game) {
			game->setIsGameBeingPlayed(false);
			engine->sendRoomMessage(room, user->getName() + " has ended the game.");
		}
	}
	else {
		engine->sendMessage(userId, "You are not in any room");
	}
}

void leaveRoom(ServerEngine *engine, const EngineMessage& message) {
	auto userId = message.userId;

	auto user = engine->findUserById(userId);
	auto room = user->getCurrentRoom();
	if (room->getRoomId()!=engine->mainRoomId) {
		room->removeUser(userId);
        user->setCurrentRoom(engine->main);
        engine->main->addUser(userId);
        engine->sendRoomMessage(room, user->getName() + " has left the room.");
		engine->sendMessage(userId, "You have left room '" + room->getRoomName() + "'");
	}
	else {
		engine->sendMessage(userId, "You are not in any room");
	}
}

void joinRoom(ServerEngine *engine, const EngineMessage& message) {
	auto userId = message.userId;
	auto roomName = extractArguments(message.text);
	auto room = engine->findRoomByName(roomName);
	auto user = engine->findUserById(userId);
	auto currentRoom=user->getCurrentRoom();

    if (room && currentRoom->getRoomId()==engine->mainRoomId) {
        currentRoom->removeUser(userId);
        auto user = engine->findUserById(userId);
        user->setCurrentRoom(room);
        room->addUser(userId);
		engine->sendRoomMessage(room, user->getName() + " has joined the room.");
		//engine->sendMessage(userId, "You have joined room '" + room->getRoomName() + "'");
	}
	else if (currentRoom->getRoomId()!=engine->mainRoomId) {
        engine->sendMessage(userId, "You must leave your room before joining another one");
        }
	else {
		engine->sendMessage(userId, "This room does not exist");
	}
}

void showRoomInfo(ServerEngine *engine, const EngineMessage& message) {
	// Show info about user's current room 
	auto userId = message.userId;
	auto user = engine->findUserById(userId);
	if (user) {
		auto room = user->getCurrentRoom();
		if (room->getRoomId()!=engine->mainRoomId) {
			engine->sendMessage(userId, "Room name: " + room->getRoomName());
			engine->sendMessage(userId, "Number of players: " + std::to_string(room->getNumOfPlayers()) + "/" + std::to_string(room->getRoomMaxSize()));
			auto playerList = room->getUserList();
			engine->sendMessage(userId, "Room host: " + engine->findUserById(room->getHostId())->getName());
			engine->sendMessage(userId, "Player list: ");
			if (!playerList.empty()) {
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

bool isCommand(const std::string& commandText) {
	return commandText.find("/") == 0; 
}

std::string extractArguments(const std::string& commandText) {
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