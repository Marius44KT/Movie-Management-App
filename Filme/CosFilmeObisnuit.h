#include "CosFilme.h"
#include "Observer.h"
#include "Service.h"
#include <qwidget.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <qslider.h>
#include <qlayout>
#include <vector>

using std::vector;

class programCRUDGUI : public QWidget, public Observer {
private:
    CosFilme& filme_inchiriate;
    StocareFilme& srv;
    QWidget* wnd;
    QHBoxLayout* layout;
    QTableWidget* table;
    QSlider* slider;
    QPushButton* btnadd;
    QPushButton* btnempty;


    void initComponents();
    void connectSignals();

    void populateTable(QTableWidget* table, vector<Film>& all);

public:
    explicit programCRUDGUI(CosFilme& filme_inchiriate, StocareFilme& srv) :filme_inchiriate{filme_inchiriate}, srv{ srv }{
        wnd=new QWidget;
        layout=new QHBoxLayout;
        btnadd=new QPushButton("Generare de filme random");
        btnempty=new QPushButton("Goleste cosul cu filme");
        slider=new QSlider;
        table=new QTableWidget(0, 4);

    };
    void run();
    void update() override;

    ~programCRUDGUI() {
        this->filme_inchiriate.removeObserver(this);
    }
};
