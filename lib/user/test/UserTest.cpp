#include "gtest/gtest.h"
#include "User.h"

TEST(UserTest, testId) {
	User user = User("TestUser");
	EXPECT_GE(user.getUserId(), 0);
	EXPECT_LT(user.getUserId(), 65535);
}

TEST(UserTest, testSetName)
{
	User user = User("TestUser");
	EXPECT_EQ(user.getName(), "TestUser");

	user.setName("newName");
	EXPECT_EQ(user.getName(), "newName");

}

TEST(UserTest, testEquals) {
	User user = User("TestUser");
	User user2 = User("secondUser");

	EXPECT_FALSE(user == user2);
	EXPECT_TRUE(user == user);
}
