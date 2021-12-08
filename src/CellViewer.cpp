#include "CellViewer.h"

namespace Netlist{
CellViewer :: CellViewer ( QWidget * parent ): QMainWindow ( parent ), cellWidget_ ( NULL ), saveCellDialog_ ( NULL ){
    cellWidget_ = new CellWidget ( this );
    saveCellDialog_ = new SaveCellDialog ( this );
    setCentralWidget ( cellWidget_ );
    QMenu * fileMenu = menuBar () -> addMenu ( "&File" );
    QAction * action = new QAction ( "&Save As" , this );
    action -> setStatusTip ( "Save to disk (rename) the Cell" );
    action -> setShortcut ( QKeySequence ("CTRL+S") );
    action -> setVisible ( true );
    fileMenu -> addAction ( action );
    connect ( action , SIGNAL ( triggered ()) , this , SLOT ( saveCell ()) );
    action = new QAction ( "&Quit" , this );
    action -> setStatusTip ( "Exit the Netlist Viewer" );
    action -> setShortcut ( QKeySequence ("CTRL+Q") );
    action -> setVisible ( true );
    fileMenu -> addAction ( action );
    connect ( action , SIGNAL ( triggered ()) , this , SLOT ( close ()) );
}

void CellViewer :: saveCell (){
    Cell * cell = getCell ();
    if ( cell == NULL )
        return ;
    QString cellName = cell -> getName (). c_str ();
    if ( saveCellDialog_ -> run ( cellName )) {
        cell -> setName ( cellName . toStdString () );
        cell -> save ( cellName . toStdString () );
    }
}

void CellViewer :: openCell (){
    Cell * cell = getCell ();
    if ( cell == NULL )
        return ;
    QString cellName = cell -> getName (). c_str ();
    if ( openCellDialog_ -> run ( cellName )) {
        cell =Cell::find(cellName.toStdString());
        if (!(cell))
            cell -> load ( cellName . toStdString () );
    }
    setCell(cell);
}

void CellViewer :: setCell (Cell* c){
    cellWidget_ -> setCell(c);
}

Cell* CellViewer :: getCell()const{
    return cellWidget_ -> getCell();
}

}