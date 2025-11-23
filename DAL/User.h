#pragma once
#include <string>

using namespace std;

class User {
private:
    string id;
    string firstName;
    string lastName;
    string group;

public:
    User() = default;

    User(const string& id,
         const string& first,
         const string& last,
         const string& group);

    const string& GetId() const;
    const string& GetFirstName() const;
    const string& GetLastName() const;
    const string& GetGroup() const;

    void SetFirstName(const string& v);
    void SetLastName(const string& v);
    void SetGroup(const string& v);

    string ToJSON() const;
    static User FromJSON(const string& json);

private:
    static string Escape(const string& s);
    static string Extract(const string& json, const string& key);
};
