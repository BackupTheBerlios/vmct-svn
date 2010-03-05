#include <libxml/parser.h>
#include <libxml/tree.h>
#include "log.h"

class XML_INIT {
public:
	XML_INIT () {log ("libxml init");}
	~XML_INIT () {xmlCleanupParser(); log ("libxml deinit");}
};

static XML_INIT xml = XML_INIT ();

