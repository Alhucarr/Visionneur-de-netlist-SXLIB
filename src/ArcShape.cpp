#include "Shape.h"

namespace Netlist
{
    ArcShape::ArcShape (Symbol* owner, int start_, int span_, const Box& box): Shape(owner),start_(start_),span_(span_), box_(box){

    }
    ArcShape::ArcShape (Symbol * owner, int start_, int span_, int x1, int y1, int x2, int y2): Shape(owner), start_(start_), span_(span_), box_(x1,y1,x2,y2){

    }
    ArcShape::~ArcShape (){

    }
    Box ArcShape::getBoundingBox () const{
        return box_;
    }
}