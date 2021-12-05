# include < QMainWindow >
class CellViewer : 
public QMainWindow {
    Q_OBJECT ;
public :
    CellViewer ( QWidget * parent = NULL );
    virtual ~ CellViewer ();
    void setCell ( Cell * );
    Cell * getCell () const ;
public slots :
    void saveCell ();
private :
    CellWidget * cellWidget_ ;
    SaveCellDialog * saveCellDialog_ ;
};