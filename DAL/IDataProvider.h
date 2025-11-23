#pragma once
#include <vector>
#include <string>
#include "User.h"
#include "Document.h"
#include "Loan.h"

using namespace std;

class IDataProvider {
public:
    virtual ~IDataProvider() = default;

    virtual void SaveUsers(const vector<User>& users,
                           const string& filename) = 0;

    virtual vector<User> LoadUsers(const string& filename) = 0;

    virtual void SaveDocuments(const vector<Document>& docs,
                               const string& filename) = 0;

    virtual vector<Document> LoadDocuments(const string& filename) = 0;

    virtual void SaveLoans(const vector<Loan>& loans,
                           const string& filename) = 0;

    virtual vector<Loan> LoadLoans(const string& filename) = 0;
};
