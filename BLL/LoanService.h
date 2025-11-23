#pragma once
#include <vector>
#include <string>
#include "../DAL/EntityContext.h"
#include "DomainException.h"
#include "Repository.h"

using namespace std;

class LoanService {
private:
    EntityContext* ctx;
    Repository<Loan> repo;

public:
    explicit LoanService(EntityContext* context);

    // Видача документа користувачу
    void IssueDocument(const string& userId,
                       const string& documentId);

    // Список взятих користувачем документів
    vector<Document> GetDocumentsOfUser(const string& userId) const;

    // Пошук документа
    bool IsDocumentInLibrary(const string& documentId,
                             string& outUserId) const;

    // Повернення документа
    void ReturnDocument(const string& userId,
                        const string& documentId);
};
