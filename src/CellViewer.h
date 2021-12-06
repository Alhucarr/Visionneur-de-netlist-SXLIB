#ifndef NETLIST_CELL_VIEWER_H
#define NETLIST_CELL_VIEWER_H

#include "Cell.h"
#include "SaveCellDialog.h"
#include "OpenCellDialog.h"
#include "CellWidget.h"

namespace Netlist {
using namespace std;
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
private :
    CellWidget* cellWidget_ ;
    SaveCellDialog* saveCellDialog_ ;
    OpenCellDialog* openCellDialog_ ;
};
}

#endif