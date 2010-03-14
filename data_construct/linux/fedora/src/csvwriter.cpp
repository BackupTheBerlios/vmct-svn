#include "csvwriter.h"
#include "func.h"

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


boost::shared_ptr<Writer> CSVFactory::createWriter (const std::string& path) {
        return boost::shared_ptr<Writer>(new CSVWriter (path));
}

boost::shared_ptr<Row> CSVFactory::createRow (const TableInfo& t) {
        return boost::shared_ptr<Row>(new CSVRow (t));
}

