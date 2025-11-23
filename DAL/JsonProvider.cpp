#include "JsonProvider.h"
#include "DalException.h"
#include <fstream>

using namespace std;

vector<string> JsonProvider::ReadLines(const string& file) {
    ifstream ifs(file);
    if (!ifs.is_open()) return {};

    vector<string> lines;
    string line;

    while (getline(ifs, line))
        if (!line.empty())
            lines.push_back(line);

    return lines;
}

void JsonProvider::WriteLines(const vector<string>& lines,
                              const string& file) {
    ofstream ofs(file);
    if (!ofs.is_open())
        throw DalException("Cannot open file: " + file);

    for (const auto& l : lines)
        ofs << l << "\n";
}

void JsonProvider::SaveUsers(const vector<User>& users,
                             const string& file) {
    vector<string> lines;
    for (const auto& u : users)
        lines.push_back(u.ToJSON());
    WriteLines(lines, file);
}

vector<User> JsonProvider::LoadUsers(const string& file) {
    auto lines = ReadLines(file);
    vector<User> out;
    for (auto& l : lines)
        out.push_back(User::FromJSON(l));
    return out;
}

void JsonProvider::SaveDocuments(const vector<Document>& docs,
                                 const string& file) {
    vector<string> lines;
    for (const auto& d : docs)
        lines.push_back(d.ToJSON());
    WriteLines(lines, file);
}

vector<Document> JsonProvider::LoadDocuments(const string& file) {
    auto lines = ReadLines(file);
    vector<Document> out;
    for (auto& l : lines)
        out.push_back(Document::FromJSON(l));
    return out;
}

void JsonProvider::SaveLoans(const vector<Loan>& loans,
                             const string& file) {
    vector<string> lines;
    for (const auto& l : loans)
        lines.push_back(l.ToJSON());
    WriteLines(lines, file);
}

vector<Loan> JsonProvider::LoadLoans(const string& file) {
    auto lines = ReadLines(file);
    vector<Loan> out;
    for (auto& l : lines)
        out.push_back(Loan::FromJSON(l));
    return out;
}
