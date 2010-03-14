#include "writer.h"

TableInfo::TableInfo (const std::string& n) : name (n) {}

void TableInfo::addField (const std::string& f) {
	field.push_back (f);
}

std::string TableInfo::getField (size_t n) const {
	if (n < field.size ()) return field[n];
	return "";
}

std::string TableInfo::getName () const { return name; }

size_t TableInfo::fieldCount () const {
	return field.size ();
}

Row::Row (const TableInfo& t) : info (t) {
	value.resize (info.fieldCount ());
}

Row::~Row () {}

void Row::setValue (size_t i, const std::string& v) {
	value[i] = v;
}

std::string Row::getName () const {
	return info.getName ();
}

Writer::Writer (const std::string& p) : path (p) {}

Writer::~Writer () {
}

int Writer::getError () const {
	return error;
}

