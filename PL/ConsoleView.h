#pragma once
#include <string>
#include "../BLL/UserService.h"
#include "../BLL/DocumentService.h"
#include "../BLL/LoanService.h"

using namespace std;

class ConsoleView {
private:
    UserService& userService;
    DocumentService& docService;
    LoanService& loanService;

    int ReadInt(const string& prompt);
    string ReadString(const string& prompt);

    void ShowMessage(const string& msg);

    /// USERS
    void MenuUsers();
    void AddUser();
    void RemoveUser();
    void EditUser();
    void ShowUser();
    void ListUsers();
    void SearchUsers();

    // Sorting users
    void SortUsersByFirstName();
    void SortUsersByLastName();
    void SortUsersByGroup();

    /// DOCUMENTS
    void MenuDocuments();
    void AddDocument();
    void RemoveDocument();
    void EditDocument();
    void ShowDocument();
    void ListDocuments();
    void SearchDocuments();

    // Sorting documents
    void SortDocumentsByTitle();
    void SortDocumentsByAuthor();
    void SortDocumentsByYear();

    /// LOANS
    void MenuLoans();
    void IssueDocument();
    void ReturnDocument();
    void WhoHasDocument();
    void UserDocuments();

    /// GLOBAL SEARCH
    void MenuSearchGeneral();

public:
    ConsoleView(UserService& us,
                DocumentService& ds,
                LoanService& ls);

    void Run();
    void MainMenu();
};
