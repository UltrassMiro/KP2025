#include "LoanService.h"
#include <algorithm>

using namespace std;

LoanService::LoanService(EntityContext* context)
    : ctx(context),
      repo(&context->Loans) {
    if (!ctx) {
        throw DomainException("LoanService: context is null");
    }
}

void LoanService::IssueDocument(const string& userId,
                                const string& documentId) {
    // Перевірка користувача
    auto userIt = find_if(ctx->Users.begin(), ctx->Users.end(),
                          [&](const User& u) {
                              return u.GetId() == userId;
                          });
    if (userIt == ctx->Users.end()) {
        throw DomainException("User not found");
    }

    // Перевірка документа
    auto docIt = find_if(ctx->Documents.begin(), ctx->Documents.end(),
                         [&](const Document& d) {
                             return d.GetId() == documentId;
                         });
    if (docIt == ctx->Documents.end()) {
        throw DomainException("Document not found");
    }

    // Чи документ вже виданий
    for (const auto& l : ctx->Loans) {
        if (l.GetDocumentId() == documentId && !l.IsReturned()) {
            throw DomainException("Document is already issued");
        }
    }

    int active = 0;
    for (const auto& l : ctx->Loans) {
        if (l.GetUserId() == userId && !l.IsReturned()) {
            active++;
        }
    }

    if (active >= 4) {
        throw DomainException("User exceeded max number of active loans (4)");
    }

    // Створення нової видачі
    string loanId = "L" + to_string(ctx->Loans.size() + 1);
    ctx->Loans.emplace_back(loanId, userId, documentId, false);
}

vector<Document> LoanService::GetDocumentsOfUser(const string& userId) const {
    vector<Document> result;

    for (const auto& l : ctx->Loans) {
        if (l.GetUserId() == userId && !l.IsReturned()) {
            auto docIt = find_if(ctx->Documents.begin(), ctx->Documents.end(),
                                 [&](const Document& d) {
                                     return d.GetId() == l.GetDocumentId();
                                 });
            if (docIt != ctx->Documents.end()) {
                result.push_back(*docIt);
            }
        }
    }

    return result;
}

bool LoanService::IsDocumentInLibrary(const string& documentId,
                                      string& outUserId) const {
    for (const auto& l : ctx->Loans) {
        if (l.GetDocumentId() == documentId && !l.IsReturned()) {
            outUserId = l.GetUserId();
            return false;
        }
    }

    outUserId.clear();
    return true;
}

void LoanService::ReturnDocument(const string& userId,
                                 const string& documentId) {
    auto* loan = repo.FindOne([&](const Loan& l) {
        return l.GetUserId() == userId &&
               l.GetDocumentId() == documentId &&
               !l.IsReturned();
    });

    if (!loan) {
        throw DomainException("Active loan not found for this user and document");
    }

    loan->SetReturned(true);
}
