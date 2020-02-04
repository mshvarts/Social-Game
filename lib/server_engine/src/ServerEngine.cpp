
#include "ServerEngine.h"

namespace server_engine {

ServerEngine::ServerEngine() {
	Room mainMenu{"MainMenu"};
	rooms.insert(RoomMap::value_type{-1, mainMenu});
}

void ServerEngine::createRoom(User host) {

}

void ServerEngine::processMessage(ConnectionMessage message) {
	Room senderRoom = rooms.at(users.at(message.connection).getCurrentRoom());

	for(const auto& user : senderRoom.getUserList()) {
		ConnectionMessage chatMessage{user.getConnection(), message.text};
		outgoing.push_back(chatMessage);
	}
}

std::vector<ConnectionMessage> ServerEngine::getMessages() {
	std::vector<ConnectionMessage> oldOutgoing;
	std::swap(oldOutgoing, outgoing);
	return oldOutgoing;
}

void ServerEngine::logIn(Connection connection) {
	User newUser{connection, "testUser"};
	rooms.at(-1).addUser(newUser);
	users.insert(UserMap::value_type(connection, newUser));
}

void ServerEngine::logOut(Connection connection) {
	rooms.at(-1).removeUser(users.at(connection));
	users.erase(connection);
}

}
