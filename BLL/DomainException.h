#pragma once
#include <exception>
#include <string>

using namespace std;

class DomainException : public exception {
    string msg;
public:
    explicit DomainException(const string& message)
        : msg(message) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};
