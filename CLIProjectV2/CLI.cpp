#include "CLI.h"
#include "Pipe.h"
using namespace std;

CLI::CLI() : cmdPrompt("$") {}

CLI* CLI::instance;

CLI::~CLI() {
	delete Parser::getInstance();
}

CLI* CLI::getInstance() {
	if (!instance) instance = new CLI();
	return instance;
}

void CLI::work() const {
	ConsoleStream* cs = ConsoleStream::getInstance();
	Parser* p = Parser::getInstance();
	while (true) {
		printPrompt();
		string line = cs->read();
		vector<int> pos = findPipeSep(line);

		if (pos.empty()) { // a command
			Command* c = p->makeCommand(line);
			if (c) {
				c->generateResult();
				c->outputResult();
				delete c;
			}
		}
		else { // a pipe
			Pipe* pi = new Pipe(line, pos);
			pi->process();
			delete pi;
		}
	}
}

string CLI::getPrompt() const { return cmdPrompt; }
void CLI::setPrompt(string newPrompt) { cmdPrompt = newPrompt; }

void CLI::printPrompt() const {
	ConsoleStream::getInstance()->print(cmdPrompt, ' ');
}

vector<int> CLI::findPipeSep(string line) const {
	vector<int> pos = {};
	bool inQuote = false;
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == '\"') inQuote = !inQuote;
		else if (!inQuote && line[i] == '|') pos.push_back(i);
	}
	return pos;
}