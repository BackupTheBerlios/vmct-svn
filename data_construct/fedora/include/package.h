#ifndef PACKAGE_H
#define PACKAGE_H

struct Version {
        std::string epoch;
        std::string ver;
        std::string rev;
};

struct Checksum {
        std::string value;
        std::string type;
        std::string pkgId;
};

struct Size {
        std::string package;
        std::string installed;
        std::string archive;
};

struct Entry {
        std::string name;
        std::string flags;
        std::string epoch;
        std::string ver;
};

struct Package {
        std::string name;
        std::string arch;
        std::string summary;
        std::string description;
        std::string packager;
        std::string url;
        Version version;
        Checksum checksum;
        Size size;
        std::string location;
        std::vector<Entry> provides;
        std::vector<Entry> requires;
};

#endif

