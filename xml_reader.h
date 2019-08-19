#ifndef XMLREADERH_
#define XMLREADERH_

#include "xml_parser.h"

class xml_reader: public virtual xml_parser
{
    public:
        xml_reader(const std::string &docname):xml_parser(docname) {}
        //xml_reader():xmlParser {}
        virtual ~xml_reader() {}
        
        //parse a existent xml file
        //must be called first
        bool parse_file();
        
        //parse root element from doc, must be called after parseFile
        //if a new xml will be created this method don't have to be called
        //otherwise, if a existent xml will be read, this method must be called
        //xmlFail must be tested after calling
        xml_node_ptr xml_doc_get_root();
        
        //return the child element with this text
        xml_node_ptr get_element(xml_node_ptr cur,const std::string &element,const std::string &text) const;
        
        //return the text of the element cur
        std::string get_text(xml_node_ptr cur) const;
        
        //return this attribute value
        std::string get_attribute(xml_node_ptr cur,const std::string &attribute) const;
};

#endif
