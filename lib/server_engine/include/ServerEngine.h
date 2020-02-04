//
// Created by human on 2020-02-03.
//

#ifndef SOCIALGAMING_SERVERENGINE_H
#define SOCIALGAMING_SERVERENGINE_H

#include "Server.h"
#include "User.h"

using networking::Connection;

class ServerEngine {
public:
	explicit ServerEngine(const std::vector<Connection> &);

	void createRoom(User host);

private:
	const std::vector<Connection>& connections;
};

#endif //SOCIALGAMING_SERVERENGINE_H
