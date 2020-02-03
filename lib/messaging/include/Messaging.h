#ifndef SOCIALGAMING_MESSAGING_H
#define SOCIALGAMING_MESSAGING_H

#include "User.h"

#include <string>
#include <vector>

namespace messaging {

struct IncomingMessage {
	User sender;
	std::string contents;
};

struct OutgoingMessage {
	std::vector<User> recipients;
	std::string contents;
};

class Messaging {
public:
	static std::vector<OutgoingMessage> getResponse(IncomingMessage);
};

}

#endif //SOCIALGAMING_MESSAGING_H
