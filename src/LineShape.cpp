#include "Shape.h"

namespace Netlist
{
    LineShape :: LineShape (Symbol* owner, int x1, int y1, int x2, int y2): Shape ( owner ) , x1_ ( x1 ), y1_ ( y1 ), x2_ ( x2 ), y2_ ( y2 ){

    }
    LineShape ::~LineShape (){

    }
    Box BoxShape :: getBoundingBox () const{
        return Box(x1_,y1_,x2_,y2_) ;
    }
}