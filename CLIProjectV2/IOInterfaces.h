#pragma once
#include <string>

// Interface for classes with the ability to read data.

class IInput {
public:
    virtual std::string read() = 0;
};

// Interface for classes with the ability to write data.

class IOutput {
public:
    virtual void print(std::string line, char end = '\n') = 0;
};