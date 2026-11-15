#pragma once
#include "Command.h"
#include <string>

// "Translates" a given string into a command. Controls execution and sets parametres of commands. Singleton.

class Parser
{
public:

	// Singleton destructor
	~Parser();

	// Returns singleton instance
	static Parser* getInstance();

	// Makes a command out of a string
	Command* makeCommand(std::string line) const;

private:

	// Constructor.
	Parser();

	// Instance
	static Parser* instance;

	// Two helper functions for making a command:

	// Advance to next word (ie. to first non-space character)
	void seek(std::string line, int &i) const;

	// Read word (all characters before space)
	std::string getWord(std::string line, int &i) const;

};

