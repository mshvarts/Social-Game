#include "gtest/gtest.h"
#include "Room.h"
#include "User.h"

TEST(RoomTest, testName)
{
	// Check initialization
	Room room = Room("Room1");
	EXPECT_EQ(room.getRoomName(), "Room1");

	room.setRoomName("Room2");
	EXPECT_EQ(room.getRoomName(), "Room2");
	EXPECT_NE(room.getRoomName(), "Room1");

}

TEST(RoomTest, testNumOfPlayers) {

	Room room = Room("Room1");
	User user = User("Bob");
	room.addUser(user.getUserId());
	EXPECT_EQ(room.getNumOfPlayers(), 1);

	room.removeUser(user.getUserId());
	EXPECT_EQ(room.getNumOfPlayers(), 0);
}

// TODO: find a way to retrieve username from userlist
/*TEST(RoomTest, testUserList) {
	Room room = Room("Room1");
	User user = User("John");
	room.addUser(user.getUserId());
	cout << room.getUserList();
	EXPECT_EQ(std::get<1>(room.getUserList()[0]), "John");
}*/