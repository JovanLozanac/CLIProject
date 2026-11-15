#define _CRT_SECURE_NO_WARNINGS
#include "Command.h"
#include "IOClasses.h"
#include <ctime>
using namespace std;

Date::Date() : Command() {}

Date::~Date() {}

bool Date::endOfLine() const {
	return true;
}

void Date::generateResult() {
	if (getArgCount() > 0) {
		ConsoleStream::getInstance()->print("Error. Too many arguments.");
		return;
	}

	if (getOption() != "") {
		ConsoleStream::getInstance()->print("Error. Option set.");
		return;
	}

	time_t timeStamp = time(&timeStamp);
	struct tm dateTime = *localtime(&timeStamp);
	setResult(to_string(dateTime.tm_mday) + "." + to_string(dateTime.tm_mon + 1) + "." + to_string(dateTime.tm_year + 1900) + ".");
	setExecuted(true);
}