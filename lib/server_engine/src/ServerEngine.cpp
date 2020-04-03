
#include "ServerEngine.h"
#include "MessageParser.h"

#include <algorithm>
#include <time.h>


void ServerEngine::processMessage(const EngineMessage& message) {
	parseMessage(message, this);
}

std::vector<EngineMessage> ServerEngine::getMessages() {        //find where this function gets used It doesn't get called when the serverengine calls messages, but does get called when
	std::vector<EngineMessage> oldOutgoing;                     //MessageParse does.
	std::swap(oldOutgoing, outgoing);
	return oldOutgoing;
}

/* A system for loading users from a database can later be implemented here or in another module
 */
void ServerEngine::logIn(UserId userId) {
	User newUser{userId, std::to_string(userId)};
    newUser.setCurrentRoom(main);
    std::string newName=generateRandomName();
    newUser.setName(newName);
    main->addUser(userId);
	users.emplace(userId, std::move(newUser));
    this -> sendRoomMessage(main,newName + " has joined the server.");

}

void ServerEngine::logOut(UserId userId) {
	auto user = this->findUserById(userId);

	// remove user if hes inside a room
	if (user->getCurrentRoom()) {
		leaveRoom(this, EngineMessage{ userId, "" });
	}
    if (user->getCurrentRoom()==main)   //should theoretically be always.
    {
        main->removeUser(userId);
    }
	this->sendRoomMessage(main,user->getName() + " has left the server.");
	users.erase(userId);
}

void ServerEngine::registerRoom(Room room, UserId userId) {
    room.setHost(userId);

    room.setRoomId(roomCounter);
	rooms.emplace(room.getRoomName(), room);

	roomCounter++;


}

void ServerEngine::unregisterRoom(Room room) {
	rooms.erase(room.getRoomName());
}

User* ServerEngine::findUserById(UserId userId) {

	auto user = users.find(userId);

	if (user == users.end()) {

		return nullptr; // not found
	}
	else {
		return &user->second; 
	}
}

Room* ServerEngine::findRoomByName(const std::string& roomName) {
	auto room = rooms.find(roomName);

	if (room == rooms.end()) {
		return nullptr;
	}
	else {
		return &room->second;
	}
}

std::vector<Room> ServerEngine::getRooms() {
	std::vector<Room> roomList;
	for (auto room : rooms) {
		roomList.push_back(room.second);
	}
	return roomList;
}

void ServerEngine::sendMessageToAll(const std::string& message) {
	for(auto const &userEntry : users) {
		auto chatMessage = EngineMessage{ userEntry.first, message };
		outgoing.push_back(chatMessage);

	}
}

void ServerEngine::sendMessage(UserId toUserId, const std::string& message) { 
	auto chatMessage = EngineMessage{ toUserId, message };
	outgoing.push_back(chatMessage);
}

std::string ServerEngine::generateRandomName()
{
    srand((unsigned)time(NULL) );
    return nicknameFirstHalf[rand() % nicknameFirstHalf.size()] + nicknameSecondHalf[rand() % nicknameSecondHalf.size()];

}
void ServerEngine::sendRoomMessage(Room* room, const std::string& message) {

    for(auto const &userId : room->getUserList()) {
        auto chatMessage = EngineMessage{ userId, message };
        outgoing.push_back(chatMessage);
    }
}