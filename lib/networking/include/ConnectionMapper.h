#ifndef SOCIALGAMING_CONNECTIONMAPPER_H
#define SOCIALGAMING_CONNECTIONMAPPER_H

#include "User.h"
#include "Connections.h"

namespace networking {

/* This class maps connections to users. Its current purpose is simply to abstract connection
 * handling away from the ServerEngine class. It may be expanded to track users if their connection
 * id changes, such as if they reload the webpage, through the use of a session id. It may also be
 * expanded to incorporate a login system through a user database.
 */
class ConnectionMapper {
public:
	Connection getConnectionForUserId(UserId userId) {
		return Connection{reinterpret_cast<uintptr_t>(userId)};
	}

	UserId getUserIdForConnection(Connection connection) {
		return reinterpret_cast<UserId>(connection.id);
	}
};

}

#endif //SOCIALGAMING_CONNECTIONMAPPER_H
