#include "Command.h"
#include "IOClasses.h"
#include <iostream>
#include <fstream>
using namespace std;

RemoveFile::RemoveFile() : Command() {}

RemoveFile::~RemoveFile() {}

bool RemoveFile::endOfLine() const {
	return true;
}

void RemoveFile::generateResult() {
	if (checkFile()) {
		//If file already exists...
		ifstream file(getArg(0));
		if (file) {
			//...delete it...
			file.close();
			if (remove(getArg(0).data()) != 0) ConsoleStream::getInstance()->print("Error. Could not delete file.");
			setExecuted(true);
			return;
		}
		//...otherwise, report an error
		ConsoleStream::getInstance()->print("Error. File does not exist.");
		file.close();
	}
}