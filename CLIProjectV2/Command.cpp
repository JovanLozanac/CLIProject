#include "Command.h"
#include "IOClasses.h"
using namespace std;

Command::Command() : executed(false) {}

Command::~Command() {}

bool Command::readArgFromFile() {
	if(!endOfLine()) addFirstArg(ConsoleStream::getInstance()->readMissingArg());
	for (int i = 1; i < args.size(); i++) {
		if (args[i] != "") {
			if (args[i][0] != '\"') {
				ConsoleStream::getInstance()->print("Unexpected character: " + string{ args[i][0] });
				return false;
			}
			if (args[i][args[i].length() - 1] != '\"') {
				ConsoleStream::getInstance()->print("Unexpected character: " + string{ args[i][args[i].length() - 1] });
				return false;
			}
			args[i] = args[i].substr(1, args[i].length() - 2);
			if (args[i].find("\"") != string::npos) {
				ConsoleStream::getInstance()->print("Unexpected character: " + string{ args[i][args[i].find("\"")] });
				return false;
			}
		}
	}
	if (args[0][0] == '\"' && args[0][args[0].length() - 1] == '\"') {
		args[0] = args[0].substr(1, args[0].length() - 2);
		return true;
	}
	else if (args[0].length() >= 4 && args[0].substr(args[0].length() - 4) == ".txt") {
		if (args[0].find("\"") != string::npos) {
			ConsoleStream::getInstance()->print("Unexpected character: " + string{ args[0][args[0].find("\"")] });
			return false;
		}
		FInput* f = new FInput(args[0]);
		if (f->getFileExists()) {
			args[0] = f->read();
			delete f;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		ConsoleStream::getInstance()->print("Unexpected character: " + string{ args[0][0] });
		return false;
	}
}

bool Command::checkFile() {
	if (getArgCount() > 1) {
		ConsoleStream::getInstance()->print("Error. Too many arguments.");
	}

	else if (getOption() != "") {
		ConsoleStream::getInstance()->print("Error. Option set.");
	}

	else if (getArg(0) == "" || getArg(0)[0] == '\"' && getArg(0)[getArg(0).length() - 1] == '\"') {
		ConsoleStream::getInstance()->print("Argument error.");
	}

	else if (getArg(0).find("\"") != string::npos) {
		ConsoleStream::getInstance()->print("Unexpected character: " + string{ getArg(0)[getArg(0).find("\"")] });
	}

	else if (getArg(0).substr(getArg(0).length() - 4, 4) != ".txt") {
		ConsoleStream::getInstance()->print("File format error.");
	}
	else return true;
	return false;
}

void Command::addArg(string s) {
	args.push_back(s);
}
void Command::addFirstArg(string s) {
	args.insert(args.begin(), s);
}

void Command::outputResult() const {
	if (outFile == "") ConsoleStream::getInstance()->print(result);
	else {
		FOutput* f = new FOutput(outFile);
		f->print(result);
		delete f;
	}
}

string Command::getOption() const { return option; }
string Command::getArg(int i) const { return args[i]; }
int Command::getArgCount() const { return args.size(); }
string Command::getResult() const { return result; }
string Command::getOutFile() const { return outFile; }
bool Command::getExecuted() const { return executed; }

void Command::setOption(string s) { option = s; }
void Command::setArg(string s, int i) { 
	if (args.size() == 0) addFirstArg(s);
	else if (i > -1 && i < args.size()) args[i] = s;
}
void Command::setResult(string s) { result = s; }
void Command::setOutFile(string s) { outFile = s; }
void Command::setExecuted(bool newState) { executed = newState; }