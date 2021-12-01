#include "Shape.h"

namespace Netlist
{
TermShape :: TermShape ( Symbol * owner , std::string name , int x1 , int y1, NameAlign na ): Shape ( owner ) , term_ ( NULL ), x1_ ( x1 ), y1_ ( y1 ),align_(na) {
    Cell * cell = getCell ();
    term_ = cell -> getTerm ( name );
}

TermShape ::~ TermShape () {

}

Box TermShape :: getBoundingBox () const{ 
    return Box ( x1_ , y1_ , x1_ , y1_ );
}

void  TermShape::toXml (std::ostream& stream ) const
{
    stream << indent << "<term name=\"" << getTerm()
                     <<    "\" x1=\"" << getX()
                     <<    "\" y1=\"" << getY()
                     << "\" align=\"" << Aligntostr(align_) << "\"/>" << std::endl;
}

Shape* TermShape::fromXml (Symbol* owner, xmlTextReaderPtr reader) 
    {
    std::string name = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
    std::string x_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x1" ) );
    std::string y_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y1" ) );
    std::string align_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"align" ) );

    if(name.empty() || align_str.empty() ||
       x_str.empty() || y_str.empty())
      return NULL;

    NameAlign align = Strtoalign( align_str );
    
    int x = atoi(x_str.c_str());
    int y = atoi(y_str.c_str());

    Shape* Ntshape = new TermShape(owner, name, x, y, align);

    return Ntshape;
    }


std::string TermShape::Aligntostr(NameAlign na)const{
    switch(na){
        case TopLeft:
            return "top_left";
        case TopRight:
            return "top_right";
        case BottomLeft:
            return "bottom_left";
        case BottomRight:
            return "bottom_right";
        case Unknown:
            return "Unknown";
    }
    return "Unknown";
}

TermShape::NameAlign TermShape::Strtoalign(std::string str){
    if(!str.compare("top_left"))
        return TopLeft;
    if(!str.compare("top_right"))
        return TopRight;
    if(!str.compare("bottom_left"))
        return BottomLeft;
    if(!str.compare("bottom_right"))
        return BottomRight;

    return Unknown;
}

}
