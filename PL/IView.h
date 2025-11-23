#pragma once
#include <string>

using namespace std;

class IView {
public:
    virtual ~IView() = default;

    virtual void Run() = 0;

protected:
    virtual int ReadInt(const string& prompt) = 0;
    virtual string ReadString(const string& prompt) = 0;
    virtual void ShowMessage(const string& msg) = 0;
};
