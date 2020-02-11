#ifndef SOCIALGAMING_MESSAGEPARSER_H
#define SOCIALGAMING_MESSAGEPARSER_H

#include "ServerEngine.h"

#include <memory>
#include <string>
#include <utility>

class MessageParser {
public:
	static void parseMessage(const EngineMessage& message, ServerEngine *engine);
};

#endif //SOCIALGAMING_MESSAGEPARSER_H
