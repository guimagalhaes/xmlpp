#include <iostream>
#include <string>
#include "xml_rw.h"

using namespace std;

void parse_story (xml_node_ptr cur, xml_rw *xml)
{
    string site;    //elemento site
    string url;        //atributo url do elemento site
    string other;    //elemento other
    
    cur = cur->children_node;
    while (cur != NULL) {
        if (xml->is_element_of_type(cur,"site")) {
            site = xml->get_text(cur);
            url = xml->get_attribute(cur,"url");
            if (site.size() && url.size()) {
                cout << "site: " << site << endl;
                cout << "url: " << url << endl << endl;
                site = "";
                url = "";
            }
         }
        
        if (xml->is_element_of_type(cur,"other")) {
            other = xml->get_text(cur);
            cout << "other: " << other << endl << endl;
         }
        
        cur = cur->next;
    }
    
    return;
}

void parse_cast (xml_node_ptr cur,xml_rw *xml)
{
    string person;        //elemento person
    string people;        //atributo do elemento storycast    
    
    // xmlAttrPtr newattr;        //novo atributo a ser inserido
    // xml_node_ptr newnode;        //novo elemento a ser inserido
    
    people = xml->get_attribute(cur,"people");
    cout << "people: " << people << endl;
    int i = atoi(people.c_str());
    ++i;
    char s[4] = {0};
    sprintf(s,"%i",i);
    xml->set_attribute(cur,"people",s);
    
    // newnode = xml->insert_text_element(cur,"person","Joe");
    // newattr = xml->insert_attribute(newnode,"attrTest","attrValue");
    
    cur = cur->children_node;
    while (cur != NULL) {
        if (xml->is_element_of_type(cur,"person")) {
            person = xml->get_text(cur);
            cout << "person: " << person << endl;
            if (xml->is_str_equal(person,"Guilherme")) {
                if (!xml->attribute_exists(cur,"sector")) {
                    xml->insert_attribute(cur,"sector","programmer");
                }
            }
         }
        
        cur = cur->next;
    }
    
    return;
}

int main(int args,char** argv)
{    
    xml_rw *xml;
    xml_node_ptr cur;

    if (args == 2) {
        xml = new xml_rw(argv[1]);
        if (!xml) {
            cerr << "xml is null" << endl;
            exit(0);
        }
    }
    else {
        cout << "xml name argument missed" << endl;
        exit(0);
    }
    
    if (!xml->parse_file()) {
        cerr << "could not parse file" << endl;
        delete xml;
        return 0;
    }
    
    cur = xml->xml_doc_get_root();
    if (xml->xml_fail.failed()) {
        delete xml;
        return 0;
    }
    
    if (!xml->is_element_of_type(cur,"story")) {
        cerr << "document of the wrong type, root node != story" << endl;
        delete xml;
        return 0;
    }
    
    cur = cur->children_node;
    while (cur != NULL) {
        if (xml->is_element_of_type(cur,"storyinfo")) {
            parse_story (cur, xml);
        }
        
        if (xml->is_element_of_type(cur,"storycast")) {
            parse_cast (cur,xml);
        }
         
        cur = cur->next;
    }
    
    xml->set_doc_name("xml/new.xml");
    xml->save_doc();
    
    delete xml;
}

