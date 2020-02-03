#include "Messaging.h"

#include "Parser.h"
#include "Builder.h"

namespace messaging {

std::vector<OutgoingMessage>
Messaging::getResponse(IncomingMessage) {
	return std::vector<OutgoingMessage>{};
}

}