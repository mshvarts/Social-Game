
#include "ServerEngine.h"

namespace server_engine {

ServerEngine::ServerEngine(const std::vector<Connection> &connections) :
		connections{connections} {
}

void ServerEngine::createRoom(User host) {

}

void ServerEngine::processMessage(ConnectionMessage message) {
	outgoing.push_back(message);
}

std::vector<ConnectionMessage> ServerEngine::getMessages() {
	std::vector<ConnectionMessage> oldOutgoing;
	std::swap(oldOutgoing, outgoing);
	return oldOutgoing;
}

}
