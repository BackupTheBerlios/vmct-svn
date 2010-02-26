#include <string.h>
#include <algorithm>
#include "func.h"
#include "dl.h"

xmlNode* getFirstUrl(xmlNode * a_node) {
        xmlNode *cur_node = NULL;
        std::string name;
        xmlNode* ret;
        for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
                if (strncmp ("url", (const char*)cur_node->name, 3) == 0) return cur_node;
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
                        url = (const char*)el->content;
                }
        }

        xmlFreeDoc(doc);

        return url;
}

/*std::string basename (const std::string& url) {
        std::string name;
        ssize_t it = url.find_last_of ('/');
        if (it != std::string::npos) name.assign (url.begin () + it + 1, url.end ());
        else return url;
        return name;
}*/

