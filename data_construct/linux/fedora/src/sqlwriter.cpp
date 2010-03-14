#include "sqlwriter.h"
#include "func.h"

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

boost::shared_ptr<Writer> SQLFactory::createWriter (const std::string& path) {
	return boost::shared_ptr<Writer>(new SQLWriter (path));
}

boost::shared_ptr<Row> SQLFactory::createRow (const TableInfo& t) {
	return boost::shared_ptr<Row>(new SQLRow (t));
}

