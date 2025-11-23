#include "EntityContext.h"

using namespace std;

EntityContext::EntityContext(IDataProvider* p)
    : provider(p) {}

void EntityContext::Load(const string& usersFile,
                         const string& docsFile,
                         const string& loansFile) {
    Users     = provider->LoadUsers(usersFile);
    Documents = provider->LoadDocuments(docsFile);
    Loans     = provider->LoadLoans(loansFile);
}

void EntityContext::Save(const string& usersFile,
                         const string& docsFile,
                         const string& loansFile) {
    provider->SaveUsers(Users, usersFile);
    provider->SaveDocuments(Documents, docsFile);
    provider->SaveLoans(Loans, loansFile);
}
