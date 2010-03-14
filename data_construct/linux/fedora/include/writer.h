#ifndef __WRITER_H__
#define __WRITER_H__

#include <vector>
#include <string>
#include <map>
#include <ostream>
#include <fstream>
#include <boost/shared_ptr.hpp>

class TableInfo {
	std::vector<std::string> field;
	std::string name;
public:
	TableInfo (const std::string&);
	void addField (const std::string&);
	std::string getField (size_t) const;
	std::string getName () const;
	size_t fieldCount () const;
};

class Row {
protected:
	TableInfo info;
	std::vector<std::string> value;
public:
	Row (const TableInfo&);
	virtual ~Row ();
	virtual void setValue (size_t, const std::string&);
	virtual void out (std::ostream*) const = 0;
	std::string getName () const;
};

class Writer {
protected:
	std::string path;
	int error;
public:
	Writer (const std::string&);
	virtual ~Writer ();
	virtual void out (boost::shared_ptr<Row>) = 0;
	int getError () const;
};

class WriterFactory {
public:
	virtual boost::shared_ptr<Writer> createWriter (const std::string&) = 0;
	virtual boost::shared_ptr<Row> createRow (const TableInfo&) = 0;
};

#endif 

