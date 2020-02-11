//
// Created by human on 2020-02-03.
//

#ifndef SOCIALGAMING_SERVERENGINE_H
#define SOCIALGAMING_SERVERENGINE_H

#include <vector>
#include <unordered_map>
#include <memory>

#include "User.h"
#include "Room.h"

struct EngineMessage {
	UserId userId;
	std::string text;
};

using UserMap = std::unordered_map<UserId, User>;

class ServerEngine {
public:
	explicit ServerEngine();

	void logIn(UserId userId);
	void logOut(UserId userId);

	void processMessage(const EngineMessage& message);
	std::vector<EngineMessage> getMessages();

	/* These messages are to be called by the JSON processor
	 * for the purpose of good design, figure out how to somehow
	 * refactor this to better encapsulate this functionality.
	 * MessageParser can't be a friend class in the header because
	 * it creates a circular dependency. Maybe something like how the
	 * server class is separated from it's implementation in the
	 * network code? */
	void chatMessage(UserId userId, const std::string& text);

private:
	UserMap users;

	std::vector<EngineMessage> outgoing;
};

#endif //SOCIALGAMING_SERVERENGINE_H
