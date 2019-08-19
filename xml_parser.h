#ifndef XMLPARSERH_
#define XMLPARSERH_

#include <string>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include "fail_base.h"

/*
** Base class only. Use xml_read, xml_write or xml_rw.
**
*/

typedef xmlDocPtr xml_doc_ptr;
typedef xmlNodePtr xml_node_ptr;

#define children_node xmlChildrenNode

class xml_parser
{
    private:
        std::string doc_name;
        xml_doc_ptr doc;
        xml_node_ptr root;
    
    protected:
        std::string xml_encode;
    
    public:
        //fail object
        fail_base xml_fail;
    
        //constructor, parse doc file
        xml_parser(const std::string &doc_name);
        //xml_parser() {}        
        virtual ~xml_parser() = 0;
        
        //convert a encode of a string to the encode "encoding"
        std::string encode_convert(const std::string &in, const std::string &encoding) const;
        
        //get and set encoding
        std::string get_xml_encode() { return xml_encode; }
        void set_xml_encode(const std::string &enc) { xml_encode = enc; }
        
        //set and get doc file name
        void set_doc_name(const std::string &name) {doc_name = name;}
        std::string get_doc_name() const {return doc_name;}

        //get and set xml doc 
        xml_doc_ptr get_doc() const {return doc;}
        void set_doc(xml_doc_ptr _doc) {doc = _doc;}
        //get and set root element
        xml_node_ptr get_root() const {return root;}
        void set_root(xml_node_ptr cur) {root = cur;}
        
        //return true if strings are equal
        bool is_str_equal(const std::string &s1, const std::string &s2) const;
        
        //return true if element is of this type
        bool is_element_of_type(xml_node_ptr cur,const std::string &type) const;
        
        //return true if element has this attribute
        bool attribute_exists(xml_node_ptr cur,const std::string &attribute) const;
        
        //return true if this element has text equal to text parameter
        bool is_element_text_equal(xml_node_ptr cur,const std::string &element,const std::string &text) const;
};

#endif
