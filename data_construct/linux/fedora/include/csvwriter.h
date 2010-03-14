#ifndef __CSV_WRITER_H__
#define __CSV_WRITER_H__

#include <map>
#include "writer.h"

class CSVRow : public Row {
public:
        CSVRow (const TableInfo&);
        virtual ~CSVRow ();
        void out (std::ostream*) const;
};


class CSVWriter : public Writer {
	typedef std::map<std::string, boost::shared_ptr<std::ofstream> > of_t;
        of_t of;
public:
        CSVWriter (const std::string&);
        virtual ~CSVWriter ();
        void out (boost::shared_ptr<Row>);
};


class CSVFactory : public WriterFactory {
public:
        boost::shared_ptr<Writer> createWriter (const std::string&);
        boost::shared_ptr<Row> createRow (const TableInfo&);
};

#endif 

