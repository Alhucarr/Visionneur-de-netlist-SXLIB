#ifndef NETLIST_CELL_VIEWER_H
#define NETLIST_CELL_VIEWER_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTableView>
#include <QMenuBar>
#include <QAction>
#include "Cell.h"
#include "SaveCellDialog.h"
#include "OpenCellDialog.h"
#include "CellWidget.h"

namespace Netlist {
using namespace std;
class InstancesWidget;
class CellsLib;

class CellViewer : 
public QMainWindow {
    Q_OBJECT ;
public :
    CellViewer ( QWidget * parent = NULL );
    virtual ~ CellViewer (){}
    void setCell ( Cell * );
    Cell * getCell () const ;

public slots :
    void saveCell ();
    void openCell ();
    void showCellsLib();
    void showInstanceWidget();

signals:
    void cellLoaded();

private :
    CellWidget* cellWidget_ ;
    SaveCellDialog* saveCellDialog_ ;
    InstancesWidget* instancesWidget_;
    CellsLib* cellsLib_;
};
}

#endif