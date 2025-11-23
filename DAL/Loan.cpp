#include "Loan.h"
#include <sstream>

using namespace std;

Loan::Loan(const string& id,
           const string& userId,
           const string& documentId,
           bool returned)
    : id(id), userId(userId), documentId(documentId), returned(returned) {}

const string& Loan::GetId() const { return id; }
const string& Loan::GetUserId() const { return userId; }
const string& Loan::GetDocumentId() const { return documentId; }
bool Loan::IsReturned() const { return returned; }

void Loan::SetReturned(bool r) { returned = r; }

string Loan::Escape(const string& s) {
    ostringstream ss;
    for (char c : s) {
        switch (c) {
            case '\\': ss << "\\\\"; break;
            case '\"': ss << "\\\""; break;
            default: ss << c;
        }
    }
    return ss.str();
}

string Loan::Extract(const string& json, const string& key) {
    string t = "\"" + key + "\":";
    size_t start = json.find(t);
    if (start == string::npos) return "";

    start += t.size();

    if (json[start] == 't') return "true";
    if (json[start] == 'f') return "false";

    if (json[start] == '\"') {
        start++;
        size_t end = json.find("\"", start);
        return json.substr(start, end - start);
    }

    return "";
}

string Loan::ToJSON() const {
    ostringstream ss;
    ss << "{";
    ss << "\"id\":\"" << Escape(id) << "\",";
    ss << "\"userId\":\"" << Escape(userId) << "\",";
    ss << "\"documentId\":\"" << Escape(documentId) << "\",";
    ss << "\"returned\":" << (returned ? "true" : "false");
    ss << "}";
    return ss.str();
}

Loan Loan::FromJSON(const string& json) {
    bool ret = Extract(json, "returned") == "true";
    return Loan(
        Extract(json, "id"),
        Extract(json, "userId"),
        Extract(json, "documentId"),
        ret
    );
}
