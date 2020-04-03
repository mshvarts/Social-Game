/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////

#include "Server.h"
#include "User.h"
#include "ServerEngine.h"
#include "ConnectionMapper.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <ctime>

using networking::Connection;
using networking::ConnectionHash;
using networking::ConnectionMessage;
using networking::ConnectionMapper;
using networking::Server;

std::vector<Connection> clients;
std::unique_ptr<ConnectionMapper> connectionMapper;
std::unique_ptr<ServerEngine> serverEngine;

void onConnect(Connection c)
{
  std::cout << "New connection found: " << c.id << "\n";

  UserId userId = connectionMapper->getUserIdForConnection(c);
  serverEngine->logIn(userId);

  clients.push_back(c);
}

void onDisconnect(Connection c)
{
  std::cout << "Connection lost: " << c.id << "\n";

  UserId userId = connectionMapper->getUserIdForConnection(c);
  serverEngine->logOut(userId);

  auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
  clients.erase(eraseBegin, std::end(clients));
}

struct MessageResult
{
  std::vector<ConnectionMessage> result;
  bool shouldShutdown;
};

MessageResult
processMessages(Server &server, const std::deque<ConnectionMessage> &incoming)
{

  std::vector<ConnectionMessage> result;
  bool quit = false;

  for (auto &message : incoming)
  {

    if (message.text == "quit")
    {
      server.disconnect(message.connection);
    }
    else if (message.text == "shutdown")
    {
      std::cout << "Shutting down.\n";
      quit = true;
    }
    else
    {
    	auto messageUserId = connectionMapper->getUserIdForConnection(message.connection);
    	EngineMessage engineMessage{messageUserId, message.text};
    	serverEngine->processMessage(engineMessage);
//    	auto engineResponse = serverEngine->getMessages();
//    	for(auto &responseMessage : engineResponse) {
//    		auto messageConnection = connectionMapper->getConnectionForUserId(responseMessage.userId);
//    		ConnectionMessage outgoing{messageConnection, responseMessage.text};
//
//    		result.push_back(outgoing);
//    	}
    }
  }

    auto engineResponse = serverEngine->getMessages();     //I don't know if this is going to break something later, but it sure works for now.
    for(auto &responseMessage : engineResponse) {          //In the case that moving this chunk of code breaks something down the line, just comment out these lines,
        auto messageConnection = connectionMapper->getConnectionForUserId(responseMessage.userId);  //and uncomment the lines in the for loop above.
        ConnectionMessage outgoing{messageConnection, responseMessage.text};                        //This chunk of code was moved so that messages sent from the server
        result.push_back(outgoing);                                                                 //would be sent automatically instead of waiting for a user input to be sent first.
    }
  return MessageResult{result, quit};
}

std::deque<ConnectionMessage>
buildOutgoing(const std::vector<ConnectionMessage> &log)
{
  std::deque<ConnectionMessage> outgoing;

  outgoing.insert(outgoing.end(), log.begin(), log.end());

  return outgoing;
}

std::string
getHTTPMessage(const char *htmlLocation)
{
  if (access(htmlLocation, R_OK) != -1)
  {
    std::ifstream infile{htmlLocation};
    return std::string{std::istreambuf_iterator<char>(infile),
                       std::istreambuf_iterator<char>()};
  }
  else
  {
    std::cerr << "Unable to open HTML index file:\n"
              << htmlLocation << "\n";
    std::exit(-1);
  }
}

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage:\n  " << argv[0] << " <port> <html response>\n"
              << "  e.g. " << argv[0] << " 4002 ./webgame.html\n";
    return 1;
  }

  connectionMapper = std::make_unique<ConnectionMapper>();
  serverEngine = std::make_unique<ServerEngine>();

  unsigned short port = std::stoi(argv[1]);
  Server server{port, getHTTPMessage(argv[2]), onConnect, onDisconnect};

  while (true)
  {
    bool errorWhileUpdating = false;
    try
    {
      server.update();
    }
    catch (std::exception &e)
    {
      std::cerr << "Exception from Server update:\n"
                << " " << e.what() << "\n\n";
      errorWhileUpdating = true;
    }

    auto incoming = server.receive();

    auto [log, shouldQuit] = processMessages(server, incoming);

    auto outgoing = buildOutgoing(log);
    server.send(outgoing);

    if (shouldQuit || errorWhileUpdating)
    {
      break;
    }

    sleep(1);
  }

  return 0;
}
