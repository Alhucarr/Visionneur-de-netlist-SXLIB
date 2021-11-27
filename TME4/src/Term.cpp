// -*- explicit-buffer-name: "Term.cpp<M1-MOBJ/4-5>" -*-

#include "Term.h"
#include "Net.h"

namespace Netlist {
    using namespace std;
            Term::Term ( Cell* cell  , const std::string name, Direction d)
            :owner_(cell),name_(name),direction_(d),type_(External),net_(NULL),node_(this){
                ((Cell*)owner_)->add(this);
            }
            Term::Term ( Instance* I, const Term* modelTerm ):owner_(I),name_(modelTerm->getName()),direction_(modelTerm->getDirection()),type_(Internal),net_(NULL),node_(this){
                ((Instance*)owner_)->add(this);
            }
            Term::~Term (){
                if(type_ == Internal){
                    ((Instance*)owner_)->remove(this);
                }
                else if(type_ == External){
                    ((Cell*)owner_) ->remove(this);
                }
                if(net_ != NULL){
                    net_->remove(&node_);
                }
            }
            void  Term::setNet       ( Net* n){
                NodeTerm* nt = dynamic_cast<NodeTerm*>(&node_);
                if(n == NULL && net_ != NULL){
                        if(nt->getTerm() == this){
                            net_->remove(nt);
                        }
                }else{
                    net_ = n;
                    net_->add(getNode());
                }
            }
            void  Term::setNet       ( const std::string& str){
                std::vector<Net*> n;
                if (isInternal()){
                    n=getInstance()->getCell()->getNets();
                }else{
                    n=getCell()->getNets();
                }
                for(size_t i = 0; i < n.size(); ++i){
                    if(n[i]->getName() == str ) {
                        net_ = n[i]; 
                        break; 
                    }
                }
            }

            void  Term::setPosition  ( const Point& p){node_.setPosition(p);}
            void  Term::setPosition  ( int x, int y ){node_.setPosition(x,y);}
            
            std::string Term::toString(Term::Type t) { 
                if(t == Term::Internal)
                    return "Internal";
                else if(t == Term::External)
                    return "External";
                return "";
            }
    
            std::string Term::toString ( Term::Direction d) { 
                switch(d){
                    case(Term::In): return "In"; break;
                    case(Term::Out): return "Out"; break;
                    case(Term::Inout): return "Inout"; break;
                    case(Term::Tristate): return "Tristate"; break;
                    case(Term::Unknown): return "Unkown"; break;
                    case(Term::Transcv): return "Transcv"; break;
                }
                return "";
            }
            void Term::toXml(std::ostream& o) {
                o << ++indent << "<term name = \"" << getName() << "\" direction=\"" << toString(getDirection()) << "\"/>" << --indent << std::endl;
            }

            Term* Term::fromXml(Cell* c, xmlTextReaderPtr TxtR){
                Term* NewTerm;
                Term::Direction dir;
                int x,y;
                std::string name = xmlCharToString(     xmlTextReaderGetAttribute(   TxtR, (const xmlChar*) "name"     )     );
                std::string dir_str = xmlCharToString   (xmlTextReaderGetAttribute(  TxtR, (const xmlChar*) "direction")     );
                std::string x_str = xmlCharToString(    xmlTextReaderGetAttribute(   TxtR, (const xmlChar*) "x")     );
                std::string y_str = xmlCharToString(    xmlTextReaderGetAttribute(   TxtR, (const xmlChar*) "y")     );

                if(name.empty() or dir_str.empty() or x_str.empty() or y_str.empty()){
                    return NULL;
                }

                if(!dir_str.compare("In")){
                    dir = In;
                }else{
                    if(!dir_str.compare("Out")){
                        dir = Out;
                    }else{
                        if(!dir_str.compare("Inout")){
                            dir = Inout;
                        }else{
                            if(!dir_str.compare("Tristate")){
                                dir = Tristate;
                            }else{
                                if(!dir_str.compare("Transcv")){
                                    dir = Transcv;
                                }else{
                                    return NULL;
                                }
                            }
                        }
                    }
                }   

                NewTerm = new Term(c, name, dir);
                x = atoi(x_str.c_str());
                y = atoi(y_str.c_str());
                NewTerm->setPosition(x,y);
                
                return NewTerm;
            }

}