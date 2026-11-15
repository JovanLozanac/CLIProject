#include "Command.h"
#include "IOClasses.h"
using namespace std;

Translate::Translate() : Command() {}

Translate::~Translate() {}

bool Translate::endOfLine() const {
	return getArgCount() > 1 && getArg(1) != "";
}

void Translate::generateResult() {
	if (getArgCount() > 3) {
		ConsoleStream::getInstance()->print("Error. Too many arguments.");
		return;
	}

	if (getOption() != "") {
		ConsoleStream::getInstance()->print("Error. Option set.");
		return;
	}

	if (readArgFromFile()) {
		string res = "";
		for (int i = 0; i < getArg(0).length(); i++) {
			if (getArg(0).substr(i, getArg(1).length()) == getArg(1)) {
				res += (getArgCount() > 2) ? getArg(2) : "";
				i += getArg(1).length() - 1;
			}
			else res += getArg(0)[i];
		}
		setResult(res);
		setExecuted(true);
	}
		
}