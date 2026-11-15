#include "CLI.h"
#include "Command.h"

Prompt::Prompt() : Command() {}

Prompt::~Prompt() {}

bool Prompt::endOfLine() const {
	return getArgCount() != 0 && getArg(0) != "";
}

void Prompt::generateResult() {
	if (getArgCount() > 1) {
		ConsoleStream::getInstance()->print("Error. Too many arguments.");
		return;
	}

	if (getOption() != "") {
		ConsoleStream::getInstance()->print("Error. Option set.");
		return;
	}

	if (readArgFromFile()) {
		CLI::getInstance()->setPrompt(getArg(0));
		setExecuted(true);
	}
}