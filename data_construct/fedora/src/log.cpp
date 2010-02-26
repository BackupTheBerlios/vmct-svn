#include "log.h"
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <iostream>

void log (const char* str) {
#ifdef LOG_ON
	std::cout << str << std::endl;
#endif
}

void log (const std::string& str) {
#ifdef LOG_ON
        std::cout << str << std::endl;
#endif
}

