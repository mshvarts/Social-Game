//
// Created by human on 2020-02-03.
//

#ifndef SOCIALGAMING_SERVERENGINE_H
#define SOCIALGAMING_SERVERENGINE_H

#include <vector>

#include "Connections.h"
#include "User.h"
#include "Room.h"

struct EngineMessage {
	UserId userId;
	std::string text;
};

namespace server_engine {

using networking::Connection;
using networking::ConnectionMessage;
using networking::ConnectionHash;

typedef std::unordered_map<Connection, User, ConnectionHash> UserMap;
typedef std::unordered_map<int, Room> RoomMap;

class ServerEngine {
public:
	explicit ServerEngine();

	void createRoom(User host);
	void logIn(Connection connection);
	void logOut(Connection connection);

	void processMessage(EngineMessage message);

	std::vector<EngineMessage> getMessages();

private:
	UserMap users;
	RoomMap rooms;

	std::vector<EngineMessage> outgoing;
};

}

#endif //SOCIALGAMING_SERVERENGINE_H
