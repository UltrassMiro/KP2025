#include "Document.h"
#include <sstream>

using namespace std;

Document::Document(const string& id,
                   const string& title,
                   const string& author,
                   int year)
    : id(id), title(title), author(author), year(year) {}

const string& Document::GetId() const { return id; }
const string& Document::GetTitle() const { return title; }
const string& Document::GetAuthor() const { return author; }
int Document::GetYear() const { return year; }

void Document::SetTitle(const string& v) { title = v; }
void Document::SetAuthor(const string& v) { author = v; }
void Document::SetYear(int v) { year = v; }

string Document::Escape(const string& s) {
    ostringstream ss;
    for (char c : s) {
        switch (c) {
            case '\\': ss << "\\\\"; break;
            case '\"': ss << "\\\""; break;
            default: ss << c; break;
        }
    }
    return ss.str();
}

string Document::Extract(const string& json, const string& key) {
    string token = "\"" + key + "\":\"";
    size_t start = json.find(token);
    if (start == string::npos) {
        // year — число
        token = "\"" + key + "\":";
        start = json.find(token);
        if (start == string::npos) return "";
        start += token.size();
        size_t end = json.find_first_of(",}", start);
        return json.substr(start, end - start);
    }

    start += token.size();
    size_t end = json.find("\"", start);
    return json.substr(start, end - start);
}

string Document::ToJSON() const {
    ostringstream ss;
    ss << "{";
    ss << "\"id\":\"" << Escape(id) << "\",";
    ss << "\"title\":\"" << Escape(title) << "\",";
    ss << "\"author\":\"" << Escape(author) << "\",";
    ss << "\"year\":" << year;
    ss << "}";
    return ss.str();
}

Document Document::FromJSON(const string& json) {
    int y = stoi(Extract(json, "year"));
    return Document(
        Extract(json, "id"),
        Extract(json, "title"),
        Extract(json, "author"),
        y
    );
}
