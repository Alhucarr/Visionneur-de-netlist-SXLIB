#ifndef NETLIST_SHAPE_H
#define NETLIST_SHAPE_H

#include "string.h"
#include "Symbol.h"
#include "Box.h"
#include "Term.h"

namespace Netlist {

  class BoxShape;
  class LineShape;
  
  class Shape {
  public :
    Shape ( Symbol * );
    virtual ~Shape ();
    inline Symbol * getSymbol () const{ return owner_ ; };
    inline Cell* getCell() const{return owner_->getCell();};
    virtual Box getBoundingBox () const = 0;
    virtual void  toXml   (std::ostream&) const =0;
    static Shape* fromXml (Symbol*, xmlTextReaderPtr);
  private :
    Symbol * owner_ ;
  };

  class BoxShape : public Shape {
  public :
    BoxShape ( Symbol *, const Box & );
    BoxShape ( Symbol *, int x1 , int y1 , int x2 , int y2 );
    ~BoxShape ();
    Box getBoundingBox () const ;
    void  toXml   (std::ostream&) const;
    static BoxShape* fromXml (Symbol* owner, xmlTextReaderPtr reader);
  private :
    Box box_ ;
  };

  class LineShape : public Shape{
  public:
    LineShape (Symbol*, int x1, int y1, int x2, int y2);
    ~LineShape ();
    Box getBoundingBox () const;
    void  toXml   (std::ostream&) const;
    static LineShape* fromXml (Symbol* owner, xmlTextReaderPtr reader);
    inline Point getPointdeb(){return Point(x1_,y1_);}
    inline Point getPointfin(){return Point(x2_,y2_);}
  private:
    int x1_, y1_, x2_, y2_;
  };

class TermShape : public Shape {
public :
  enum NameAlign {TopLeft = 1, TopRight, BottomLeft, BottomRight,Unknown};
private :
  Term * term_ ;
  int x1_ , y1_ ;
  NameAlign align_;
public :
  TermShape ( Symbol *, std::string name , int x , int y,NameAlign na);
  ~ TermShape ();
  Box getBoundingBox () const ;

  void  toXml   (std::ostream&) const;
  static Shape* fromXml (Symbol*, xmlTextReaderPtr);

  std::string Aligntostr(NameAlign na) const;
  static NameAlign Strtoalign(std::string str);

  inline Term * getTerm () const{return term_;}
  inline int getX () const{return x1_;}
  inline int getY () const{return y1_;}
  inline NameAlign getNameAlign(){return align_;}
};

class EllipseShape : public Shape
  {    
  public:
    EllipseShape (Symbol*, const Box&);
    EllipseShape (Symbol*, int x1, int y1, int x2, int y2);
    ~EllipseShape ();
    Box getBoundingBox () const;
    
    void  toXml   (std::ostream&) const;
    static EllipseShape* fromXml (Symbol* owner, xmlTextReaderPtr reader);
    
  private:
    Box box_;
  };

  class ArcShape : public Shape
  {    
  private:
    int start_, span_;
    Box box_;
  public:
    ArcShape (Symbol*, int start_, int span_, const Box&);
    ArcShape (Symbol*, int start_, int span_, int x1, int y1, int x2, int y2);
    ~ArcShape ();
    Box getBoundingBox () const;

    inline int getStart()const;
    inline int getSpan()const;
    void  toXml   (std::ostream&) const;
    static ArcShape* fromXml (Symbol* owner, xmlTextReaderPtr reader);

  };

  inline int ArcShape::getStart()const{return start_;}
  inline int ArcShape::getSpan()const{return span_;}

  }
  #endif