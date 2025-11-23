#pragma once
#include "User.h"
#include "Document.h"
#include "Loan.h"
#include "IDataProvider.h"
#include <vector>

using namespace std;

class EntityContext {
private:
    IDataProvider* provider;

public:
    vector<User> Users;
    vector<Document> Documents;
    vector<Loan> Loans;

    explicit EntityContext(IDataProvider* p);

    void Load(const string& usersFile,
              const string& docsFile,
              const string& loansFile);

    void Save(const string& usersFile,
              const string& docsFile,
              const string& loansFile);
};
