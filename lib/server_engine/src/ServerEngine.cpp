
#include "ServerEngine.h"

namespace server_engine {

void ServerEngine::createRoom(User host) {

}

void ServerEngine::processMessage(ConnectionMessage message) {
	for(const auto& user : users) {
		ConnectionMessage chatMessage{user.first, message.text};
		outgoing.push_back(chatMessage);
	}
}

std::vector<ConnectionMessage> ServerEngine::getMessages() {
	std::vector<ConnectionMessage> oldOutgoing;
	std::swap(oldOutgoing, outgoing);
	return oldOutgoing;
}

void ServerEngine::logIn(Connection connection) {
	User newUser{"testUser"};
	users.insert(UserMap::value_type(connection, newUser));
}

void ServerEngine::logOut(Connection connection) {
	users.erase(connection);
}

}
