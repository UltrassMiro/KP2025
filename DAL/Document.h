#pragma once
#include <string>

using namespace std;

class Document {
private:
    string id;
    string title;
    string author;
    int year{};

public:
    Document() = default;

    Document(const string& id,
             const string& title,
             const string& author,
             int year);

    const string& GetId() const;
    const string& GetTitle() const;
    const string& GetAuthor() const;
    int GetYear() const;

    void SetTitle(const string& v);
    void SetAuthor(const string& v);
    void SetYear(int v);

    string ToJSON() const;
    static Document FromJSON(const string& json);

private:
    static string Escape(const string& s);
    static string Extract(const string& json, const string& key);
};
