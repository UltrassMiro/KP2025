#include "DAL/JsonProvider.h"
#include "DAL/EntityContext.h"
#include "BLL/UserService.h"
#include "BLL/DocumentService.h"
#include "BLL/LoanService.h"
#include "PL/ConsoleView.h"

using namespace std;

int main() {
    JsonProvider provider;
    EntityContext ctx(&provider);

    string usersFile = "users.txt";
    string docsFile  = "documents.txt";
    string loansFile = "loans.txt";

    ctx.Load(usersFile, docsFile, loansFile);

    UserService userSvc(&ctx);
    DocumentService docSvc(&ctx);
    LoanService loanSvc(&ctx);

    ConsoleView view(userSvc, docSvc, loanSvc);
    view.Run();

    ctx.Save(usersFile, docsFile, loansFile);

    return 0;
}
