#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "dl.h"
#include "repo.h"

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

	RepoFile repo (file);
	std::cout << repo.repo.size () << std::endl;
	
	return 0;
}
 
