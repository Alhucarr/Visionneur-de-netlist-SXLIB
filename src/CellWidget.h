// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_CELL_WIDGET_H
#define NETLIST_CELL_WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QMainWindow>
#include <QDialog>
#include <QPainter>
#include <QRect>
#include <QPoint>
#include <QMenuBar>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class QPainter;
#include "Box.h"


namespace Netlist {

  class Cell;
  class NodeTerm;


  class CellWidget : public QWidget {
      Q_OBJECT;
    public:
                      CellWidget         ( QWidget* parent=NULL );
      virtual        ~CellWidget         ();
              void    setCell            ( Cell* );
      inline  Cell*   getCell            () const;
      virtual QSize   minimumSizeHint    () const;
      virtual void    resizeEvent        ( QResizeEvent* );
    protected:
      virtual void    paintEvent         ( QPaintEvent* );
    private:
      Cell* cell_;
  };


  inline Cell* CellWidget::getCell () const { return cell_; }


}  // Netlist namespace.

#endif  // NETLIST_CELL_WIDGET_H