#pragma once
#include "IOInterfaces.h"
#include <fstream>

// Class FInput - Takes input from file.

class FInput : IInput {
public:

	// Constructor. Takes file name.
	FInput(std::string fileName);

	// Destructor. Also closes the file.
	~FInput();

	// Reads all lines from file.
	virtual std::string read();

	bool getFileExists() const;

private:
	
	// Stream object
	std::ifstream s;

	// Indicator of file existance
	bool fileExists;

};

// Class FOutput - Writes output to file.
class FOutput : IOutput {
public:

	// Constructor. Takes file name.
	FOutput(std::string fileName);

	// Destructor. Also closes the file.
	~FOutput();

	// Optionally empties the file, then writes a line to the file.
	virtual void print(std::string line, char end = '\n');

private:

	// Stream object
	std::ofstream s;

};

// Class ConsoleStream - Console. Supports both input and output and also reports errors. Singleton.
class ConsoleStream : IInput, IOutput {
public:

	// Destructor
	~ConsoleStream();

	// Returns singleton instance
	static ConsoleStream* getInstance();

	// Reads one or more lines from console.
	virtual std::string read();
	virtual std::string readMissingArg();

	// Writes to console, then writes end char (optionally making a new line)
	virtual void print(std::string line, char end = '\n');

private:

	// Constructor.
	ConsoleStream();

	// Instance
	static ConsoleStream* instance;
};