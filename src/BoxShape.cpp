#include "Shape.h"

namespace Netlist
{
    BoxShape :: BoxShape ( Symbol * owner , const Box & box ): Shape ( owner ) , box_ ( box ){

    }
    BoxShape ::~ BoxShape (){

    }
    Box BoxShape :: getBoundingBox () const{
        return box_ ;
    }
}