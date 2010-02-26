#include <iostream>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <stdio.h>

#include "func.h"
#include "repo.h"
#include "dl.h"
#include "err.h"
#include "log.h"
#include "package.h"
#include "SimpleIni.h"

typedef CSimpleIniA::TNamesDepend sections_t;
typedef CSimpleIniA::TNamesDepend keys_t;

enum TAG {
	T_FILELISTS = 0,
	T_PRIMARY,
//	T_GROUP
};

static const char* data_tags [] =
{
        "filelists",
        "primary",
//        "group",
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
		log (std::string ("process ").append (i->pItem));
		if (ini.GetValue (i->pItem, "enabled")[0] == '1') {
			keys_t key;
			ini.GetAllKeys (i->pItem, key);
			for (keys_t::iterator j = key.begin (); j != key.end (); j++) {
				if (strncmp ("baseurl", j->pItem, 7) == 0) {
					url = ini.GetValue (i->pItem, "baseurl");
					url.append ("/repodata/repomd.xml");
				}
			}
			if (!url.length ()) {
				url = getBaseUrl (ini.GetValue (i->pItem, "mirrorlist"));
			}
			Repo repo_;
			if (repo_.processRepo (url) == 0) repo.push_back (repo_);
		}
	}
}

// download and process repomd.xml
int Repo::processRepo (const std::string& repomd) {
	this->repomd = repomd;
	file_dl (repomd);

	xmlDocPtr doc = xmlReadMemory(&*dl_content ().begin (), dl_content ().size (), "noname.xml", NULL, 0);
	if (!doc) {
		return E_XML;
	}

	this->files.resize (data_tag_count);

	xmlNode *el = xmlDocGetRootElement(doc);
	if (el && strncmp ((const char*)el->name, "repomd", 6) == 0) {
		el = el->children;
		for (;el; el = el->next) {
			if (strncmp ((const char*)el->name, "data", 4) == 0) {
				processDataTag (el);
			}
		}
	} else {
		xmlFreeDoc(doc);
		std::cout << "err";
		return E_XML;
	}

	xmlFreeDoc(doc);

	processPrimary ();
	processFileList ();

	return E_OK;
}

// extract information from <data>-tags
int Repo::processDataTag (xmlNode* el) {
	const char* type = (const char*)xmlGetProp (el, (const xmlChar*)"type");

	int idx = check (type);
	if (idx == -1) return E_NONE;
	
	this->files[idx] = processDataTag_ (el, type);

	return E_OK;
}

std::string Repo::processDataTag_ (xmlNode* el, const char* name) {
        xmlNode* local = el;
	size_t len = strlen (name);

        local = local->children;
        for (;local;local = local->next) {
	        if (strncmp ((const char*)local->name, "location", 8) == 0) break;
	}
	if (local) {
	        std::string url = repomd;
	        url.resize (url.length () - 19);
		std::string fileName = (const char*)xmlGetProp (local, (const xmlChar*)"href");
	        url.append (fileName);
		if ( strncmp (".xml.gz", std::string (url.end () - 7, url.end ()).c_str (), 7) == 0 ) {
			return dl_unpack (url);
		}
        }

        return "";
}

void ifTextField (xmlNode* el, const char* name, std::string& value) {
	if (!el) return;
	if (strncmp ((const char*)el->name, name, strlen (name)) == 0) {
		if (el->children && el->children->content) value = (const char*)el->children->content;
	}
}

void ifGetProp (xmlNode* el, const char* elName, const char* propName, std::string& value) {
	if (!el) return;
	if (strncmp ((const char*)el->name, elName, strlen (elName)) == 0) {
		const char* ptr = (const char*)xmlGetProp (el, (const xmlChar*)propName);
		if (ptr) value.assign (ptr);
	}
}

void extractList (xmlNode* el2, const char* name, std::vector<Entry>& data) {
	if (strncmp ((const char*)el2->name, name, strlen (name)) == 0) {
		for (xmlNode* el3 = el2->children; el3; el3 = el3->next) {
		        if (strncmp ((const char*)el3->name, "entry", 5) == 0) {
		                Entry e;
		                ifGetProp (el3, "entry", "name", e.name);
		                ifGetProp (el3, "entry", "flags", e.flags);
		                ifGetProp (el3, "entry", "epoch", e.epoch);
		                ifGetProp (el3, "entry", "ver", e.ver);
		                data.push_back (e);
		        }
		}
	}
}

void Repo::processPrimary () {
	if (!files.size () && !files[T_PRIMARY].length ()) return;
	log ("primary " + files[T_PRIMARY]);
	xmlDoc *doc = xmlReadFile (files[T_PRIMARY].c_str (), NULL, 0);
	if (!doc) {
		log ("error group file");
		return;
	}

	Package pkg;

	xmlNode *el = xmlDocGetRootElement(doc); // metadata
	for (el = el->children; el; el = el->next) {
		if (strncmp ((const char*)el->name, "package", 7) != 0) continue;
		pkg.provides.resize (0);
                pkg.requires.resize (0);
		for (xmlNode* local = el->children; local; local = local->next) {
			ifTextField (local, "name", pkg.name);
			ifTextField (local, "arch", pkg.arch);
			ifTextField (local, "checksum", pkg.checksum.value);
			ifTextField (local, "summary", pkg.summary);
			ifTextField (local, "description", pkg.description);
			ifTextField (local, "packager", pkg.packager);
			ifTextField (local, "url", pkg.url);
			ifGetProp (local, "version", "epoch", pkg.version.epoch);
			ifGetProp (local, "version", "ver", pkg.version.ver);
			ifGetProp (local, "version", "rev", pkg.version.rev);
			ifGetProp (local, "checksum", "type", pkg.checksum.type);
			ifGetProp (local, "checksum", "pkgId", pkg.checksum.pkgId);
			if (strncmp ((const char*)local->name, "format", 6) == 0) {
				for (xmlNode* el2 = local->children; el2; el2 = el2->next) {
					extractList (el2, "provides", pkg.provides);
					extractList (el2, "requires", pkg.requires);
				}
			}
		}
/*		log ("Name " + pkg.name);
		log ("Version " + pkg.version.ver);
		log ("Arch " + arch);
		log ("Checksum " + checksum);
		log ("Summary " + summary);
		log ("Description " + description);
		log ("Packager " + packager);
		log ("Url " + url);*/
	}

	xmlFreeDoc(doc);
}

void Repo::processFileList () {
	if (!files.size () && !files[T_FILELISTS].length ()) return;
	log ("filelist " + files[T_FILELISTS]);
	xmlDoc *doc = xmlReadFile (files[T_FILELISTS].c_str (), NULL, 0);
        if (!doc) {
                log ("error group file");
                return;
        }

	xmlNode *el = xmlDocGetRootElement(doc); // filelists
	for (el = el->children; el; el = el->next) {
		if (strncmp ((const char*)el->name, "package", 7) != 0) continue;
		std::string pkgId;
		ifGetProp (el, "package", "pkgId", pkgId);
		log ("package " + pkgId);
		for (xmlNode* local = el->children; local; local = local->next) {
			std::string file;
			ifTextField (local, "file", file);
			if (file.length ()) log ("file " + file);
		}
	}

	xmlFreeDoc(doc);
}


