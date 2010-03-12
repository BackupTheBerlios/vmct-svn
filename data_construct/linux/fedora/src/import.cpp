#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <getopt.h>
#include "dl.h"
#include "repo.h"
#include "writer.h"

static const char* const short_options = "hrs:o";
static const struct option long_options [] = {
	{"help", 0, NULL, 'h'},
	{"repo", 1, NULL, 'r'},
	{"os", 1, NULL, 's'},
	{"out", 1, NULL, 'o'},
	{NULL, 0, NULL, 0}
};

static void display_usage () {
	std::cout << "--help     This help" << std::endl;
	std::cout << "--repo, -r Point to the file with repository metadata" << std::endl;
	std::cout << "--out,  -o Point to out-file. Or none, if you need out to stdout" << std::endl;
	std::cout << "--os,   -s Name of OS. Fedora by default" << std::endl;
}

int main (int argc, char** argv) {
	std::string file;
	std::string os = "Fedora";
	std::string out;

	int c;
	while ((c = getopt_long (argc, argv, short_options, long_options, NULL)) != -1) {
		switch (c) {
			case 'h':
				display_usage ();
				exit (0);
			break;
			case 'r': 
				file = optarg;
			break;
			case 's':
				os = optarg;
			break;
			case 'o': 
				out = optarg;
			break;
		}
	}

	if (!file.length ()) {
		display_usage ();
		return 1;
	}

	SQLFactory factory;

	RepoFile repo (file, &factory, out, os);

	return 0;
}
 
