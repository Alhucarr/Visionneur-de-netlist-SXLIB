// -*- explicit-buffer-name: "Instance.cpp<M1-MOBJ/4-5>" -*-

#include "Instance.h"
#include "Shape.h"

namespace Netlist {
    using namespace std;
            Instance::Instance      ( Cell* owner, Cell* model, const std::string& name):owner_(owner),masterCell_(model),name_(name){
                owner_->add(this);
                std::vector<Term*> Cterms_ = model->getTerms();
                for(unsigned int i = 0; i < Cterms_.size(); ++i){
                    add(new Term(this, Cterms_[i]));
                }
            }
            Instance::~Instance      (){
                for(unsigned int i; i < terms_.size(); i++){
                    delete terms_[i];
                }
            }
            const std::string& Instance::getName       () const{
                return name_;
            }
            Cell* Instance::getMasterCell () const{
                return masterCell_;
            }
            Cell* Instance::getCell() const{
                return owner_;
            }
            const std::vector<Term*>& Instance::getTerms      () const{
                return terms_;
            }
            Term* Instance::getTerm       ( const std::string& name) const{
                for(size_t i = 0; i < terms_.size(); ++i){
					if(terms_[i]->getName() == name) return terms_[i];
				}
				return NULL;
            }
            Point Instance::getPosition   () const{
                return position_;
            }
            bool Instance::connect(const std::string& name, Net* n) {
                Term* t = getTerm(name);
                if(t != NULL){
                    t->setNet(n);
                    return true;
                }
                return false;
            }
    
            void Instance::add(Term* t) {
                terms_.push_back(t);
            }
    
            void Instance::remove(Term* t) {
                for(size_t i = 0; i < terms_.size(); i++){
                    if(terms_[i] == t)
                        terms_.erase(terms_.begin()+i);
                }
            }   
    
            void Instance::setPosition(const Point& p) {
                position_ = Point(p);
            }

            void Instance::setPosition(int x, int y) {
                position_ = Point(x, y);
            }
            void Instance::toXml(std::ostream& o) {
                o << ++indent << "<instance name = \"" << getName() << "\" mastercell=\"" << masterCell_->getName() << "\" x=\"" << position_.Point::getX() << "\" y=\"" << position_.Point::getY() << "\"/>" << --indent << std::endl;
            }
            
            Instance* Instance :: fromXml(Cell* cell, xmlTextReaderPtr TxtR){
                    string name =    xmlCharToString(xmlTextReaderGetAttribute(TxtR,(const xmlChar*) "name"));
                    string mastercell = xmlCharToString(xmlTextReaderGetAttribute(TxtR,(const xmlChar*) "mastercell"));
                    string x_str =   xmlCharToString(xmlTextReaderGetAttribute(TxtR,(const xmlChar*) "x"));
                    string y_str =   xmlCharToString(xmlTextReaderGetAttribute(TxtR,(const xmlChar*) "y"));

                    if(name.empty() || mastercell.empty() || x_str.empty() || y_str.empty()) return NULL;

                    Instance* i = new Instance(cell,Cell::find(mastercell),name);

                    int x = atoi(x_str.c_str());
                    int y = atoi(y_str.c_str());

                    i->setPosition(x,y);
                    return i;
            }
}