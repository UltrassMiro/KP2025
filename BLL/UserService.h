#pragma once
#include <vector>
#include <string>
#include "../DAL/EntityContext.h"
#include "DomainException.h"
#include "Repository.h"

using namespace std;

class UserService {
private:
    EntityContext* ctx;
    Repository<User> repo;

public:
    explicit UserService(EntityContext* context);

    void AddUser(const User& u);
    void RemoveUser(const string& userId);
    void UpdateUser(const string& userId,
                    const string& newFirst,
                    const string& newLast,
                    const string& newGroup);

    User GetById(const string& userId) const;
    vector<User> GetAll() const;

    // Пошук
    vector<User> FindByFirstName(const string& name) const;
    vector<User> FindByLastName(const string& name) const;
    vector<User> FindByGroup(const string& group) const;

    vector<User> FindByKeyword(const string& keyword) const;

    // Сортування
    vector<User> SortByFirstName() const;
    vector<User> SortByLastName() const;
    vector<User> SortByGroup() const;


};
