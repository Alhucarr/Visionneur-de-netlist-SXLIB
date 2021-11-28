#include "Shape.h"

namespace Netlist
{
TermShape :: TermShape ( Symbol * owner , std::string name , int x1 , int y1 ): Shape ( owner ) , term_ ( NULL ), x1_ ( x1 ), y1_ ( y1 ) {
    Cell * cell = getCell ();
    term_ = cell -> getTerm ( name );
}
TermShape ::~ TermShape () {

}
Box TermShape :: getBoundingBox () const{ 
    return Box ( x1_ , y1_ , x1_ , y1_ );
}
}