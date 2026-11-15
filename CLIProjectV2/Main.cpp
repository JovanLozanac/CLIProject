#include "CLI.h"

int main() {
	CLI* c = CLI::getInstance();
	c->work();
	delete c;

	return 0;
}
