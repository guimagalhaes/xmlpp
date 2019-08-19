#ifndef XMLRWH_
#define XMLRWH_

#include "xml_reader.h"
#include "xml_writer.h"

class xml_rw: public xml_reader, public xml_writer
{
    public:
        xml_rw(const std::string &docname):
            xml_parser(docname),
            xml_reader(docname),
            xml_writer(docname) 
            {}        
        //xmlRW() {}        
        virtual ~xml_rw() {}
};

#endif
