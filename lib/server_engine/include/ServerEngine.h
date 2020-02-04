//
// Created by human on 2020-02-03.
//

#ifndef SOCIALGAMING_SERVERENGINE_H
#define SOCIALGAMING_SERVERENGINE_H

#include <vector>

#include "Connections.h"
#include "User.h"

namespace server_engine {

using networking::Connection;
using networking::ConnectionMessage;
using networking::ConnectionHash;

typedef std::unordered_map<Connection, User, ConnectionHash> UserMap;

class ServerEngine {
public:
	explicit ServerEngine() = default;

	void createRoom(User host);
	void logIn(Connection connection);
	void logOut(Connection connection);

	void processMessage(ConnectionMessage message);

	std::vector<ConnectionMessage> getMessages();

private:
	UserMap users;

	std::vector<ConnectionMessage> outgoing;
};

}

#endif //SOCIALGAMING_SERVERENGINE_H
