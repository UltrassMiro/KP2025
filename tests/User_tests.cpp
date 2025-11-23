#include <gtest/gtest.h>
#include "../DAL/User.h"

TEST(User_Json, Roundtrip) {
    User u1("U1", "Ivan", "Petrenko", "IK-21");

    string json = u1.ToJSON();
    User u2 = User::FromJSON(json);

    EXPECT_EQ(u1.GetId(), u2.GetId());
    EXPECT_EQ(u1.GetFirstName(), u2.GetFirstName());
    EXPECT_EQ(u1.GetLastName(), u2.GetLastName());
    EXPECT_EQ(u1.GetGroup(), u2.GetGroup());
}

TEST(User_Setters, ChangeFields) {
    User u("U1", "A", "B", "C");

    u.SetFirstName("X");
    u.SetLastName("Y");
    u.SetGroup("Z");

    EXPECT_EQ(u.GetFirstName(), "X");
    EXPECT_EQ(u.GetLastName(), "Y");
    EXPECT_EQ(u.GetGroup(), "Z");
}
