#include "xml_writer.h"

#ifdef DEBUG
#include <iostream>
#endif

using namespace std;

bool xml_writer::new_doc(const string &version)
{
    set_doc(xmlNewDoc(reinterpret_cast<const xmlChar *> (version.c_str())));
    
    if (get_doc() == NULL)
        return false;
    
    return true;
}

xml_node_ptr xml_writer::new_doc_node(const string &element, const string &text)
{
    xml_node_ptr root;
    
    string celement = encode_convert(element, xml_encode);
    string ctext = encode_convert(text, xml_encode);
    
    if (text == "")
        root = xmlNewDocNode(get_doc(), NULL, reinterpret_cast<const xmlChar *> (celement.c_str()), 
            NULL);
    else
        root = xmlNewDocNode(get_doc(), NULL, reinterpret_cast<const xmlChar *> (celement.c_str()), 
            reinterpret_cast<const xmlChar *> (ctext.c_str()));
    xmlDocSetRootElement(get_doc(), root);
    set_root(root);
    
    return root;
}

bool xml_writer::save_doc() const
{
    if (get_doc() != NULL) {
        if (xmlSaveFormatFileEnc(get_doc_name().c_str(), get_doc(), xml_encode.c_str(), 1) >= 0)
        //if (xmlSaveFile (doc_name.c_str(), get_doc()) >= 0)
        //if (xmlSaveFileEnc(get_doc_name().c_str(), get_doc(), xml_encode.c_str()) >= 0)        
            return true;
    }
    
    return false;
}

xml_node_ptr xml_writer::insert_element(xml_node_ptr cur,const string &element) const
{
    string celement = encode_convert(element, xml_encode);
    
    return xmlNewChild(cur, NULL, reinterpret_cast<const xmlChar *> (celement.c_str()), NULL);
}

xml_node_ptr xml_writer::insert_text_element(xml_node_ptr cur,const string &element,const string &text) const
{
    string celement = encode_convert(element, xml_encode);
    string ctext = encode_convert(text, xml_encode);
    
    return xmlNewTextChild (cur, NULL, reinterpret_cast<const xmlChar *> (celement.c_str()), 
        reinterpret_cast<const xmlChar *> (ctext.c_str()));
}

void xml_writer::set_attribute(xml_node_ptr cur,const string &attr_name,const string &attr_value) const
{
    string cattr_name = encode_convert(attr_name, xml_encode);
    string cattr_value = encode_convert(attr_value, xml_encode);
    
    xmlSetProp(cur, reinterpret_cast<const xmlChar *> (cattr_name.c_str()), 
        reinterpret_cast<const xmlChar *> (cattr_value.c_str()));
}

xmlAttrPtr xml_writer::insert_attribute(xml_node_ptr cur,const string &attr_name,const string &attr_value) const
{
    string cattr_name = encode_convert(attr_name, xml_encode);
    string cattr_value = encode_convert(attr_value, xml_encode);
    
    return xmlNewProp (cur, reinterpret_cast<const xmlChar *> (cattr_name.c_str()), 
        reinterpret_cast<const xmlChar *> (cattr_value.c_str()));
}

void xml_writer::delete_element(xml_node_ptr node) const
{
    //xmlUnlinkNode(node); 
    //xmlFreeNode(node);
    xmlFreeNodeList(node);
}

