#include "User.h"
#include <sstream>

using namespace std;

User::User(const string& id,
           const string& first,
           const string& last,
           const string& group)
    : id(id), firstName(first), lastName(last), group(group) {}

const string& User::GetId() const { return id; }
const string& User::GetFirstName() const { return firstName; }
const string& User::GetLastName() const { return lastName; }
const string& User::GetGroup() const { return group; }

void User::SetFirstName(const string& v) { firstName = v; }
void User::SetLastName(const string& v) { lastName = v; }
void User::SetGroup(const string& v) { group = v; }

string User::Escape(const string& s) {
    ostringstream ss;
    for (char c : s) {
        switch (c) {
            case '\\': ss << "\\\\"; break;
            case '\"': ss << "\\\""; break;
            case '\n': ss << "\\n"; break;
            case '\r': ss << "\\r"; break;
            case '\t': ss << "\\t"; break;
            default: ss << c; break;
        }
    }
    return ss.str();
}

string User::Extract(const string& json, const string& key) {
    string token = "\"" + key + "\":\"";
    size_t start = json.find(token);
    if (start == string::npos) return "";

    start += token.size();
    size_t end = json.find("\"", start);
    return json.substr(start, end - start);
}

string User::ToJSON() const {
    ostringstream ss;
    ss << "{";
    ss << "\"id\":\"" << Escape(id) << "\",";
    ss << "\"firstName\":\"" << Escape(firstName) << "\",";
    ss << "\"lastName\":\"" << Escape(lastName) << "\",";
    ss << "\"group\":\"" << Escape(group) << "\"";
    ss << "}";
    return ss.str();
}

User User::FromJSON(const string& json) {
    return User(
        Extract(json, "id"),
        Extract(json, "firstName"),
        Extract(json, "lastName"),
        Extract(json, "group")
    );
}
