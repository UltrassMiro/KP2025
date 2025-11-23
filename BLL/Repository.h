#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

template<typename T>
class Repository {
private:
    vector<T>* data;

public:
    explicit Repository(vector<T>* d)
        : data(d) {
        if (!data) {
            throw invalid_argument("Repository data pointer is null");
        }
    }

    vector<T>& GetAll() {
        return *data;
    }

    const vector<T>& GetAll() const {
        return *data;
    }

    template<typename Pred>
    T* FindOne(Pred predicate) {
        auto it = find_if(data->begin(), data->end(), predicate);
        if (it == data->end()) return nullptr;
        return &(*it);
    }

    template<typename Pred>
    const T* FindOne(Pred predicate) const {
        const vector<T>* cdata = data;
        auto it = find_if(cdata->begin(), cdata->end(), predicate);
        if (it == cdata->end()) return nullptr;
        return &(*it);
    }

    template<typename Pred>
    vector<T> FindMany(Pred predicate) const {
        vector<T> result;
        const vector<T>* cdata = data;
        for (const auto& item : *cdata) {
            if (predicate(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};
