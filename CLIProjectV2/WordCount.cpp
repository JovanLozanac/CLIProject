#include "Command.h"
#include "IOClasses.h"
using namespace std;

WordCount::WordCount() : Command() {}

WordCount::~WordCount() {}

bool WordCount::endOfLine() const {
	return getOption() != "" && getArgCount() != 0;
}

void WordCount::generateResult() {
	if (getArgCount() > 1) {
		ConsoleStream::getInstance()->print("Error. Too many arguments.");
		return;
	}

	else if (getOption() != "-w" && getOption() != "-c") {
		if (getOption() == "") ConsoleStream::getInstance()->print("Error. Option not set.");
		else ConsoleStream::getInstance()->print("Error. Unrecognised option.");
		return;
	}

	else if (readArgFromFile()) {
		if (getOption() == "-w") {
			int count = 0;
			bool onLetter = false;
			for (int i = 0; i < getArg(0).length(); i++) {
				if (!isspace(getArg(0)[i]) && !onLetter) {
					onLetter = true;
					count++;
				}
				else onLetter = !isspace(getArg(0)[i]);
			}
			setResult(to_string(count));
		}
		else setResult(to_string(getArg(0).length()));

		setExecuted(true);
	}
}