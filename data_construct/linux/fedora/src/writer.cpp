#include "writer.h"
#include "func.h"

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

/////////////////////////////////////////

Row::Row (const TableInfo& t) : info (t) {
	value.resize (info.fieldCount ());
}

Row::~Row () {}

void Row::setValue (size_t i, const std::string& v) {
	value[i] = v;
}

////////////////////////////////////7

SQLRow::SQLRow (const TableInfo& t) : Row (t) {}

SQLRow::~SQLRow () {}

void SQLRow::out (std::ostream* os) const {
	(*os) << "INSERT INTO " << info.getName () << " (";
	size_t size = info.fieldCount ();
	for (size_t i = 0; i < size; i++) {
		(*os) << info.getField (i);
		if (i != size - 1) (*os) << ",";
	}
	(*os) << ") VALUES (";
	for (size_t i = 0; i < size; i++) {
		(*os) << "'" << escape (value[i]) << "'";
		if (i != size - 1) (*os) << ",";
	}
	(*os) << ");" << std::endl;
}

/////////////////////////////

Writer::Writer (const std::string& p) : path (p) {}

Writer::~Writer () {
}

/////////////////////////////

SQLWriter::SQLWriter (const std::string& p) : Writer (p) {
	of.open (path.c_str ());
}

SQLWriter::~SQLWriter () {
	of.close ();
}

void SQLWriter::out (Row* r) {
	r->out (&of);
}

/////////////////////////////////

Writer* SQLFactory::createWriter (const std::string& path) {
	return new SQLWriter (path);
}

Row* SQLFactory::createRow (const TableInfo& t) {
	return new SQLRow (t);
}

