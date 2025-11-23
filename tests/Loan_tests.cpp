#include <gtest/gtest.h>
#include "../DAL/Loan.h"

TEST(Loan_Json, Roundtrip) {
    Loan l1("L1", "U1", "D1", false);

    string json = l1.ToJSON();
    Loan l2 = Loan::FromJSON(json);

    EXPECT_EQ(l1.GetId(), l2.GetId());
    EXPECT_EQ(l1.GetUserId(), l2.GetUserId());
    EXPECT_EQ(l1.GetDocumentId(), l2.GetDocumentId());
    EXPECT_EQ(l1.IsReturned(), l2.IsReturned());
}

TEST(Loan_SetReturned, SetsCorrectly) {
    Loan l("L1", "U1", "D1", false);
    l.SetReturned(true);
    EXPECT_TRUE(l.IsReturned());
}
