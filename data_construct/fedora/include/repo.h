#ifndef REPO_H
#define REPO_H

#include <string>
#include <vector>
#include <libxml/parser.h>
#include <libxml/tree.h>

class Repo {
	int processRepo (const std::string& repomd);
	int processDataTag (xmlNode* el);
	std::vector<char> processDataTag_ (xmlNode* el, const char* name);

	std::string repomd;
	std::vector<std::vector<char> > data;

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

