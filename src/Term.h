// -*- explicit-buffer-name: "Term.h<M1-MOBJ/4-5>" -*-

#ifndef NETLIST_TERM_H
#define NETLIST_TERM_H
#include  <libxml/xmlreader.h>
#include <string>
#include <vector>
#include "Cell.h"
#include "Point.h"
#include "Node.h"
#include "Instance.h"
#include "XmlUtil.h"

namespace Netlist {
class Net;
class Term{
        public :
            enum Type      { Internal=1, External=2 };
            enum Direction { In=1, Out=2, Inout=3, Tristate=4, Transcv=5, Unknown=6 };
        private :
            void*         owner_;
            std::string   name_;
            Direction     direction_;
            Type          type_;
            Net*          net_;
            NodeTerm      node_;
        public :
            Term ( Cell*    , const std::string name, Direction );
            Term ( Instance*, const Term* modelTerm );
            ~Term ();
            inline bool               isInternal   () const{if(type_ == Internal)return true;return false;};
            inline bool               isExternal   () const{if(type_ == External)return true;return false;};
            inline const std::string& getName      () const{return name_;}
            inline NodeTerm*          getNode      ()      {return &node_;}
            inline Net*               getNet       () const{return net_;}
            inline Cell*              getCell      () const{return ( type_ == External ) ? static_cast < Cell * >( owner_ ) : NULL ; }
                   Cell*              getOwnerCell () const;
            inline Instance*          getInstance  () const{return ( type_ == Internal ) ? static_cast < Instance * >( owner_ ): NULL ; }
            inline Direction          getDirection () const{return direction_;}
            inline Point              getPosition  () const{return node_.getPosition();}
            inline Type               getType      () const{return type_;}
            void  setNet       ( Net* n);
            void  setNet       ( const std::string& );
            inline void  setDirection ( Direction d){direction_=d;}
            void  setPosition  ( const Point& );
            void  setPosition  ( int x, int y );
            static std::string toString(Term::Type t);
            static std::string toString(Term::Direction d);
            void toXml(std::ostream& o);
            static Term* fromXml(Cell*, xmlTextReaderPtr);
    };
}


#endif