#include <string.h>
#include <algorithm>
#include "func.h"
#include "dl.h"

xmlNode* getFirstUrl(xmlNode * a_node) {
        xmlNode *cur_node = NULL;
        std::string name;
        xmlNode* ret;
        for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
                if (strncmp ("url", reinterpret_cast<const char*>(cur_node->name), 3) == 0) return cur_node;
                ret = getFirstUrl (cur_node->children);
                if (ret) return ret;
        }
        return NULL;
}


std::string getBaseUrl (const std::string& mirrorlist) {
        std::string url;

        file_dl (mirrorlist);

        xmlDocPtr doc = xmlReadMemory(&*dl_content ().begin (), dl_content ().size (), "noname.xml", NULL, 0);
        if (!doc) {
                return url;
        }

        xmlNode *el = getFirstUrl (xmlDocGetRootElement(doc));
        if (el) {
                el = el->children;
                if (el && el->content) {
                        url = reinterpret_cast<const char*>(el->content);
                }
        }

        xmlFreeDoc(doc);

        return url;
}

std::string escape (const std::string& str) {
	std::string res;
	char escape;
	for (std::string::const_iterator it = str.begin (); it != str.end (); it++) {
		escape = 0;
		switch (*it) {
			case 0:
				escape = '0';
			break;
			case '\n':
				escape = 'n';
			break;
			case '\r':
                                escape = 'r';
                        break;
			case '\\':
                                escape = '\\';
                        break;
			case '\'':
                                escape = '\'';
                        break;
			case '"':
                                escape = '"';
                        break;
			case '\032':
                                escape = 'Z';
                        break;
		}
		if (escape) {
			res.push_back ('\\');
			res.push_back (escape);
		} else {
			res.push_back (*it);
		}
	}
	return res;
}

