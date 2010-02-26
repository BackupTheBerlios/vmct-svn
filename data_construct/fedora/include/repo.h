#ifndef REPO_H
#define REPO_H

#include <string>
#include <vector>
#include <libxml/parser.h>
#include <libxml/tree.h>

class Repo {
	int processRepo (const std::string& repomd);
	int processDataTag (xmlNode* el);
	std::string processDataTag_ (xmlNode* el, const char* name);

	void processFileList ();
	void processPrimary ();

	std::string repomd;
	std::vector<std::string> files;

	friend class RepoFile;
public:
	Repo ();
};

class RepoFile {
public:
	RepoFile (const std::string& file);
	std::vector<Repo> repo;
};


#endif

