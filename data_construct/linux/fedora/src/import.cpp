#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <getopt.h>
#include <string.h>
#include "dl.h"
#include "repo.h"
#include "sqlwriter.h"
#include "csvwriter.h"

static const char* const short_options = "hr:s:t:o:";
static const struct option long_options [] = {
	{"help", 0, NULL, 'h'},
	{"repo", 1, NULL, 'r'},
	{"os", 1, NULL, 's'},
	{"type", 1, NULL, 't'},
	{"out", 1, NULL, 'o'},
	{NULL, 0, NULL, 0}
};

static void display_usage () {
	std::cout << "--help     This help" << std::endl;
	std::cout << "--repo, -r Point to the file with repository metadata" << std::endl;
	std::cout << "--out,  -o Point to out-file. Or none, if you need out to stdout" << std::endl;
	std::cout << "--os,   -s Name of OS. Fedora by default" << std::endl;
	std::cout << "--type, -t Type of output (sql, csv)" << std::endl;
}

int main (int argc, char** argv) {
	std::string file;
	std::string os = "Fedora";
	std::string out;
	boost::shared_ptr<WriterFactory> factory;

	int c;
	while ((c = getopt_long (argc, argv, short_options, long_options, NULL)) != -1) {
		switch (c) {
			case 'h':
				display_usage ();
				exit (0);
			break;
			case 'r': 
				if (optarg) file = optarg; 
				std::cout << "file " << file << std::endl;
			break;
			case 's':
				if (optarg) os = optarg;
				std::cout << "optarg " << optarg << std::endl;
			break;
			case 'o': 
				if (optarg) out = optarg;
				std::cout << "out " << optarg << std::endl;
			break;
			case 't':
				if (strncmp ("sql", optarg, 3) == 0) factory = boost::shared_ptr<WriterFactory> (new SQLFactory);
				if (strncmp ("csv", optarg, 3) == 0) factory = boost::shared_ptr<WriterFactory> (new CSVFactory);
				std::cout << "type " << optarg << std::endl;
			break;
		}
	}

	if (!file.length () || !factory.get ()) {
		display_usage ();
		return 1;
	}

	RepoFile repo (file, factory, out, os);

	return 0;
}
 
