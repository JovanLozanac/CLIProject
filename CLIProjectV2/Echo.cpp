#include "Command.h"
#include "IOClasses.h"

Echo::Echo() : Command() {}

Echo::~Echo() {}

bool Echo::endOfLine() const {
	return getArgCount() != 0 && getArg(0) != "";
}

void Echo::generateResult() {
	if (getArgCount() > 1) {
		ConsoleStream::getInstance()->print("Error. Too many arguments.");
		return;
	}

	if (getOption() != "") {
		ConsoleStream::getInstance()->print("Error. Option set.");
		return;
	}
	if (readArgFromFile()) {
		setResult(getArg(0));
		setExecuted(true);
	}
}