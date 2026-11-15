#include "Command.h"
#include "IOClasses.h"
#include "Parser.h"
using namespace std;

Batch::Batch() : Command() {}

Batch::~Batch() {}

bool Batch::endOfLine() const {
	return getArgCount() != 0 && getArg(0) != "";
}

void Batch::generateResult() {

	if (getArgCount() > 1) {
		ConsoleStream::getInstance()->print("Error. Too many arguments.");
		return;
	}

	if (getOption() != "") {
		ConsoleStream::getInstance()->print("Error. Option set.");
		return;
	}
	if (readArgFromFile()) {
		string currCommand = "";
		for (int i = 0; i <= getArg(0).length(); i++) {
			if (getArg(0)[i] == '\n' || i == getArg(0).length()) {
				Command* c = Parser::getInstance()->makeCommand(currCommand);
				if (c) {
					c->generateResult();
					c->outputResult();
					delete c;
				}
				currCommand = "";
			}
			else currCommand += getArg(0)[i];
		}
		setExecuted(true);
	}
}