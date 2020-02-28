#include "gtest/gtest.h"
#include "User.h"

TEST(UserTest, testName)
{
	User user = User("TestUser");
	EXPECT_EQ(user.getName(), "TestUser");
	EXPECT_GE(user.getUserId(), 0);
	EXPECT_LT(user.getUserId(), 65535);

	user.setName("newName");
	EXPECT_EQ(user.getName(), "newName");

	User user2 = User("secondUser");

	EXPECT_FALSE(user == user2);
	EXPECT_TRUE(user == user);
}


