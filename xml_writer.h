#ifndef XMLWRITERH_
#define XMLWRITERH_

#include "xml_parser.h"
#include <libxml/tree.h>

class xml_writer: public virtual xml_parser
{
    public:
        xml_writer(const std::string &docname):xml_parser(docname) {}
        //xml_writerr():xmlParser() {}
        virtual ~xml_writer() {}
        
        //create a new xml file
        //must be called first
        bool new_doc(const std::string &version = "1.0");
            
        //insert root element
        //must be called just one time, after newDoc
        xml_node_ptr new_doc_node(const std::string &element, const std::string &text = "");
            
        //save modifications on file
        bool save_doc() const;
        
        //insert empty element
        //not tested
        xml_node_ptr insert_element(xml_node_ptr cur,const std::string &element) const;
        //insert element with text
        xml_node_ptr insert_text_element(xml_node_ptr cur,const std::string &element,const std::string &text) const;
        //insert atribute with value on element
        void set_attribute(xml_node_ptr cur,const std::string &attr_name,const std::string &attr_value) const;
        xmlAttrPtr insert_attribute(xml_node_ptr element,const std::string &attr_name,const std::string &attr_value) const;
        
        //delete an element
        void delete_element(xml_node_ptr node) const;
};

#endif

