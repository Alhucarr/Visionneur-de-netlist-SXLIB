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
    virtual Box getBoundingBox () const = 0;
    void  toXml   (std::ostream&) const;
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
    static BoxShape* fromXml (Symbol*, xmlTextReaderPtr);
  private :
    Box box_ ;
  };

  class LineShape : public Shape{
  public:
    LineShape (Symbol*, int x1, int y1, int x2, int y2);
    ~LineShape ();
    Box getBoundingBox () const;
    //void  toXml   (std::ostream&) const;
    //static LineShape* fromXml (Symbol*, xmlTextReaderPtr);
  private:
    int x1_, y1_, x2_, y2_;
  };

class TermShape : public Shape {
public :
  TermShape ( Symbol *, std::string name , int x , int y );
  ~ TermShape ();
  Box getBoundingBox () const ;
  void  toXml   (std::ostream&) const;
  static Shape* fromXml (Symbol*, xmlTextReaderPtr);
  inline Term * getTerm () const{return term_;};
  inline Cell*  getCell () const{return term_->getCell();}
  inline int getX () const{return x1_;};
  inline int getY () const{return y1_;}
private :
  Term * term_ ;
  int x1_ , y1_ ;
};

class EllipseShape : public Shape
  {    
  public:
    EllipseShape (Symbol*, const Box&);
    EllipseShape (Symbol*, int x1, int y1, int x2, int y2);
    ~EllipseShape ();
    Box getBoundingBox () const;
    
    void  toXml   (std::ostream&) const;
    static EllipseShape* fromXml (Symbol*, xmlTextReaderPtr);
    
  private:
    Box box_;
  };

  class ArcShape : public Shape
  {    
  public:
    ArcShape (Symbol*, int start_, int span_, const Box&);
    ArcShape (Symbol*, int start_, int span_, int x1, int y1, int x2, int y2);
    ~ArcShape ();
    Box getBoundingBox () const;

    inline int getStart();
    inline int getSpan();
    void  toXml   (std::ostream&) const;
    static ArcShape* fromXml (Symbol*, xmlTextReaderPtr);
    
  private:
    Box box_;
    int start_, span_;
  };

  inline int ArcShape::getStart(){return start_;}
  inline int ArcShape::getSpan(){return span_;}

  }
  #endif