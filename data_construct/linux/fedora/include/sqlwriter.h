#ifndef __SQL_WRITER_H__
#define __SQL_WRITER_H__

#include "writer.h"

class SQLRow : public Row {
public:
	SQLRow (const TableInfo&);
	virtual ~SQLRow ();
	void out (std::ostream*) const;
};

class SQLWriter : public Writer {
	std::ofstream of;
public:
	SQLWriter (const std::string&);
	virtual ~SQLWriter ();
	void out (boost::shared_ptr<Row>);
};

class SQLFactory : public WriterFactory {
public:
	boost::shared_ptr<Writer> createWriter (const std::string&);
	boost::shared_ptr<Row> createRow (const TableInfo&);
};

#endif 

