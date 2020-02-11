
#include "ServerEngine.h"

#include <algorithm>

namespace server_engine {

ServerEngine::ServerEngine() = default;

void ServerEngine::processMessage(const EngineMessage& message) {
	for(auto &userEntry : users) {
		EngineMessage outgoingMessage{userEntry.first, message.text};
		outgoing.push_back(std::move(outgoingMessage));
	}
}

std::vector<EngineMessage> ServerEngine::getMessages() {
	std::vector<EngineMessage> oldOutgoing;
	std::swap(oldOutgoing, outgoing);
	return oldOutgoing;
}

/* A system for loading users from a database can later be implemented here or in another module
 */
void ServerEngine::logIn(UserId userId) {
	User newUser{userId, std::to_string(userId)};
	users.emplace(userId, std::move(newUser));
}

void ServerEngine::logOut(UserId userId) {
	users.erase(userId);
}

}
