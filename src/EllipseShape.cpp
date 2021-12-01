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
    void EllipseShape::toXml (std::ostream& stream ) const
    {
    stream << indent << "<ellipse x1=\"" << getBoundingBox().getX1()
                     <<    "\" y1=\"" << getBoundingBox().getY1() 
                     <<    "\" x2=\"" << getBoundingBox().getX2()
                     <<    "\" y2=\"" << getBoundingBox().getY2() << "\"/>" << std::endl;
    }
    EllipseShape* EllipseShape::fromXml (Symbol* owner, xmlTextReaderPtr reader) 
    {
    std::string x1_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x1" ) );
    std::string y1_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y1" ) );
    std::string x2_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x2" ) );
    std::string y2_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y2" ) );

    if(x1_str.empty() or y1_str.empty() or x2_str.empty() or y2_str.empty())
      return NULL;
    
    int x1 = std::stoi(x1_str);
    int y1 = std::stoi(y1_str);
    int x2 = std::stoi(x2_str);
    int y2 = std::stoi(y2_str);

    EllipseShape* Nell = new EllipseShape(owner,x1,y1,x2,y2);

    return Nell;
    }
}