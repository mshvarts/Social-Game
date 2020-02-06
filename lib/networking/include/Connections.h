//
// Created by human on 2020-02-03.
//

#ifndef SOCIALGAMING_CONNECTIONS_H
#define SOCIALGAMING_CONNECTIONS_H

#include <functional>

namespace networking {

/**
 *  An identifier for a Client connected to a Server. The ID of a Connection is
 *  guaranteed to be unique across all actively connected Client instances.
 */
struct Connection {
	uintptr_t id;

	bool
	operator==(Connection other) const {
		return id == other.id;
	}
};


struct ConnectionHash {
	size_t
	operator()(Connection c) const {
		return std::hash<decltype(c.id)>{}(c.id);
	}
};

/**
 *  A Message containing text that can be sent to or was recieved from a given
 *  Connection.
 */
struct ConnectionMessage {
	Connection connection;
	std::string text;
};

}

#endif //SOCIALGAMING_CONNECTIONS_H
