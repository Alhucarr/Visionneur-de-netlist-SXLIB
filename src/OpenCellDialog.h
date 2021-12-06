#ifndef NETLIST_OPEN_CELL_DIALOG_H
#define NETLIST_OPEN_CELL_DIALOG_H

#include "CellWidget.h"

namespace Netlist {
using namespace std;
class OpenCellDialog : 
public QDialog {
    Q_OBJECT ;
public :
    OpenCellDialog ( QWidget * parent = NULL );
    static bool run ( QString & name );
    const QString getCellName () const ;
    void setCellName ( const QString & );
protected :
    QLineEdit * lineEdit_ ;
};
}

#endif