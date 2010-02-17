#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "repo.h"
#include "dl.h"
#include "SimpleIni.h"

typedef CSimpleIniA::TNamesDepend sections_t;
typedef CSimpleIniA::TNamesDepend keys_t;

Repo::Repo (const std::string& file) {
	CSimpleIniA ini;
	ini.LoadFile (file.c_str ());
	sections_t section;
	ini.GetAllSections (section);
	std::string url;
	for (sections_t::iterator i = section.begin (); i != section.end (); i++) {
		std::cout << i->pItem << std::endl;
		if (ini.GetValue (i->pItem, "enabled")[0] == '1') {
			keys_t key;
			ini.GetAllKeys (i->pItem, key);
			for (keys_t::iterator j = key.begin (); j != key.end (); j++) {
				if (std::string ("baseurl").compare (j->pItem) == 0) url = ini.GetValue (i->pItem, "baseurl");
			}
			if (!url.length ()) {
				url = getBaseUrl (ini.GetValue (i->pItem, "mirrorlist"));
				std::cout << url << std::endl;
			}
		}
	}
}

xmlNode* getFirstUrl(xmlNode * a_node) {
	xmlNode *cur_node = NULL;
	std::string name;
	xmlNode* ret;
	for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
		name = (const char*)cur_node->name;
		if (name.compare ("url") == 0) return cur_node;
		ret = getFirstUrl (cur_node->children);
		if (ret) return ret;
	}
	return NULL;	
}


std::string Repo::getBaseUrl (const std::string& mirrorlist) {
	std::string url;
	
	data_t data;
	http_dl (mirrorlist/*, data*/);
	data = content ();

	xmlDocPtr doc = xmlReadMemory(&data[0], data.size (), "noname.xml", NULL, 0);
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

