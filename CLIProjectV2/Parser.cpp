#include "IOClasses.h"
#include "Exceptions.h"
#include "Parser.h"
#include <map>
using namespace std;

Parser::Parser() {}

Parser* Parser::instance;

Parser::~Parser() {}

Parser* Parser::getInstance() {
	if (!instance) instance = new Parser();
	return instance;
}

Command* Parser::makeCommand(string line) const {
	try {
		int i = 0;
		seek(line, i);
		string current = getWord(line, i);

		Command* c = nullptr;
		map <string, Command*> init = { {"batch", new Batch()}, {"date", new Date()}, {"echo", new Echo()},
			{"head", new Head()}, {"prompt", new Prompt()}, {"time", new Time()},
			{"rm", new RemoveFile()}, {"touch", new Touch()}, {"tr", new Translate()},
			{"truncate", new Truncate()}, {"wc", new WordCount()} };

		if (init.find(current) == init.end()) throw UnrecognisedCommandException("Unrecognised command: " + current);

		c = init[current];

		seek(line, i);

		while (i < line.length()) {
			current = getWord(line, i);
			if (current == ">" || current == "<" || current == ">>") {
				seek(line, i);
				current = current + getWord(line, i);
			}

			//adding data

			if (current[0] == '-') {
				if (c->getArgCount() > 0 || c->getOutFile() != "") throw SyntaxError();
				if (c->getOption() != "") throw CommandOptException();
				c->setOption(current);
				seek(line, i);
				continue;
			}
			if (current[0] == '>') {
				if (!c->endOfLine()) throw SyntaxError();
				if (c->getOutFile() != "") throw CommandOException();
				c->setOutFile(current);
			}
			else if (current.length() > 4 && current.substr(current.length() - 4) == ".txt") { //fix for files with name starting with '-' (a hyphen)
				if (c->getArgCount() != 0 || c->getOutFile() != "") throw SyntaxError();
				c->addArg(current);
			}
			else {
				if (c->getOutFile() != "") throw SyntaxError();
				if (current.substr(1, current.length() - 2).find("\"") != string::npos) {
					throw UnexpectedChar("Unexpected character: " + string{ current[current.substr(1, current.length() - 2).find("\"") + 2] });
				}
				c->addArg(current);
			}
			
			seek(line, i);
		}
		return c;
	}
	catch (exception &e) {
		ConsoleStream::getInstance()->print(e.what());
		return nullptr;
	}
	
}

void Parser::seek(string line, int& i) const {
	while (i < line.length() && (line[i] == ' ' || line[i] == '\t')) {
		i++;
	}
}

string Parser::getWord(string line, int& i) const {
	string word = "";
	while (i < line.length() && line[i] != ' ' && line[i] != '\t') {
		word += line[i];
		i++;
	}
	//not an arg
	if (word.find('\"') == string::npos) return word;

	//is an arg
	if (word[0] == '\"' && word != "\"" && word[word.length() - 1] == '\"') return word;
	else {
		//read until closing quotation mark
		while (i < line.length()) {
			word += line[i];
			if (line[i++] == '\"') break;
		}
	}
	return word;
}