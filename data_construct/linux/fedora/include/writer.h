#ifndef __WRITER_H__
#define __WRITER_H__

#include <vector>
#include <string>
#include <ostream>
#include <fstream>

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
};

class SQLRow : public Row {
public:
	SQLRow (const TableInfo&);
	virtual ~SQLRow ();
	void out (std::ostream*) const;
};

class Writer {
protected:
	std::string path;
public:
	Writer (const std::string&);
	virtual ~Writer ();
	virtual void out (Row*) = 0;
};

class SQLWriter : public Writer {
	std::ofstream of;
public:
	SQLWriter (const std::string&);
	virtual ~SQLWriter ();
	void out (Row*);
};

class WriterFactory {
public:
	virtual Writer* createWriter (const std::string&) = 0;
	virtual Row* createRow (const TableInfo&) = 0;
};

class SQLFactory : public WriterFactory {
public:
	Writer* createWriter (const std::string&);
	Row* createRow (const TableInfo&);
};

#endif 

