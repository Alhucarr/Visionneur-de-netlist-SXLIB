#include "Shape.h"

namespace Netlist
{
    EllipseShape::EllipseShape (Symbol * owner, const Box & box): Shape(owner), box_(box){

    }
    EllipseShape::EllipseShape (Symbol * owner, int x1, int y1, int x2, int y2): Shape(owner), box_(x1,y1,x2,y2){

    }
    EllipseShape::~EllipseShape (){

    }
    Box EllipseShape::getBoundingBox () const{
        return box_;
    }
}