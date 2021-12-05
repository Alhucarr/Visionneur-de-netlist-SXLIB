#include "CellViewer.h"

CellViewer :: CellViewer ( QWidget * parent ): QMainWindow ( parent ), cellWidget_ ( NULL ), saveCellDialog_ ( NULL ){
    cellWidget_ = new CellWidget ();
    saveCellDialog_ = new SaveCellDialog ( this );
    setCentralWidget ( cellWidget_ );
    QMenu * fileMenu = menuBar () - > addMenu ( " & File " );
    QAction * action = new QAction ( " & Save ␣ As " , this );
    action -> setStatusTip ( " Save ␣ to ␣ disk ␣ ( rename ) ␣ the ␣ Cell " );
    action -> setShortcut ( QKeySequence (" CTRL +S") );
    action -> setVisible ( true );
    fileMenu -> addAction ( action );
    connect ( action , SIGNAL ( triggered ()) , this , SLOT ( saveCell ()) );
    action = new QAction ( "& Quit " , this );
    action -> setStatusTip ( " Exit ␣ the ␣ Netlist ␣ Viewer " );
    action -> setShortcut ( QKeySequence (" CTRL +Q") );
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
        cell - > setName ( cellName . toStdString () );
        cell - > save ( cellName . toStdString () );
    }
}