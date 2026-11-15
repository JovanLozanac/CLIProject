#include "Command.h"
#include "IOClasses.h"
#include <fstream>
using namespace std;

Touch::Touch() : Command() {}

Touch::~Touch() {}

bool Touch::endOfLine() const {
	return true;
}

void Touch::generateResult() {
	if (checkFile()) {
		//If file already exists...
		ifstream file(getArg(0));
		if (file) {
			//...report an error...
			ConsoleStream::getInstance()->print("Error. File already exists.");
			file.close();
			return;
		}
		//...otherwise, make file
		file.close();
		ofstream test;
		test.open(getArg(0));
		test.close();
		setExecuted(true);
	}
}