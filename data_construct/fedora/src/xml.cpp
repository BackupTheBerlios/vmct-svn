#include <libxml/parser.h>
#include <libxml/tree.h>

class XML_INIT {
public:
	XML_INIT () {}
	~XML_INIT () {xmlCleanupParser();}
};

static XML_INIT xml = XML_INIT ();

