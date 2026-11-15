#include "Command.h"
#include "IOClasses.h"
#include <iostream>
#include <fstream>
using namespace std;

Truncate::Truncate() : Command() {}

Truncate::~Truncate() {}

bool Truncate::endOfLine() const {
	return true;
}

void Truncate::generateResult() {
	if (checkFile()) {
		//If file already exists...
		ifstream file(getArg(0));
		if (file) {
			//...truncate it...
			file.close();
			remove(getArg(0).data());
			ofstream file(getArg(0));
			file.close();
			setExecuted(true);
			return;
		}
		//...otherwise, report an error
		ConsoleStream::getInstance()->print("Error. File does not exist.");
		file.close();
		remove(getArg(0).data());
	}
}