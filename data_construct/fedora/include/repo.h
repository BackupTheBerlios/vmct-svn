#ifndef REPO_H
#define REPO_H

#include <string>

class Repo {
	std::string getBaseUrl (const std::string& mirrorlist);
public:
	Repo (const std::string& file);
};

#endif

