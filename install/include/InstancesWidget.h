// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_INSTANCES_WIDGET_H
#define NETLIST_INSTANCES_WIDGET_H

#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include "Cell.h"
#include "InstancesModel.h"
#include "CellViewer.h"
class QPainter;
#include "Box.h"

namespace Netlist {

class CellViewer;
class Cell;
class InstancesModel;

class InstancesWidget : public QWidget {
    Q_OBJECT ;
  public :
                      InstancesWidget ( QWidget * parent = NULL );
                 void setCellViewer ( CellViewer * );
                  int getSelectedRow () const ;
          inline void setCell ( Cell * );
  public slots :
                 void load ();
  private :
      CellViewer * cellViewer_ ;
      InstancesModel * baseModel_ ;
      QTableView * view_ ;
      QPushButton * load_ ;
};
}  // Netlist namespace.

#endif