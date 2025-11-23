#include "UserService.h"
#include <algorithm>

using namespace std;

UserService::UserService(EntityContext* context)
    : ctx(context),
      repo(&context->Users) {
    if (!ctx) {
        throw DomainException("UserService: context is null");
    }
}

void UserService::AddUser(const User& u) {
    auto* existing = repo.FindOne([&](const User& x) {
        return x.GetId() == u.GetId();
    });

    if (existing) {
        throw DomainException("User with this ID already exists");
    }

    repo.GetAll().push_back(u);
}

void UserService::RemoveUser(const string& userId) {
    auto& all = repo.GetAll();
    auto it = remove_if(all.begin(), all.end(),
                        [&](const User& u) {
                            return u.GetId() == userId;
                        });
    if (it == all.end()) {
        throw DomainException("User not found");
    }
    all.erase(it, all.end());
}

void UserService::UpdateUser(const string& userId,
                             const string& newFirst,
                             const string& newLast,
                             const string& newGroup) {
    auto* u = repo.FindOne([&](const User& x) {
        return x.GetId() == userId;
    });

    if (!u) {
        throw DomainException("User not found");
    }

    u->SetFirstName(newFirst);
    u->SetLastName(newLast);
    u->SetGroup(newGroup);
}

User UserService::GetById(const string& userId) const {
    const auto* u = repo.FindOne([&](const User& x) {
        return x.GetId() == userId;
    });

    if (!u) {
        throw DomainException("User not found");
    }

    return *u;
}

vector<User> UserService::GetAll() const {
    return repo.GetAll();
}

vector<User> UserService::FindByFirstName(const string& name) const {
    return repo.FindMany([&](const User& u) {
        return u.GetFirstName() == name;
    });
}

vector<User> UserService::FindByLastName(const string& name) const {
    return repo.FindMany([&](const User& u) {
        return u.GetLastName() == name;
    });
}

vector<User> UserService::FindByGroup(const string& group) const {
    return repo.FindMany([&](const User& u) {
        return u.GetGroup() == group;
    });
}

vector<User> UserService::FindByKeyword(const string& keyword) const {
    return repo.FindMany([&](const User& u) {
        return u.GetFirstName().find(keyword) != string::npos
            || u.GetLastName().find(keyword)  != string::npos
            || u.GetGroup().find(keyword)     != string::npos;
    });
}

vector<User> UserService::SortByFirstName() const {
    auto copy = ctx->Users;
    sort(copy.begin(), copy.end(), [](const User& a, const User& b){
        return a.GetFirstName() < b.GetFirstName();
    });
    return copy;
}

vector<User> UserService::SortByLastName() const {
    auto copy = ctx->Users;
    sort(copy.begin(), copy.end(), [](const User& a, const User& b){
        return a.GetLastName() < b.GetLastName();
    });
    return copy;
}

vector<User> UserService::SortByGroup() const {
    auto copy = ctx->Users;
    sort(copy.begin(), copy.end(), [](const User& a, const User& b){
        return a.GetGroup() < b.GetGroup();
    });
    return copy;
}
