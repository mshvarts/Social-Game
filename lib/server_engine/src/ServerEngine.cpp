
#include "ServerEngine.h"
#include "MessageParser.h"

#include <algorithm>

ServerEngine::ServerEngine() = default;

void ServerEngine::processMessage(const EngineMessage& message) {
	MessageParser::parseMessage(message, this);
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

void ServerEngine::chatMessage(UserId userId, const std::string& text) {
	for(auto const &userEntry : users) {
		outgoing.push_back(EngineMessage{userEntry.first, std::to_string(userId) + " > " + text});
	}
}
