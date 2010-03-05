#ifndef FUNC_H
#define FUNC_H

#include <string>
#include <vector>
#include <libxml/parser.h>
#include <libxml/tree.h>

xmlNode* getFirstUrl(xmlNode * a_node);

std::string getBaseUrl (const std::string& mirrorlist);

std::string escape (const std::string& str);

#endif 

