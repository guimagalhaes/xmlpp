#include "xml_parser.h"
#ifdef DEBUG
#include <iostream>
#endif 

using namespace std;

xml_parser::xml_parser(const string &doc_name): xml_encode("ISO-8859-1")
{    
    set_doc_name(doc_name);
}

xml_parser::~xml_parser()
{
    xmlFreeDoc(doc);
}

string xml_parser::encode_convert(const string &in, const string &encoding) const
{
    char *out;
    int ret, size, out_size, temp;
    xmlCharEncodingHandlerPtr handler;
    
    if (!in.length()) {
        return "";
    }
    
        size = in.length() + 1; 
        out_size = size*2-1; 
        out = (char *) malloc((size_t)out_size); 

        if (out) {
                handler = xmlFindCharEncodingHandler(encoding.c_str());
                
                if (!handler) {
                        free(out);
                        out = NULL;
                }
        }
        if (out) {
                temp=size-1;
                ret = handler->input(reinterpret_cast<unsigned char *>(out), &out_size, 
                    reinterpret_cast<const unsigned char*>(in.c_str()), &temp);
                if (ret != temp || temp-size+1) {
#ifdef DEBUG
                        if (ret) {
                                cerr << "Conversion wasn't successful." <<  " ret=" << ret << " temp=" << temp << " size=" << size << endl;
                                cerr << " in=" << in << " encoding=" << encoding << endl;
                        } else {
                                cerr << "Conversion wasn't successful. Converted "<< temp << " octets." << endl;
                        }
#endif
                        free(out);
                        out = NULL;
                } else {
                        out = (char *) realloc(out,out_size+1); 
                        out[out_size]=0; /*null terminating out*/
                        
                }
        }
        else {
#ifdef DEBUG
                cerr << "no mem" << endl;
#endif
            return "";
        }

    string s = string(out);
    free(out);
    
    return s;
}

bool xml_parser::is_element_of_type(xml_node_ptr cur,const string &type) const
{
    return is_str_equal(reinterpret_cast<const char*>(cur->name),type);
}

bool xml_parser::attribute_exists(xml_node_ptr cur,const string &attribute) const
{
    xmlChar *attr;
    
    attr = xmlGetProp(cur, reinterpret_cast<const xmlChar *> (attribute.c_str()));
    if (attr == NULL)
        return false;
    else {
        xmlFree(attr);
        return true;
    }
}

bool xml_parser::is_element_text_equal(xml_node_ptr cur,const string &element,const string &text) const
{
    xmlChar *element_text;
    
    if (is_element_of_type(cur,element)) {
        element_text = xmlNodeListGetString(doc, cur->children_node, 1);
        if (element_text != NULL) {
            if (is_str_equal(reinterpret_cast<const char*> (element_text),text))
                return true;
            xmlFree(element_text);
        }
    }
    
    return false;
}

bool xml_parser::is_str_equal(const string &s1, const string &s2) const
{
    if ((!xmlStrcmp(reinterpret_cast<const xmlChar *> (s1.c_str()), reinterpret_cast<const xmlChar *> (s2.c_str()))))
        return true;
    else
        return false;
}

