//
// Created by human on 2020-02-03.
//

#ifndef SOCIALGAMING_SERVERENGINE_H
#define SOCIALGAMING_SERVERENGINE_H

#include <vector>
#include <unordered_map>
#include <memory>

#include "User.h"
using RoomId = long unsigned int;

struct EngineMessage {
	UserId userId;
	std::string text;
};

using UserMap = std::unordered_map<UserId, User>;
using RoomMap = std::unordered_map<std::string, Room>;

class ServerEngine {
public:
	// Upon initialization, a new user called admin is created. Then a new room called "Main" is created with Admin as the host It'll have roomID 0.
	// All new users are immediately placed into the room with ID 0.
	// Creating new rooms is only allowed in room with ID 0
	ServerEngine() {
		UserId adminId{000000};
		User Admin{adminId, "Admin"};
		Room mainRoom{"Main"};
		mainRoom.setMaxSize(999);
		registerRoom(mainRoom, adminId);
		main=findRoomByName("Main");

	}
	RoomId roomCounter=0;
	Room* main;
    const RoomId mainRoomId=0;    //in theory the main room's Id should always be zero, but I'd prefer to implement this as findIdByName("Main") once that function gets implemented
	void logIn(UserId userId);
	void logOut(UserId userId);
	void registerRoom(Room room, UserId userId);
	void unregisterRoom(Room room);
	std::vector<Room> getRooms();

	User* findUserById(UserId userId);
	Room* findRoomByName(const std::string& roomName);

	void processMessage(const EngineMessage& message);
	std::vector<EngineMessage> getMessages();

	/* These messages are to be called by the JSON processor
	 * for the purpose of good design, figure out how to somehow
	 * refactor this to better encapsulate this functionality.
	 * MessageParser can't be a friend class in the header because
	 * it creates a circular dependency. Maybe something like how the
	 * server class is separated from it's implementation in the
	 * network code? */

	void sendMessage(UserId toUserId, const std::string& text);
	void sendRoomMessage(Room* room, const std::string& text);
	void sendMessageToAll(const std::string& text);
    std::string generateRandomName();
	Room* getMainRoom();

private:
	UserMap users;
	RoomMap rooms;
	std::vector<EngineMessage> outgoing;

    std::vector<std::string> nicknameFirstHalf{"Amazing","Ambitious","Brave","Energetic","Flaming","Free","Green","Happy","Heroic","Large","Sneaky","Swift","The","Tiny"};
    std::vector<std::string> nicknameSecondHalf{"Rat","Ox","Tiger","Rabbit","Dragon","Snake","Horse","Goat","Monkey","Rooster","Dog","Pig"};
};


#endif //SOCIALGAMING_SERVERENGINE_H
