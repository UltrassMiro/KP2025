#pragma once
#include "IDataProvider.h"

using namespace std;

class JsonProvider : public IDataProvider {
public:
    void SaveUsers(const vector<User>& users,
                   const string& filename) override;

    vector<User> LoadUsers(const string& filename) override;

    void SaveDocuments(const vector<Document>& docs,
                       const string& filename) override;

    vector<Document> LoadDocuments(const string& filename) override;

    void SaveLoans(const vector<Loan>& loans,
                   const string& filename) override;

    vector<Loan> LoadLoans(const string& filename) override;

private:
    static vector<string> ReadLines(const string& file);
    static void WriteLines(const vector<string>& lines,
                           const string& file);
};
