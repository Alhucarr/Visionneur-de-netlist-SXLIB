// -*- explicit-buffer-name: "Net.h<M1-MOBJ/4-5>" -*-

#ifndef _NET_H
#define NETLIST_NET_H

#include <string>
#include <vector>
#include "Term.h"
#include "Line.h"
#include "XmlUtil.h"
#include "Cell.h"
#include "Node.h"

namespace Netlist {
    class Term;
    class Net{
        private :
            Cell*               owner_;
            std::string         name_;
            unsigned int        id_;
            Term::Type          type_;
            std::vector<Node*>  nodes_;
            std::vector<Line*>       lines_;
        public :
            Net     ( Cell*, const std::string&, Term::Type );
            ~Net     ();
            Cell*                     getCell       () const;
            const std::string&        getName       () const;
            unsigned int              getId         () const;
            Term::Type                getType       () const;
            Node*                     getNode (size_t) const;
            const std::vector<Node*>& getNodes      () const;
            size_t                    getFreeNodeId () const;
     inline const std::vector<Line*>& getLines () const{ return lines_; }
            void  add    ( Node* );
            void  add    ( Line* );
            bool  remove ( Node* );
            bool  remove ( Line* line );
            void  toXml(std::ostream& stream);
            static Net* fromXml(Cell*, xmlTextReaderPtr);
    };
}


#endif