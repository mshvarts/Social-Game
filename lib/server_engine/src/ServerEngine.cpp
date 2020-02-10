
#include "ServerEngine.h"

namespace server_engine {

ServerEngine::ServerEngine() {
	Room mainMenu{"MainMenu"};
	rooms.insert(RoomMap::value_type{-1, mainMenu});
}

void ServerEngine::createRoom(User host) {

}

void ServerEngine::processMessage(EngineMessage message) {
}

std::vector<EngineMessage> ServerEngine::getMessages() {
	std::vector<EngineMessage> oldOutgoing;
	std::swap(oldOutgoing, outgoing);
	return oldOutgoing;
}

void ServerEngine::logIn(Connection connection) {
}

void ServerEngine::logOut(Connection connection) {
}

}
