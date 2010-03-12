#ifndef REPO_H
#define REPO_H

#include <string>
#include <vector>
#include <ostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "writer.h"

class Repo {
	int processRepo (const std::string& repomd);
	int processDataTag (xmlNode* el);
	std::string processDataTag_ (xmlNode* el, const char* name);

	void processFileList ();
	void processPrimary ();

	std::string repomd;
	std::vector<std::string> files;
//	std::ostream* of;
	std::string os;
	Writer* writer;
	WriterFactory* factory;
	std::string path;

	friend class RepoFile;
public:
	Repo (/*std::ostream* _of*/WriterFactory* f, const std::string& path, const std::string& _os);
	~Repo ();
};

class RepoFile {
public:
	RepoFile (const std::string& file, /*std::ostream* of*/WriterFactory* f, const std::string& path, const std::string& os);
	std::vector<Repo> repo;
};


#endif

