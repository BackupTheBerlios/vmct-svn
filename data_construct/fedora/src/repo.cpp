#include <iostream>
#include <string.h>
#include <algorithm>

#include "func.h"
#include "repo.h"
#include "dl.h"
#include "err.h"
#include "SimpleIni.h"

typedef CSimpleIniA::TNamesDepend sections_t;
typedef CSimpleIniA::TNamesDepend keys_t;

static const char* data_tags [] =
{
        "filelists",
        "primary",
        "group",
};

static const int data_tag_count = sizeof (data_tags)/sizeof(const char*);

int check (const char* type) {
        for (int i = 0; i < data_tag_count; i++) {
                if (strncmp (type, data_tags[i], strlen (data_tags[i])) == 0) return i;
        }
        return -1;
}

Repo::Repo () {}

// process a .repo file
RepoFile::RepoFile (const std::string& file) {
	CSimpleIniA ini;
	ini.LoadFile (file.c_str ());
	sections_t section;
	ini.GetAllSections (section);
	std::string url;

	// for each [repo] section
	for (sections_t::iterator i = section.begin (); i != section.end (); i++) {
		std::cout << i->pItem << std::endl;
		if (ini.GetValue (i->pItem, "enabled")[0] == '1') {
			keys_t key;
			ini.GetAllKeys (i->pItem, key);
			for (keys_t::iterator j = key.begin (); j != key.end (); j++) {
				if (strncmp ("baseurl", j->pItem, 7) == 0) url = ini.GetValue (i->pItem, "baseurl");
			}
			if (!url.length ()) {
				Repo repo_;
				if (repo_.processRepo (getBaseUrl (ini.GetValue (i->pItem, "mirrorlist"))) == 0) repo.push_back (repo_);
			}
		}
	}
}

// download and process repomd.xml
int Repo::processRepo (const std::string& repomd) {
	this->repomd = repomd;
	std::cout << repomd << std::endl;
	file_dl (repomd);

	xmlDocPtr doc = xmlReadMemory(&*dl_content ().begin (), dl_content ().size (), "noname.xml", NULL, 0);
	if (!doc) {
		return E_XML;
	}

	this->data.resize (data_tag_count);

	xmlNode *el = xmlDocGetRootElement(doc);
	if (el && strncmp ((const char*)el->name, "repomd", 6) == 0) {
		el = el->children;
		while (el) {
			if (strncmp ((const char*)el->name, "data", 4) == 0) {
				processDataTag (el);
			}
			el = el->next;
		}
	} else {
		xmlFreeDoc(doc);
		std::cout << "err";
		return E_XML;
	}

	xmlFreeDoc(doc);
	return E_OK;
}

// extract information from <data>-tags
int Repo::processDataTag (xmlNode* el) {
	const char* type = (const char*)xmlGetProp (el, (const xmlChar*)"type");

	int idx = check (type);
	if (idx == -1) return E_NONE;
	
	this->data[idx] = processDataTag_ (el, type);

	return E_OK;
}

std::vector<char> Repo::processDataTag_ (xmlNode* el, const char* name) {
        xmlNode* local = el;
	size_t len = strlen (name);

        local = local->children;
        while (local) {
	        if (strncmp ((const char*)local->name, "location", 8) == 0) break;
                local = local->next;
	}
	if (local) {
	        std::string url = repomd;
	        url.resize (url.length () - 19);
	        url.append ((const char*)xmlGetProp (local, (const xmlChar*)"href"));
		if ( strncmp (".xml.gz", std::string (url.end () - 7, url.end ()).c_str (), 7) == 0 ) {
			std::cout << "process " << url << std::endl;
//			file_dl (url);
			return dl_content ();
		}
        }

        return std::vector<char> ();
}

