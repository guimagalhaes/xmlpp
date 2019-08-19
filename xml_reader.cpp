#include "xml_reader.h"

#ifdef DEBUG
#include <iostream>
#endif

using namespace std;

bool xml_reader::parse_file()
{
    set_doc(xmlParseFile(get_doc_name().c_str()));
    
    if (get_doc() == NULL ) {
#ifdef DEBUG
        cerr << "Document not parsed successfully." << endl;
#endif
        //xmlFail.set_failed();
        return false;
    }
    
    return true;
}

xml_node_ptr xml_reader::xml_doc_get_root() {
    set_root(xmlDocGetRootElement(get_doc()));
    
    if (get_root() == NULL) {
#ifdef DEBUG
        cerr << "empty document" << endl;
#endif
        xml_fail.set_failed();
        return NULL;
    }
    
    return get_root();
}

string xml_reader::get_attribute(xml_node_ptr cur,const string &attribute) const
{
    string ret = "";
    xmlChar *s = xmlGetProp(cur, reinterpret_cast<const xmlChar *> (attribute.c_str()));
    
    if (s) {
        ret = reinterpret_cast<char *> (s);
        xmlFree(s);
    }
    
    string cret = encode_convert(ret, xml_encode);
    //string cret = encode_convert(ret, "UTF-8");
    //string cret = encode_convert(ret, "ASCII");
    return cret;
}

xml_node_ptr xml_reader::get_element(xml_node_ptr cur,const string &element,const string &text) const
{
    xmlChar *element_text;
    
    cur = cur->children_node;
    while (cur != NULL) {
        if (is_element_of_type(cur,element)) {
            element_text = xmlNodeListGetString(get_doc(), cur->children_node, 1);
            
            if (element_text != NULL) {
                if (is_str_equal(reinterpret_cast<const char *>(element_text),text)) {
                    xmlFree(element_text);
                    return cur;
                }
                
                xmlFree(element_text);
            }
         }
        
        cur = cur->next;
    }
    
    return NULL;
}

string xml_reader::get_text(xml_node_ptr cur) const
{
    string ret = "";
    xmlChar *s = xmlNodeListGetString(get_doc(), cur->children_node, 1); // 0 to not expand entities
    
    if (s) {
        ret = reinterpret_cast<char *> (s);
        xmlFree(s);
    }
    
    string cret = encode_convert(ret, xml_encode);
    //string cret = encode_convert(ret, "UTF-8");
    return cret;
}
