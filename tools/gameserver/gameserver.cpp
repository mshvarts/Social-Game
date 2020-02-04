/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////

#include "Server.h"
#include "Game.h"
#include "User.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <unordered_map>

using networking::Connection;
using networking::ConnectionHash;
using networking::ConnectionMessage;
using networking::Server;

std::vector<Connection> clients;

std::unordered_map<Connection, User, ConnectionHash> users;

void onConnect(Connection c)
{
  std::cout << "New connection found: " << c.id << "\n";
  clients.push_back(c);
  User tempUser{"testTempUser"};
  users.insert(std::pair<Connection, User>{c, tempUser});
}

void onDisconnect(Connection c)
{
  std::cout << "Connection lost: " << c.id << "\n";
  auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
  clients.erase(eraseBegin, std::end(clients));
  users.erase(c);
}

struct MessageResult
{
  std::string result;
  bool shouldShutdown;
};

MessageResult
processMessages(Server &server, const std::deque<ConnectionMessage> &incoming)
{
  std::ostringstream result;
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
        result << message.connection.id << "> " << message.text << "\n";
    }
  }
  return MessageResult{result.str(), quit};
}

std::deque<ConnectionMessage>
buildOutgoing(const std::string &log)
{
  std::deque<ConnectionMessage> outgoing;
  for (auto client : clients)
  {
    outgoing.push_back({client, log});
  }
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
