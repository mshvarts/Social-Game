//
// Created by human on 2020-02-03.
//

#ifndef SOCIALGAMING_SERVERENGINE_H
#define SOCIALGAMING_SERVERENGINE_H

#include <vector>
#include <unordered_map>

#include "User.h"
#include "Room.h"

struct EngineMessage {
	UserId userId;
	std::string text;
};

namespace server_engine {

using UserMap = std::unordered_map<UserId, User>;

class ServerEngine {
public:
	explicit ServerEngine();

	//void createRoom(User host);
	void logIn(UserId userId);
	void logOut(UserId userId);

	void processMessage(const EngineMessage& message);

	std::vector<EngineMessage> getMessages();

private:
	UserMap users;

	std::vector<EngineMessage> outgoing;
};

}

#endif //SOCIALGAMING_SERVERENGINE_H
