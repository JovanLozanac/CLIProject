#include "IOClasses.h"
#include "Command.h"
#include "CLI.h"
#include "Parser.h"
#include <iostream>
#include <fstream>
using namespace std;

// Class FInput

FInput::FInput(string fileName) {
	if(fileName[0] == '<') s.open(fileName.substr(1));
	else s.open(fileName);
	if (!s.good()) {
		ConsoleStream::getInstance()->print("Error. File not found.");
		fileExists = false;
	}
	else fileExists = true;
}

FInput::~FInput() {
	s.close();
}

string FInput::read() {
	string allLines;
	string singleLine;
	while (getline(s, singleLine)) {
		allLines.append(singleLine);
		allLines.append("\n");
	}
	if (allLines.length() > 0 && allLines[allLines.length() - 1] == '\n') allLines = allLines.substr(0, allLines.length() - 1);
	return allLines;
}

bool FInput::getFileExists() const { return fileExists; }

// Class FOutput

FOutput::FOutput(string fileName) {
	if (fileName.substr(0, 2) == ">>") s.open(fileName.substr(2), ios::app);
	else if (fileName[0] == '>') s.open(fileName.substr(1), ios::trunc);
}

FOutput::~FOutput() {
	s.close();
}

void FOutput::print(string line, char end) {
	s << line;
}

// Class ConsoleStream

ConsoleStream::ConsoleStream() {}

ConsoleStream* ConsoleStream::instance;

ConsoleStream::~ConsoleStream() {}

ConsoleStream* ConsoleStream::getInstance() {
	if (!instance) instance = new ConsoleStream();
	return instance;
}

string ConsoleStream::read() {
	string line = "";
	char c;
	while ((c = getchar()) != '\n') line += c;
	line = line.substr(0, 512);

	return line;
}

string ConsoleStream::readMissingArg() {
	string missingArg = "\"";
	char c;
	while ((c = getchar()) != EOF) missingArg += c;
	missingArg[missingArg.length() - 1] = '\"';
	return missingArg;
}

void ConsoleStream::print(string line, char end) {
	if(line != "") cout << line << end;
}