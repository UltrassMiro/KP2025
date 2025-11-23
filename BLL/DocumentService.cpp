#include "DocumentService.h"
#include <algorithm>

using namespace std;

DocumentService::DocumentService(EntityContext* context)
    : ctx(context),
      repo(&context->Documents) {
    if (!ctx) {
        throw DomainException("DocumentService: context is null");
    }
}

void DocumentService::AddDocument(const Document& d) {
    auto* existing = repo.FindOne([&](const Document& x) {
        return x.GetId() == d.GetId();
    });

    if (existing) {
        throw DomainException("Document with this ID already exists");
    }

    repo.GetAll().push_back(d);
}

void DocumentService::RemoveDocument(const string& docId) {
    auto& all = repo.GetAll();
    auto it = remove_if(all.begin(), all.end(),
                        [&](const Document& d) {
                            return d.GetId() == docId;
                        });
    if (it == all.end()) {
        throw DomainException("Document not found");
    }
    all.erase(it, all.end());
}

void DocumentService::UpdateDocument(const string& docId,
                                     const string& newTitle,
                                     const string& newAuthor,
                                     int newYear) {
    auto* d = repo.FindOne([&](const Document& x) {
        return x.GetId() == docId;
    });

    if (!d) {
        throw DomainException("Document not found");
    }

    d->SetTitle(newTitle);
    d->SetAuthor(newAuthor);
    d->SetYear(newYear);
}

Document DocumentService::GetById(const string& docId) const {
    const auto* d = repo.FindOne([&](const Document& x) {
        return x.GetId() == docId;
    });

    if (!d) {
        throw DomainException("Document not found");
    }

    return *d;
}

vector<Document> DocumentService::GetAll() const {
    return repo.GetAll();
}

vector<Document> DocumentService::FindByAuthor(const string& author) const {
    return repo.FindMany([&](const Document& d) {
        return d.GetAuthor() == author;
    });
}

vector<Document> DocumentService::FindByTitleSubstring(const string& keyword) const {
    return repo.FindMany([&](const Document& d) {
        return d.GetTitle().find(keyword) != string::npos;
    });
}

vector<Document> DocumentService::SortByTitle() const {
    auto copy = ctx->Documents;
    sort(copy.begin(), copy.end(), [](const Document& a, const Document& b){
        return a.GetTitle() < b.GetTitle();
    });
    return copy;
}

vector<Document> DocumentService::SortByAuthor() const {
    auto copy = ctx->Documents;
    sort(copy.begin(), copy.end(), [](const Document& a, const Document& b){
        return a.GetAuthor() < b.GetAuthor();
    });
    return copy;
}

vector<Document> DocumentService::SortByYear() const {
    auto copy = ctx->Documents;
    sort(copy.begin(), copy.end(), [](const Document& a, const Document& b){
        return a.GetYear() < b.GetYear();
    });
    return copy;
}

