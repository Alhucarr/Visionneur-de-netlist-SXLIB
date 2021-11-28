#include "Term.h"
#include "Shape.h"
#include "Symbol.h"

namespace Netlist
{
  Symbol::Symbol(Cell* cell):owner_(cell){}
  Symbol::~Symbol(){}

  Cell* Symbol::getCell () const {return owner_;}
  Box Symbol::getBoundingBox () const
  {
    Box b = Box();
    for(size_t i = 0; i < shapes_.size(); ++i)
    {
      b = b.merge(shapes_[i]->getBoundingBox());
    }
    return b;
  }
  Point Symbol::getTermPosition (Term* t) const
  {
    TermShape* ts = getTermShape(t);
    if(ts)
      return Point(ts->getX(), ts->getY());
    return Point();
  }
  TermShape* Symbol::getTermShape (Term* t) const
  {
    TermShape* ts = NULL;
    for(size_t i = 0; i < shapes_.size(); ++i)
    {
      ts = dynamic_cast<TermShape*>(shapes_[i]);
      if(ts != NULL && ts->getTerm() == t)
	return ts;
    }
    return NULL;
  }
  

  void Symbol::add (Shape* s)
  {
    shapes_.push_back(s);
  }
  void Symbol::remove (Shape* s)
  {
    for(size_t i = 0; i < shapes_.size(); ++i)
    {
      if(shapes_[i] == s)
      {
	shapes_.erase(shapes_.begin() + i);
	break;
      }
    }
  }
}