
#include "ServerEngine.h"

namespace server_engine {

ServerEngine::ServerEngine() {
	Room mainMenu{"MainMenu"};
	rooms.insert(RoomMap::value_type{-1, mainMenu});
}

void ServerEngine::createRoom(User host) {

}

void ServerEngine::processMessage(ConnectionMessage message) {
}

std::vector<ConnectionMessage> ServerEngine::getMessages() {
	std::vector<ConnectionMessage> oldOutgoing;
	std::swap(oldOutgoing, outgoing);
	return oldOutgoing;
}

void ServerEngine::logIn(Connection connection) {
}

void ServerEngine::logOut(Connection connection) {
}

}
