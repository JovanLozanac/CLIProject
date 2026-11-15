#pragma once
#include "IOClasses.h"
#include "Parser.h"
#include <vector>

// Command Line Interface - Singleton class
class CLI
{
public:

	// Destructor
	~CLI();

	// Returns singleton instance
	static CLI* getInstance();

	// Infinitely take input and execute
	void work() const;

	// Getter and setter for the command prompt
	std::string getPrompt() const;
	void setPrompt(std::string newSymbol);

	// Print ready symbol (symbolizes the end of the previous command)
	void printPrompt() const;

	// Helper function to find positions of '|' outside quotation marks.
	// Important for making pipes as well as for deciding whether to make a pipe or a command.
	std::vector<int> findPipeSep(std::string line) const;

private:

	// Singleton constructor
	CLI();

	// Instance
	static CLI* instance;

	// Command prompt - ready symbol - can be changed, "$" is default
	std::string cmdPrompt;

};
