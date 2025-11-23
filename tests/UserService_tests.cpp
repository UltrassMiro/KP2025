#include <gtest/gtest.h>
#include "../BLL/UserService.h"
#include "../DAL/EntityContext.h"
#include "../DAL/JsonProvider.h"

TEST(UserService_BasicCRUD, Add_Update_Remove) {
    JsonProvider provider;
    EntityContext ctx(&provider);
    UserService svc(&ctx);

    svc.AddUser(User("U1", "Ivan", "Ivanov", "IK-11"));
    EXPECT_EQ(svc.GetAll().size(), 1);

    svc.UpdateUser("U1", "Petro", "Petrenko", "IK-22");

    User u = svc.GetById("U1");
    EXPECT_EQ(u.GetFirstName(), "Petro");
    EXPECT_EQ(u.GetLastName(), "Petrenko");
    EXPECT_EQ(u.GetGroup(), "IK-22");

    svc.RemoveUser("U1");
    EXPECT_TRUE(svc.GetAll().empty());
}

TEST(UserService_Search, Keyword) {
    JsonProvider provider;
    EntityContext ctx(&provider);
    UserService svc(&ctx);

    svc.AddUser(User("1", "Andrii", "Koval", "IK-31"));
    svc.AddUser(User("2", "Oleh", "Andrienko", "IK-31"));

    auto r = svc.FindByKeyword("And");
    EXPECT_EQ(r.size(), 2);
}
