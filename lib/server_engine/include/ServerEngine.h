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

class ServerEngine {
public:
	explicit ServerEngine(const std::vector<Connection> &);

	void createRoom(User host);

	void processMessage(ConnectionMessage message);

	std::vector<ConnectionMessage> getMessages();

private:
	const std::vector<Connection> &connections;

	std::vector<ConnectionMessage> outgoing;
};

}

#endif //SOCIALGAMING_SERVERENGINE_H
