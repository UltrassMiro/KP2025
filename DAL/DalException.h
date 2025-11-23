#pragma once
#include <exception>
#include <string>

using namespace std;

class DalException : public exception {
    string msg;
public:
    explicit DalException(const string& message)
        : msg(message) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};
