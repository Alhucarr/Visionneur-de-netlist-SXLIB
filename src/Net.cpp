// -*- explicit-buffer-name: "Net.cpp<M1-MOBJ/4-5>" -*-
#include "Net.h"


namespace Netlist {
    using namespace std;
            Net::Net     ( Cell* cell, const std::string& name, Term::Type type):owner_(cell),name_(name),type_(type){
                owner_->add(this);
            }
            Net::~Net     (){
                for(unsigned int i = 0; i < nodes_.size(); ++i){
                    NodeTerm* nt = dynamic_cast<NodeTerm*>(nodes_[i]);
                    nt->getTerm()->setNet(NULL);
                }
                owner_->remove(this);
            }
            Cell* Net::getCell () const{
                return owner_;
            }
            const std::string& Net::getName () const{
                return name_;
            }
            unsigned int Net::getId () const{
                return id_;
            }
            Term::Type Net::getType () const{
                return type_;
            }
            const std::vector<Node*>& Net::getNodes () const{
                return nodes_;
            }
            Node* Net::getNode (size_t id) const{
                return nodes_[id];
            }
            size_t Net::getFreeNodeId () const{
                unsigned int i;
                for(i=0;i<nodes_.size();i++){
                    if(nodes_[i]==NULL){
                        return i;
                    }
                }return i;
            }
            void Net::add    ( Node* n){
                unsigned int id = getFreeNodeId();
                n->setId(id);
                if(id < nodes_.size())
                    nodes_[id] = n;
                else{ 
                    nodes_.resize(id+1);
                    nodes_.push_back(n);
                }
            }
            void  Net::add ( Line* line ){
                if (line) lines_.push_back( line ); 
            }

            bool Net::remove ( Node* n){
                for(unsigned int i = 0; i < nodes_.size(); ++i){
                    if(nodes_[i] == n){
                        nodes_[i] = NULL;
                        return true;
                    }
                }
                return false;
            }

            bool  Net::remove ( Line* line ){
                if (line) {
                    for ( vector<Line*>::iterator il = lines_.begin() ; il != lines_.end() ; ++il ) {
                        if (*il == line) {
                            lines_.erase( il );
                            return true;
                        }
                    }
                }
                return false;
            }
            
            void Net::toXml(std::ostream& o){
                o << indent << "<net name=\"" << name_ << "\" type=\"" << Term::toString(type_) << "\"/>" << std::endl;
                for(unsigned int i = 0; i < nodes_.size(); ++i){
                    nodes_[i]->toXml(o);
                }
                o << indent << "</net>" << std::endl;
            }
            Net* Net::fromXml(Cell* c, xmlTextReaderPtr TxtR){
                std::string name = xmlCharToString(     xmlTextReaderGetAttribute(   TxtR, (const xmlChar*) "name"     )     );
                std::string type = xmlCharToString   (xmlTextReaderGetAttribute(  TxtR, (const xmlChar*) "type")     );
                const xmlChar* nodeTag = xmlTextReaderConstString( TxtR, (const xmlChar*)"node" );

                if(name.empty() || type.empty())
                    return NULL;
                Term::Type t;
                if(!type.compare("Internal"))
                    t = Term::Internal;
                else if(!type.compare("External"))
                    t = Term::External;
                else
                    return NULL;
                Net* n = new Net(c, name, t);
                while ( true ) {
                    int status = xmlTextReaderRead(TxtR);
                    if (status != 1) {
	                    if (status != 0) {
	                        cerr << "[ERROR] Cell::fromXml(): Unexpected termination of the XML parser." << endl;
	                    }
	                    break;
                    }
                    switch ( xmlTextReaderNodeType(TxtR) ){
                        case XML_READER_TYPE_COMMENT:
                        case XML_READER_TYPE_WHITESPACE:
                        case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
                        continue;
                    }
                    const xmlChar* nodeName = xmlTextReaderConstLocalName( TxtR );
                    if(nodeName == nodeTag){
      	                if(xmlTextReaderNodeType(TxtR) == XML_READER_TYPE_ELEMENT){
      	                    if(!Node::fromXml(n, TxtR))
	                            return NULL;
	                    }
                        else if(xmlTextReaderNodeType(TxtR) == XML_READER_TYPE_END_ELEMENT)
	                        break;
	                    else
	                        return NULL; 
                        }
                } return n;
            }
}