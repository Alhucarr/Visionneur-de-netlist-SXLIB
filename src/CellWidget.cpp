// -*- explicit-buffer-name: "CellWidget.cpp<M1-MOBJ/8-10>" -*-

#include  "CellWidget.h"



namespace Netlist {

  using namespace std;


  ostream& operator<< ( ostream& o, const QRect& rect ){
    o << "<QRect x:" << rect.x()
      <<       " y:" << rect.y()
      <<       " w:" << rect.width()
      <<       " h:" << rect.height() << ">";
    return o;
  }


  ostream& operator<< ( ostream& o, const QPoint& p ){ 
    o << "<QRect x:" << p.x() << " y:" << p.y() << ">"; return o; 
  }



  CellWidget::CellWidget ( QWidget* parent ):QWidget(parent),cell_  (NULL),viewport(new Box(0,0,500,500)){
    setAttribute    ( Qt::WA_OpaquePaintEvent );
    setAttribute    ( Qt::WA_NoSystemBackground );
    //setAttribute    ( Qt::WA_StaticContents );
    setSizePolicy   ( QSizePolicy::Expanding, QSizePolicy::Expanding );
    setFocusPolicy  ( Qt::StrongFocus );
    setMouseTracking( true );
  }


  CellWidget::~CellWidget (){}


  void  CellWidget::setCell ( Cell* cell ){
    cell_ = cell;
    repaint();
  }


  QSize  CellWidget::minimumSizeHint () const{ 
    return QSize(500,500); 
  }


  void  CellWidget::paintEvent ( QPaintEvent* event ){
    QPainter painter(this);
    painter.setBackground( QBrush( Qt::black ) );
    painter.eraseRect    ( QRect( QPoint(0,0), size() ) );

    if (cell_) query(painter);
  }

