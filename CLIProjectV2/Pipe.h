#pragma once
#include "Command.h"
#include <iostream>
#include <string>
#include <vector>

// A non-abstract class for pipes.
// Pipes are supposed to "chain" multiple commands, in that every command except for the first, takes input from the last one's output.
// The result would be the result of the last command.

class Pipe {
public:

	// Constructor. Also extracts the commands into the private field.
	Pipe(std::string line, std::vector<int> pos);

	// Destructor.
	~Pipe();

	// Function to execute from start to finish, then output the result.
	void process() const;

private:

	// This vector contains all the command text from which the commands will be initialised and executed.
	std::vector<std::string> commandText;
};