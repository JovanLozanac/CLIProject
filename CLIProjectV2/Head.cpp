#include "Command.h"
#include "IOClasses.h"
using namespace std;

Head::Head() : Command() {}

Head::~Head() {}

bool Head::endOfLine() const {
	return getArgCount() != 0 && getArg(0) != "";
}

void Head::generateResult() {
	if (getArgCount() > 1) {
		ConsoleStream::getInstance()->print("Error. Too many arguments.");
		return;
	}

	if (getOption() == "") ConsoleStream::getInstance()->print("Error. Option not set.");

	else if (getOption().length() > 7 || getOption().length() < 3 || getOption().substr(0, 2) != "-n") ConsoleStream::getInstance()->print("Error. Unrecognised option.");
	
	else if (readArgFromFile()) {
		string res = "";
		int nCount = stoi(getOption().substr(2));
		int currChar = 0;
		int lineCount = 0;
		while (lineCount < nCount && currChar < getArg(0).length() && getArg(0)[currChar] != EOF) {
			if (getArg(0)[currChar] != '\n' || nCount - lineCount != 1) res += getArg(0)[currChar];
			if (getArg(0)[currChar] == '\n') lineCount++;
			currChar++;
		}
		setResult(res);
		setExecuted(true);
	}
}