#pragma once
#include <exception>
#include <string>
using namespace std;

class UnrecognisedCommandException : public exception {
public:
	UnrecognisedCommandException(string s) : exception(s.data()) {} //only exception that has to include command name
};

class CommandOptException : public exception {
public:
	CommandOptException() : exception("Error. Command has multiple options.") {}
};

class CommandIException : public exception {
public:
	CommandIException() : exception("Error. Command has multiple input redirections.") {}
};

class CommandOException : public exception {
public:
	CommandOException() : exception("Error. Command has multiple output redirections.") {}
};

class PipeIException : public exception {
public:
	PipeIException() : exception("Error. Pipe has input stream wrongly redirected.") {}
};

class PipeOException : public exception {
public:
	PipeOException() : exception("Error. Pipe has output stream wrongly redirected.") {}
};

class SyntaxError : public exception {
public:
	SyntaxError() : exception("Syntax error.") {}
};

class UnexpectedChar : public exception {
public:
	UnexpectedChar(string s) : exception(s.data()) {}
};