  void CellWidget::query(QPainter& painter){
    //Nets
    painter.setPen(QPen(Qt::cyan, 1));
    painter.setBrush(QBrush(Qt::cyan));
    const std::vector<Net*>& nets = cell_->getNets();
    for(size_t i = 0; i < nets.size(); ++i){
      const std::vector<Line*>& lines = nets[i]->getLines();
      for(size_t j = 0; j < lines.size(); ++j){
        Point pa = lines[j]->getSource()->getPosition();
        pa.translate(0, -viewport->getY2());
        Point pb = lines[j]->getTarget()->getPosition();
        pb.translate(0, -viewport->getY2());
        QPoint p_a = pointToScreenPoint(pa);
        QPoint p_b = pointToScreenPoint(pb);
        painter.drawLine(p_a, p_b);
        if(lines[j]->getSource()->getDegree() > 2){
          QRect rect(p_a.x()-5, p_a.y()-5, 10, 10); 
          painter.drawEllipse(rect);
        }
      }
    }
    painter.setBrush(QBrush(Qt::black));
    painter.setPen(QPen(Qt::darkGreen, 3));
    const vector<Instance*>& instances = cell_->getInstances();
    for (size_t i = 0; i < instances.size(); ++i){
      cout << "Instance Name : " << instances[i]->getName() << endl;
      Point instPos = instances[i]->getPosition();
      instPos.translate(0, -viewport->getY2());
      
      const Symbol* symbol = instances[i]->getMasterCell()->getSymbol();
      if(!symbol){
        continue;
      }
      const vector <Shape*>& shapes = symbol->getShapes ();
      for (size_t j = 0; j < shapes.size(); ++j){
        cout << "   Shape Name : ";
        shapes[i]->toXml(cout);
        BoxShape* boxShape = dynamic_cast<BoxShape*>(shapes[j]);
        if (boxShape){
          Box box = boxShape->getBoundingBox ();
          QRect rect = boxToScreenRect(box.translate(instPos));
          painter.drawRect(rect);
          continue;
        }
        
        LineShape* lineShape = dynamic_cast<LineShape*>(shapes[j]);
        if (lineShape){
          Point pd = lineShape->getPointdeb();
          Point pf = lineShape->getPointfin();
          
          QPoint p_a = pointToScreenPoint(pd.translate(instPos));
          QPoint p_b = pointToScreenPoint(pf.translate(instPos));
          painter.drawLine(p_a, p_b);
          continue;
        }

        EllipseShape* ellipseShape = dynamic_cast<EllipseShape*>(shapes[j]);
        if (ellipseShape){
          Box box = ellipseShape->getBoundingBox ();
          QRect rect = boxToScreenRect(box.translate(instPos));
          painter.drawEllipse(rect);
          continue;
        }

        ArcShape* arcShape = dynamic_cast<ArcShape*>(shapes[j]);
        if (arcShape){
          Box box = arcShape->getBoundingBox ();
          QRect rect = boxToScreenRect(box.translate(instPos));
          painter.drawArc(rect, arcShape->getStart()*16, arcShape->getSpan()*16);
          continue;
        }
      }
      QRect r = boxToScreenRect(symbol->getBoundingBox().translate(instPos));
      QRect label = QRect(r.center().x(), r.center().y()+(r.height()/2), 50, 30);
      painter.drawText(label, Qt::AlignTop, instances[i]->getName().c_str());
    }
    painter.setPen(QPen(Qt::red, 1));
    painter.setBrush(QBrush(Qt::red));
    const vector<Term*>& terms = cell_->getTerms();
    for(size_t i = 0; i < terms.size(); ++i){
      Point p = terms[i]->getPosition();
      p.translate(0, -viewport->getY2());
      QPoint qp = pointToScreenPoint(p);
      int height = 6;
      int width = 6;
      
      painter.drawRect(qp.x(), qp.y()-height/2, height, width);
      QRect rect = QRect(qp.x(), qp.y(), 40, 20);
      switch(terms[i]->getDirection()){
      case Term::Internal:
        painter.drawText(rect, Qt::AlignLeft|Qt::AlignBottom, terms[i]->getName().c_str());
        break;
      case Term::External:
        painter.drawText(rect, Qt::AlignRight|Qt::AlignBottom, terms[i]->getName().c_str());
        break;
      default:
        std::cerr << "[ERROR] CellWidget::query: Unexpected Direction." << std::endl;
        break;
      }
    }
    for (size_t i = 0; i < instances.size(); ++i)
    {
      Point instPos = instances[i]->getPosition();
      instPos.translate(0, -viewport->getY2());
      const Symbol* symbol = instances[i]->getMasterCell()->getSymbol();
      if(!symbol)
	      continue;
      const vector <Shape*>& shapes = symbol->getShapes ();
      for (size_t j = 0; j < shapes.size(); ++j)
      {
        TermShape* termShape = dynamic_cast<TermShape*>(shapes[j]);
        if (termShape){
          Point p(termShape->getX(), termShape->getY());
          QPoint qp = pointToScreenPoint(p.translate(instPos));
          int height = 6;
          int width = 6;
          painter.setBrush(QBrush(Qt::red));
          painter.setPen(QPen(Qt::red, 1));
          painter.drawRect(qp.x(), qp.y()-(height/2), height, width);	  
          QRect rect = QRect(qp.x(), qp.y(), 20, 20);
          switch(termShape->getNameAlign())
          {
          case TermShape::TopLeft:
            painter.drawText(rect, Qt::AlignLeft|Qt::AlignTop, termShape->getTerm()->getName().c_str());
            break;
          case TermShape::TopRight:
            painter.drawText(rect, Qt::AlignRight|Qt::AlignTop, termShape->getTerm()->getName().c_str());
            break;
          case TermShape::BottomLeft:
            painter.drawText(rect, Qt::AlignLeft|Qt::AlignBottom, termShape->getTerm()->getName().c_str());
            break;
          case TermShape::BottomRight:
            painter.drawText(rect, Qt::AlignRight|Qt::AlignBottom, termShape->getTerm()->getName().c_str());
            break;
          default:
            std::cerr << "[ERROR] CellWidget::query: Unexpected Align." << std::endl;
            break;
          }
	      }
      }
    }
    painter.setBrush(QBrush(Qt::black));
  }

  void CellWidget::keyPressEvent(QKeyEvent* event){
    event->ignore();
    if(event->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier))
      return;

    switch(event->key()){
    case Qt::Key_Up: goUp();
      break;
    case Qt::Key_Down: goDown();
      break;
    case Qt::Key_Left: goLeft();
      break;
    case Qt::Key_Right: goRight();
      break;
    default:
      return;
    }
    event->accept();
  }

  void CellWidget::goLeft(){
    viewport->translate(-20,0);
    repaint();
  }
  void CellWidget::goRight(){
    viewport->translate(20,0);
    repaint();
  }
  void CellWidget::goUp(){
    viewport->translate(0,20);
    repaint();
  }
  void CellWidget::goDown(){
    viewport->translate(0,-20);
    repaint();
  }

}

