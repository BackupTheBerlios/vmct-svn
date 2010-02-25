#include "dl.h"
#include "repo.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>

int main (int argc, char** argv) {
	std::string file;

	int c;
	while ((c = getopt (argc, argv, "r:")) != -1) {
		switch (c) {
			case 'r':
				file = optarg;
			break;
		}
	}

	if (!file.length ()) {
		std::cerr << "Point to a .repo file with -r option" << std::endl;
		return -1;
	}

	Repo repo (file);
	
//	data_t data;
//	http_dl ("http://ya.ru", data);
	return 0;
}
 