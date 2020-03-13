
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