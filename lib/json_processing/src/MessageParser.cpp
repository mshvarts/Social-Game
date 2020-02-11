#include "MessageParser.h"

void MessageParser::parseMessage(const EngineMessage& message, ServerEngine *engine) {
	engine->chatMessage(message.userId, message.text);
}
