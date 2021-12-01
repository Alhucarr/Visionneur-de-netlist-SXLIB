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
    void  ArcShape::toXml (std::ostream& stream ) const
    {
    stream << indent << "<arc x1=\"" << getBoundingBox().getX1()
                     <<    "\" y1=\"" << getBoundingBox().getY1() 
                     <<    "\" x2=\"" << getBoundingBox().getX2()
                     <<    "\" y2=\"" << getBoundingBox().getY2()
                     <<    "\" start=\"" << getStart() 
                     <<    "\" span=\"" << getSpan() << "\"/>" << std::endl;
    }
    ArcShape* ArcShape::fromXml (Symbol* owner, xmlTextReaderPtr reader) 
    {
    std::string x1_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x1" ) );
    std::string y1_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y1" ) );
    std::string x2_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x2" ) );
    std::string y2_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y2" ) );
    std::string start_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"start"));
    std::string span_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"span"));

    if(x1_str.empty() or y1_str.empty() or x2_str.empty() or y2_str.empty() or start_str.empty() or span_str.empty())
      return NULL;
    
    int x1 = std::stoi(x1_str);
    int y1 = std::stoi(y1_str);
    int x2 = std::stoi(x2_str);
    int y2 = std::stoi(y2_str);
    int start = std::stoi(start_str);
    int span = std::stoi(span_str);

    ArcShape* Narc = new ArcShape(owner,start,span,x1,y1,x2,y2);

    return Narc;
    }
}