#include <gtest/gtest.h>
#include "../BLL/LoanService.h"
#include "../BLL/DocumentService.h"
#include "../BLL/UserService.h"
#include "../DAL/EntityContext.h"
#include "../DAL/JsonProvider.h"

TEST(LoanService_Issue, BasicIssue) {
    JsonProvider provider;
    EntityContext ctx(&provider);

    ctx.Users.push_back(User("U1", "Ivan", "I", "IK-11"));
    ctx.Documents.push_back(Document("D1", "Book", "A", 2020));

    LoanService svc(&ctx);

    svc.IssueDocument("U1", "D1");

    EXPECT_EQ(ctx.Loans.size(), 1);
    EXPECT_EQ(ctx.Loans[0].GetUserId(), "U1");
    EXPECT_EQ(ctx.Loans[0].GetDocumentId(), "D1");
}

TEST(LoanService_Issue, MaxLimit) {
    JsonProvider provider;
    EntityContext ctx(&provider);

    ctx.Users.push_back(User("U1", "Ivan", "I", "IK-11"));
    for (int i = 1; i <= 5; i++)
        ctx.Documents.push_back(Document("D" + to_string(i), "B", "A", 2020));

    LoanService svc(&ctx);

    svc.IssueDocument("U1", "D1");
    svc.IssueDocument("U1", "D2");
    svc.IssueDocument("U1", "D3");
    svc.IssueDocument("U1", "D4");

    EXPECT_THROW(svc.IssueDocument("U1", "D5"), DomainException);
}

TEST(LoanService_Issue, DocumentNotFound) {
    JsonProvider provider;
    EntityContext ctx(&provider);

    ctx.Users.push_back(User("U1", "Ivan", "I", "IK-11"));

    LoanService svc(&ctx);

    EXPECT_THROW(svc.IssueDocument("U1", "Missing"), DomainException);
}

TEST(LoanService_Return, Basic) {
    JsonProvider provider;
    EntityContext ctx(&provider);

    ctx.Users.push_back(User("U1", "Ivan", "I", "IK-11"));
    ctx.Documents.push_back(Document("D1", "Book", "A", 2020));
    ctx.Loans.push_back(Loan("L1", "U1", "D1", false));

    LoanService svc(&ctx);

    svc.ReturnDocument("U1", "D1");

    EXPECT_TRUE(ctx.Loans[0].IsReturned());
}

TEST(LoanService_WhoHasDocument, IssueAndCheck) {
    JsonProvider provider;
    EntityContext ctx(&provider);

    ctx.Users.push_back(User("U1", "Ivan", "I", "IK-11"));
    ctx.Documents.push_back(Document("D1", "Book", "A", 2020));

    LoanService svc(&ctx);

    string uid;
    EXPECT_TRUE(svc.IsDocumentInLibrary("D1", uid));
    EXPECT_EQ(uid, "");

    svc.IssueDocument("U1", "D1");

    EXPECT_FALSE(svc.IsDocumentInLibrary("D1", uid));
    EXPECT_EQ(uid, "U1");
}
