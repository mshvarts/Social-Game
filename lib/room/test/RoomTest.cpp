#include "gtest/gtest.h"
#include "Room.h"

TEST(RoomTest, testName)
{
	// Check initialization
	Room room = Room("Room1");
	EXPECT_EQ(room.getNumOfPlayers(), 0);
	EXPECT_EQ(room.getRoomName(), "Room1");

	room.setRoomName("Room2");
	EXPECT_EQ(room.getRoomName(), "Room2");
	EXPECT_NE(room.getRoomName(), "Room1");
}


