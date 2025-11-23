#pragma once
#include <string>

using namespace std;

class Loan {
private:
    string id;
    string userId;
    string documentId;
    bool returned;

public:
    Loan() : returned(false) {}

    Loan(const string& id,
         const string& userId,
         const string& documentId,
         bool returned = false);

    const string& GetId() const;
    const string& GetUserId() const;
    const string& GetDocumentId() const;
    bool IsReturned() const;

    void SetReturned(bool r);

    string ToJSON() const;
    static Loan FromJSON(const string& json);

private:
    static string Escape(const string& s);
    static string Extract(const string& json, const string& key);
};
