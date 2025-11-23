#include "ConsoleView.h"
#include <iostream>
#include "../DAL/DalException.h"

using namespace std;

ConsoleView::ConsoleView(UserService& us,
                         DocumentService& ds,
                         LoanService& ls)
    : userService(us),
      docService(ds),
      loanService(ls) {}

int ConsoleView::ReadInt(const string& prompt) {
    while (true) {
        cout << prompt;
        int val;
        if (cin >> val) {
            cin.ignore(10000, '\n');
            return val;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Incorrect number, try again.\n";
    }
}

string ConsoleView::ReadString(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

void ConsoleView::ShowMessage(const string& msg) {
    cout << msg << "\n";
}

void ConsoleView::Run() {
    MainMenu();
}

void ConsoleView::MainMenu() {
    while (true) {
        cout << "\n===== Students Library =====\n";
        cout << "1. Users\n";
        cout << "2. Documents\n";
        cout << "3. Loans\n";
        cout << "4. Global search\n";
        cout << "0. Exit\n";

        int cmd = ReadInt("Command: ");

        try {
            switch (cmd) {
                case 1: MenuUsers(); break;
                case 2: MenuDocuments(); break;
                case 3: MenuLoans(); break;
                case 4: MenuSearchGeneral(); break;
                case 0: return;
                default: ShowMessage("Error! Wrong command!"); break;
            }
        }
        catch (const DomainException& ex) {
            ShowMessage(string("Business logic error: ") + ex.what());
        }
        catch (const DalException& ex) {
            ShowMessage(string("Data access error: ") + ex.what());
        }
    }
}

// USERS

void ConsoleView::MenuUsers() {
    while (true) {
        cout << "\n===== Users =====\n";
        cout << "1. Add user\n";
        cout << "2. Remove user\n";
        cout << "3. Edit user info\n";
        cout << "4. Inspect user info\n";
        cout << "5. List all users\n";
        cout << "6. Search users\n";
        cout << "7. Sort by first name\n";
        cout << "8. Sort by last name\n";
        cout << "9. Sort by group\n";
        cout << "0. Back\n";

        int cmd = ReadInt("Command: ");

        switch (cmd) {
            case 1: AddUser(); break;
            case 2: RemoveUser(); break;
            case 3: EditUser(); break;
            case 4: ShowUser(); break;
            case 5: ListUsers(); break;
            case 6: SearchUsers(); break;
            case 7: SortUsersByFirstName(); break;
            case 8: SortUsersByLastName(); break;
            case 9: SortUsersByGroup(); break;
            case 0: return;
            default: ShowMessage("Error! Wrong command!");
        }
    }
}

void ConsoleView::AddUser() {
    string id = ReadString("ID: ");
    string first = ReadString("Name: ");
    string last = ReadString("Surname: ");
    string group = ReadString("Group: ");

    userService.AddUser(User(id, first, last, group));
    ShowMessage("User added.");
}

void ConsoleView::RemoveUser() {
    string id = ReadString("User ID: ");
    userService.RemoveUser(id);
    ShowMessage("Removed.");
}

void ConsoleView::EditUser() {
    string id = ReadString("ID: ");
    string fn = ReadString("New name: ");
    string ln = ReadString("New surname: ");
    string gr = ReadString("New group: ");
    userService.UpdateUser(id, fn, ln, gr);
    ShowMessage("Info updated.");
}

void ConsoleView::ShowUser() {
    string id = ReadString("ID: ");
    User u = userService.GetById(id);

    cout << "\nID: " << u.GetId() << "\n";
    cout << "Name: " << u.GetFirstName() << "\n";
    cout << "Surname: " << u.GetLastName() << "\n";
    cout << "Group: " << u.GetGroup() << "\n";
}

void ConsoleView::ListUsers() {
    auto list = userService.GetAll();

    cout << "\n===== User list =====\n";
    for (auto& u : list) {
        cout << u.GetId() << " | "
             << u.GetFirstName() << " "
             << u.GetLastName() << " | "
             << u.GetGroup() << "\n";
    }
}

void ConsoleView::SearchUsers() {
    string key = ReadString("Key word: ");
    auto list = userService.FindByKeyword(key);

    cout << "\n===== Users found =====\n";
    for (auto& u : list) {
        cout << u.GetId() << " | "
             << u.GetFirstName() << " "
             << u.GetLastName() << "\n";
    }
}

// SORT USERS

void ConsoleView::SortUsersByFirstName() {
    auto list = userService.SortByFirstName();

    cout << "\n===== Users sorted by FIRST NAME =====\n";
    for (auto& u : list) {
        cout << u.GetFirstName() << " "
             << u.GetLastName() << " | "
             << u.GetGroup() << " | ID: " << u.GetId() << "\n";
    }
}

void ConsoleView::SortUsersByLastName() {
    auto list = userService.SortByLastName();

    cout << "\n===== Users sorted by LAST NAME =====\n";
    for (auto& u : list) {
        cout << u.GetLastName() << ", "
             << u.GetFirstName() << " | "
             << u.GetGroup() << " | ID: " << u.GetId() << "\n";
    }
}

void ConsoleView::SortUsersByGroup() {
    auto list = userService.SortByGroup();

    cout << "\n===== Users sorted by GROUP =====\n";
    for (auto& u : list) {
        cout << u.GetGroup() << " | "
             << u.GetFirstName() << " "
             << u.GetLastName() << " | "
             << u.GetId() << "\n";
    }
}

// DOCUMENTS

void ConsoleView::MenuDocuments() {
    while (true) {
        cout << "\n===== Documents =====\n";
        cout << "1. Add document\n";
        cout << "2. Remove document\n";
        cout << "3. Edit document\n";
        cout << "4. Inspect document\n";
        cout << "5. List\n";
        cout << "6. Search\n";
        cout << "7. Sort by title\n";
        cout << "8. Sort by author\n";
        cout << "9. Sort by year\n";
        cout << "0. Back\n";

        int cmd = ReadInt("Command: ");

        switch (cmd) {
            case 1: AddDocument(); break;
            case 2: RemoveDocument(); break;
            case 3: EditDocument(); break;
            case 4: ShowDocument(); break;
            case 5: ListDocuments(); break;
            case 6: SearchDocuments(); break;
            case 7: SortDocumentsByTitle(); break;
            case 8: SortDocumentsByAuthor(); break;
            case 9: SortDocumentsByYear(); break;
            case 0: return;
        }
    }
}

void ConsoleView::AddDocument() {
    string id = ReadString("Document ID: ");
    string title = ReadString("Name: ");
    string author = ReadString("Author: ");
    int year = ReadInt("Year: ");

    docService.AddDocument(Document(id, title, author, year));
    ShowMessage("Document added.");
}

void ConsoleView::RemoveDocument() {
    string id = ReadString("Document ID: ");
    docService.RemoveDocument(id);
    ShowMessage("Removed.");
}

void ConsoleView::EditDocument() {
    string id = ReadString("Document ID: ");
    string title = ReadString("New name: ");
    string author = ReadString("New author: ");
    int year = ReadInt("New year: ");

    docService.UpdateDocument(id, title, author, year);
    ShowMessage("Updated.");
}

void ConsoleView::ShowDocument() {
    string id = ReadString("ID: ");
    Document d = docService.GetById(id);

    cout << "\nID: " << d.GetId() << "\n"
         << "Title: " << d.GetTitle() << "\n"
         << "Author: " << d.GetAuthor() << "\n"
         << "Year: " << d.GetYear() << "\n";
}

void ConsoleView::ListDocuments() {
    auto list = docService.GetAll();
    cout << "\n===== Documents =====\n";

    for (auto& d : list) {
        cout << d.GetId() << " | "
             << d.GetTitle() << " | "
             << d.GetAuthor() << " | "
             << d.GetYear() << "\n";
    }
}

void ConsoleView::SearchDocuments() {
    string key = ReadString("Key word: ");
    auto list = docService.FindByTitleSubstring(key);

    cout << "\n===== Found documents =====\n";
    for (auto& d : list) {
        cout << d.GetId() << " | " << d.GetTitle() << "\n";
    }
}

// SORT DOCUMENTS

void ConsoleView::SortDocumentsByTitle() {
    auto list = docService.SortByTitle();

    cout << "\n===== Documents sorted by TITLE =====\n";
    for (auto& d : list) {
        cout << d.GetTitle() << " | "
             << d.GetAuthor() << " | "
             << d.GetYear() << " | ID: " << d.GetId() << "\n";
    }
}

void ConsoleView::SortDocumentsByAuthor() {
    auto list = docService.SortByAuthor();

    cout << "\n===== Documents sorted by AUTHOR =====\n";
    for (auto& d : list) {
        cout << d.GetAuthor() << " | "
             << d.GetTitle() << " | "
             << d.GetYear() << " | ID: " << d.GetId() << "\n";
    }
}

void ConsoleView::SortDocumentsByYear() {
    auto list = docService.SortByYear();

    cout << "\n===== Documents sorted by YEAR =====\n";
    for (auto& d : list) {
        cout << d.GetYear() << " | "
             << d.GetTitle() << " | "
             << d.GetAuthor() << " | ID: " << d.GetId() << "\n";
    }
}

// LOANS

void ConsoleView::MenuLoans() {
    while (true) {
        cout << "\n===== Loans =====\n";
        cout << "1. Loan a document\n";
        cout << "2. Return document\n";
        cout << "3. Search document holder\n";
        cout << "4. User's documents\n";
        cout << "0. Back\n";

        int cmd = ReadInt("Command: ");

        switch (cmd) {
            case 1: IssueDocument(); break;
            case 2: ReturnDocument(); break;
            case 3: WhoHasDocument(); break;
            case 4: UserDocuments(); break;
            case 0: return;
        }
    }
}

void ConsoleView::IssueDocument() {
    string userId = ReadString("User ID: ");
    string docId = ReadString("Document ID: ");

    loanService.IssueDocument(userId, docId);
    ShowMessage("Document has been loaned.");
}

void ConsoleView::ReturnDocument() {
    string userId = ReadString("User ID: ");
    string docId = ReadString("Document ID: ");

    loanService.ReturnDocument(userId, docId);
    ShowMessage("Returned.");
}

void ConsoleView::WhoHasDocument() {
    string id = ReadString("Document ID: ");
    string user;

    bool isHere = loanService.IsDocumentInLibrary(id, user);

    if (isHere) {
        ShowMessage("Document is in the library.");
    } else {
        ShowMessage("Document was loaned to: " + user);
    }
}

void ConsoleView::UserDocuments() {
    string uid = ReadString("User ID: ");
    auto list = loanService.GetDocumentsOfUser(uid);

    cout << "===== Documents loaned to user =====\n";
    for (auto& d : list) {
        cout << d.GetId() << " | "
             << d.GetTitle() << " | "
             << d.GetAuthor() << "\n";
    }
}

// GLOBAL SEARCH

void ConsoleView::MenuSearchGeneral() {
    cout << "\n===== Global search =====\n";
    string key = ReadString("Key word: ");

    auto docs = docService.FindByTitleSubstring(key);
    auto users = userService.FindByKeyword(key);

    cout << "\nFound documents\n";
    for (auto& d : docs)
        cout << d.GetId() << " | " << d.GetTitle() << "\n";

    cout << "\nFound users\n";
    for (auto& u : users)
        cout << u.GetId() << " | "
             << u.GetFirstName() << " "
             << u.GetLastName() << "\n";
}
