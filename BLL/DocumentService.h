#pragma once
#include <vector>
#include <string>
#include "../DAL/EntityContext.h"
#include "DomainException.h"
#include "Repository.h"

using namespace std;

class DocumentService {
private:
    EntityContext* ctx;
    Repository<Document> repo;

public:
    explicit DocumentService(EntityContext* context);

    void AddDocument(const Document& d);
    void RemoveDocument(const string& docId);
    void UpdateDocument(const string& docId,
                        const string& newTitle,
                        const string& newAuthor,
                        int newYear);

    Document GetById(const string& docId) const;
    vector<Document> GetAll() const;

    // Пошук
    vector<Document> FindByAuthor(const string& author) const;

    vector<Document> FindByTitleSubstring(const string& keyword) const;

    // Сортування
    vector<Document> SortByTitle() const;
    vector<Document> SortByAuthor() const;
    vector<Document> SortByYear() const;

};
