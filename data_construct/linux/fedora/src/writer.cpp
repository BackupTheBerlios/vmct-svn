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

std::string Row::getName () const {
	return info.getName ();
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
CSVRow::CSVRow (const TableInfo& t) : Row (t) {}

CSVRow::~CSVRow () {}

void CSVRow::out (std::ostream* os) const {
	size_t size = info.fieldCount ();
        for (size_t i = 0; i < size; i++) {
                (*os) << escape (value[i]);
                if (i != size - 1) (*os) << ";";
        }
	(*os) << std::endl;
}


/////////////////////////////

Writer::Writer (const std::string& p) : path (p) {}

Writer::~Writer () {
}

int Writer::getError () const {
	return error;
}

/////////////////////////////

SQLWriter::SQLWriter (const std::string& p) : Writer (p) {
	error = 0;
	of.open (path.c_str ());
}

SQLWriter::~SQLWriter () {
	of.close ();
}

void SQLWriter::out (boost::shared_ptr<Row> r) {
	r->out (&of);
}

/////////////////////////////////

#include <sys/stat.h>
#include <sys/types.h>

CSVWriter::CSVWriter (const std::string& p) : Writer (p) {
	mode_t mode = 0777;
	error = mkdir (path.c_str (), mode);
}

CSVWriter::~CSVWriter () {
	for (of_t::iterator it = of.begin (); it != of.end (); it++) {
		it->second->close ();
	}
}

void CSVWriter::out (boost::shared_ptr<Row> r) {
	std::string rowName = r->getName ();
	of_t::iterator it = of.lower_bound (rowName);
	if (it == of.end () || it->first.compare (rowName) != 0) {
		std::string fileName = path + "/" + r->getName ();
		of[rowName] = boost::shared_ptr<std::ofstream> (new std::ofstream ());
		of[rowName]->open (fileName.c_str ());
	}
	r->out (of[rowName].get ());
}


/////////////////////////////////

boost::shared_ptr<Writer> SQLFactory::createWriter (const std::string& path) {
	return boost::shared_ptr<Writer>(new SQLWriter (path));
}

boost::shared_ptr<Row> SQLFactory::createRow (const TableInfo& t) {
	return boost::shared_ptr<Row>(new SQLRow (t));
}

//////////////////////////////

boost::shared_ptr<Writer> CSVFactory::createWriter (const std::string& path) {
        return boost::shared_ptr<Writer>(new CSVWriter (path));
}

boost::shared_ptr<Row> CSVFactory::createRow (const TableInfo& t) {
        return boost::shared_ptr<Row>(new CSVRow (t));
}

