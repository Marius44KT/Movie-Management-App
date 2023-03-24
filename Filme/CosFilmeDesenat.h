#include "Observer.h"
#include "service.h"
#include "CosFilme.h"
#include <qwidget.h>
#include <qpainter.h>
#include <random>
#include <cmath>

#define RECTANGLE_MAX_DIM 256

class programReadOnlyGUI : public QWidget, public Observer {
private:
    CosFilme& filme_inchiriate;

public:
    programReadOnlyGUI(CosFilme& filme_inchiriate);

    void update() override;

    void paintEvent(QPaintEvent* event) override;

    ~programReadOnlyGUI() {
        this->filme_inchiriate.removeObserver(this);
    }
};
