#include "log.h"
#include <iostream>

static bool logOn = false;

void setLogOn (bool b) {
	logOn = b;
}

void log (const char* str) {
	if (logOn) std::cout << str << std::endl;
}

void log (const std::string& str) {
	if (logOn) std::cout << str << std::endl;
}

