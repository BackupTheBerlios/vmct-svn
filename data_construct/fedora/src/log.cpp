#include "log.h"
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <iostream>

void log (const char* str) {
#if LOG_ON==1
	std::cout << str << std::endl;
#endif
}

void log (const std::string& str) {
#if LOG_ON==1
        std::cout << str << std::endl;
#endif
}

