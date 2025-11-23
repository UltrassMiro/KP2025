#include <gtest/gtest.h>
#include "../DAL/Document.h"

TEST(Document_Json, Roundtrip) {
    Document d1("D1", "Book", "Author", 2020);

    string json = d1.ToJSON();
    Document d2 = Document::FromJSON(json);

    EXPECT_EQ(d1.GetId(), d2.GetId());
    EXPECT_EQ(d1.GetTitle(), d2.GetTitle());
    EXPECT_EQ(d1.GetAuthor(), d2.GetAuthor());
    EXPECT_EQ(d1.GetYear(), d2.GetYear());
}

TEST(Document_Setters, ChangeFields) {
    Document d("D1", "A", "B", 1999);

    d.SetTitle("T");
    d.SetAuthor("AU");
    d.SetYear(2001);

    EXPECT_EQ(d.GetTitle(), "T");
    EXPECT_EQ(d.GetAuthor(), "AU");
    EXPECT_EQ(d.GetYear(), 2001);
}
