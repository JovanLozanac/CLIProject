#pragma once
#include <iostream>
#include <string>
#include <vector>

// Abstract class for all commands.

class Command {
public:

	// Constructor.
	Command();

	// Destructor.
	virtual ~Command();

	// Checks if command ended in the first line. Returns true if did.
	virtual bool endOfLine() const = 0;

	// Tries to read argument from file (if given). Returns true if argument was in good format, otherwise false (forcing another arg input)
	bool readArgFromFile();

	// Checks for file errors. Filename is the first argument. For commands working with files (touch, rm, truncate)
	bool checkFile();

	// Functions to add args, at end or beginning of args list
	void addArg(std::string s);
	void addFirstArg(std::string s);

	// Executes function and feeds result to string. Does not necessarily output the result.
	virtual void generateResult() = 0;

	std::string getResult() const;

	// Outputs result.
	void outputResult() const;
	
	// Getters
	std::string getArg(int i) const;
	std::string getOption() const;
	int getArgCount() const;
	std::string getOutFile() const;
	bool getExecuted() const;

	// Setters
	void setOption(std::string s);
	void setArg(std::string s, int i);
	void setResult(std::string s);
	void setOutFile(std::string s);
	void setExecuted(bool newState);

private:

	// Command option - words starting with - such as "-w"
	std::string option;

	// Argument(s) of command
	std::vector<std::string>args; //args list

	// Result of executing the command
	std::string result;

	// Output file, if exists.
	std::string outFile;

	// Flag - true if function executed without errors
	bool executed;
};

// Types of commands

// Batch - executes commands
class Batch final : public Command {
public:
	Batch();
	~Batch();
	virtual bool endOfLine() const override;
	virtual void generateResult() override;
};

// Date - prints system date (d.m.yyyy)
class Date final : public Command {
public:
	Date();
	~Date();
	virtual bool endOfLine() const override;
	virtual void generateResult() override;
};

// Echo - prints argument (console or from file)
class Echo final : public Command {
public:
	Echo();
	~Echo();
	virtual bool endOfLine() const override;
	virtual void generateResult() override;
};

// Head - prints first n lines of argument (console or from file)
class Head final : public Command {
public:
	Head();
	~Head();
	virtual bool endOfLine() const override;
	virtual void generateResult() override;
};

// Prompt - changes prompt char (default is $)
class Prompt final : public Command {
public:
	Prompt();
	~Prompt();
	virtual bool endOfLine() const override;
	virtual void generateResult() override;
};

// RemoveFile - removes a file (name given by argument)
class RemoveFile final : public Command {
public:
	RemoveFile();
	~RemoveFile();
	virtual bool endOfLine() const override;
	virtual void generateResult() override;
};

// Time - prints system time (h:mm:ss)
class Time final : public Command {
public:
	Time();
	~Time();
	virtual bool endOfLine() const override;
	virtual void generateResult() override;
};

// Touch - creates new file (name given by argument)
class Touch final : public Command {
public:
	Touch();
	~Touch();
	virtual bool endOfLine() const override;
	virtual void generateResult() override;
};

// Translate - changes substrings
class Translate final : public Command {
public:
	Translate();
	~Translate();
	virtual bool endOfLine() const override;
	virtual void generateResult() override;
};

// Truncate - truncates a file (name given by argument)
class Truncate final : public Command {
public:
	Truncate();
	~Truncate();
	virtual bool endOfLine() const override;
	virtual void generateResult() override;
};

// Word Count - has two options:
// wc -c prints number of chars in argument (console or file)
// wc -w prints number of words in argument (console or file)
class WordCount final : public Command {
public:
	WordCount();
	~WordCount();
	virtual bool endOfLine() const override;
	virtual void generateResult() override;
};