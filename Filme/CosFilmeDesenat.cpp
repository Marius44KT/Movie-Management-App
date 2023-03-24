#include "CosFilmeDesenat.h"
programReadOnlyGUI::programReadOnlyGUI(CosFilme& filme_inchiriate) : filme_inchiriate{filme_inchiriate} {
    this->filme_inchiriate.addObserver(this);
    this->repaint();
}

void programReadOnlyGUI::paintEvent(QPaintEvent* event) {
    QPainter g{this};
    g.setPen(Qt::blue);


    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> x_coord(0, this->width());
    std::uniform_int_distribution<> y_coord(0, this->height());
    std::uniform_int_distribution<> width(15, RECTANGLE_MAX_DIM);
    std::uniform_int_distribution<> height(15, RECTANGLE_MAX_DIM);

    for (const auto& prod : this->filme_inchiriate.obtine_toate_filmele_din_cos()) {
        g.drawEllipse(x_coord(mt), y_coord(mt), width(mt), height(mt));

    }
}

void programReadOnlyGUI::update() {
    this->repaint();
}