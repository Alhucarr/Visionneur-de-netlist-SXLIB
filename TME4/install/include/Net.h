// -*- explicit-buffer-name: "Net.h<M1-MOBJ/4-5>" -*-

#ifndef _NET_H
#define NETLIST_NET_H

#include <string>
#include <vector>
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
        public :
            Net     ( Cell*, const std::string&, Term::Type );
            ~Net     ();
            Cell*                     getCell       () const;
            const std::string&        getName       () const;
            unsigned int              getId         () const;
            Term::Type                getType       () const;
            const std::vector<Node*>& getNodes      () const;
            size_t                    getFreeNodeId () const;
            void  add    ( Node* );
            bool  remove ( Node* );
            void  toXml(std::ostream& stream);
            static Net* fromXml(Cell*, xmlTextReaderPtr);
    };
}


#endif