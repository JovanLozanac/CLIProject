#define _CRT_SECURE_NO_WARNINGS
#include "Command.h"
#include "IOClasses.h"
#include <ctime>
using namespace std;

Time::Time() : Command() {}

Time::~Time() {}

bool Time::endOfLine() const {
	return true;
}

void Time::generateResult() {
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
	setResult(to_string(dateTime.tm_hour) + ":" +
		(dateTime.tm_min > 9 ? to_string(dateTime.tm_min) : ("0" + to_string(dateTime.tm_min))) + ":" +
		(dateTime.tm_sec > 9 ? to_string(dateTime.tm_sec) : ("0" + to_string(dateTime.tm_sec))));
	setExecuted(true);
}