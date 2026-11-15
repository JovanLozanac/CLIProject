#include "IOClasses.h"
#include "Exceptions.h"
#include "Parser.h"
#include "Pipe.h"
using namespace std;

Pipe::Pipe(string line, vector<int> pos) {
	this->commandText = {};
	int noOfCommand = 0;
	string currCommandText = "";
	for (int i = 0; i <= line.length(); i++) {
		if (i == line.length() || (noOfCommand < pos.size() && i == pos[noOfCommand])) {
			this->commandText.push_back(currCommandText);
			currCommandText = "";
			noOfCommand++;
		}
		else currCommandText += line[i];
	}
}

Pipe::~Pipe() {}

void Pipe::process() const {
	try {
		string result = "";
		for (int i = 0; i < commandText.size(); i++) {
			if (i == 0) {
				Command* c = Parser::getInstance()->makeCommand(commandText[i]);
				if (!c) break;
				if (c->getOutFile() != "") throw PipeOException(); //redirecting output before the last command

				c->generateResult();
				if (!c->getExecuted()) {
					delete c;
					break;
				}
				result = c->getResult();
				delete c;
			}
			else {
				Command* c = Parser::getInstance()->makeCommand(commandText[i]);
				if (!c) break;
				if (c->getArgCount() > 0 && c->getArg(0).find(".txt") != string::npos) throw PipeIException(); //redirecting input

				c->addFirstArg("\"" + result + "\"");
				c->generateResult();
				if (!c->getExecuted()) {
					delete c;
					break;
				}

				result = c->getResult();

				//if command is last in line, output the result
				if (i == commandText.size() - 1) c->outputResult();
				else if (c->getOutFile() != "") throw PipeOException(); //redirecting output before the last command
				delete c;
			}
		}
	}

	catch (exception& e) {
		ConsoleStream::getInstance()->print(e.what());
	}
}