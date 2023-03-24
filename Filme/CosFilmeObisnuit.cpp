#include "CosFilmeObisnuit.h"


void programCRUDGUI::run() {
    this->filme_inchiriate.addObserver(this);

    this->initComponents();
    this->connectSignals();
    this->update();
    wnd->show();
}


void programCRUDGUI::initComponents() {
    wnd->setLayout(layout);

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    layout->addWidget(table);

    slider->setMinimum(0);
    slider->setMaximum(20);
    slider->setOrientation(Qt::Horizontal);
    slider->setTickPosition(QSlider::TicksAbove);
    layout->addWidget(slider);

    layout->addWidget(btnadd);
    layout->addWidget(btnempty);
}


void programCRUDGUI::connectSignals() {
    QObject::connect(btnadd, &QPushButton::clicked, [this]() {

        int number=slider->value();
        srv.genereaza_cos(number);
        filme_inchiriate.notify();
        });
    QObject::connect(btnempty, &QPushButton::clicked, [this]() {
        filme_inchiriate.sterge_filmele_din_cos();
        filme_inchiriate.notify();
        });
}


void programCRUDGUI::populateTable(QTableWidget* table, vector<Film>& all) {
    this->table->clearContents();
    this->table->setRowCount(static_cast<int>(all.size()));

    int lineNumber = 0;
    for (Film& film:all) {
        this->table->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(film.obtineTitlu())));
        this->table->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(film.obtineGen())));
        this->table->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(film.obtineActor())));
        this->table->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(film.obtineAn())));
        lineNumber++;
    }
}


void programCRUDGUI::update() {
    this->populateTable(table, this->filme_inchiriate.obtine_toate_filmele_din_cos());
}