#include <gtest/gtest.h>
#include "../BLL/DocumentService.h"
#include "../DAL/EntityContext.h"
#include "../DAL/JsonProvider.h"

TEST(DocumentService_BasicCRUD, Add_Update_Remove) {
    JsonProvider provider;
    EntityContext ctx(&provider);
    DocumentService svc(&ctx);

    svc.AddDocument(Document("D1", "Book", "Author", 2020));
    EXPECT_EQ(svc.GetAll().size(), 1);

    svc.UpdateDocument("D1", "NewBook", "NewAuthor", 2024);

    Document d = svc.GetById("D1");
    EXPECT_EQ(d.GetTitle(), "NewBook");
    EXPECT_EQ(d.GetAuthor(), "NewAuthor");
    EXPECT_EQ(d.GetYear(), 2024);

    svc.RemoveDocument("D1");
    EXPECT_TRUE(svc.GetAll().empty());
}

TEST(DocumentService_Search, TitleSubstring) {
    JsonProvider provider;
    EntityContext ctx(&provider);
    DocumentService svc(&ctx);

    svc.AddDocument(Document("1", "Data Structures", "Smith", 2020));
    svc.AddDocument(Document("2", "Databases", "John", 2019));

    auto r = svc.FindByTitleSubstring("Data");

    EXPECT_EQ(r.size(), 2);
}
