#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QListWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <qmainwindow.h>
#include "Service.h"
#include "MyTableModel.h"

using std::vector;
using std::string;
class StocareFilmeGUI:public QWidget {
private:
	StocareFilme& service;
	vector <string> genuri;
	//lista de filme
	QLabel* lblTitlu=new QLabel{"Titlul filmului: "};
	QLabel* lblGen=new QLabel{"Genul filmului: "};
	QLabel* lblActor=new QLabel{"Actorul principal: "};
	QLabel* lblAn=new QLabel{"Anul de aparitie: "};

	QLineEdit* editTitlu;
	QLineEdit* editGen;
	QLineEdit* editActor;
	QLineEdit* editAn;


	//butoane pe functionalitatile de baza
	QPushButton* buton_informatii;
	QPushButton* buton_cauta;
	QPushButton* buton_adauga;
	QPushButton* buton_actualizeaza;
	QPushButton* buton_sterge;
	QPushButton* buton_undo;
	QPushButton* buton_filme2022;
	QPushButton* buton_filtrare_titlu;
	QPushButton* buton_filtrare_an;
	QTableWidget* listaFilme;
	QTableWidget* cosFilme;
	QWidget* btnDyn=new QWidget;
	QLayout* lyBtnDy;
	vector<QPushButton*> butoane_genuri_filme;


	//groupBox pentru cele trei tipuri de sortare
	QGroupBox* groupBoxSortare=new QGroupBox(tr("Tip sortare"));
	QRadioButton* radio_sortare_titlu=new QRadioButton(QString::fromStdString("Titlu"));
	QRadioButton* radio_sortare_actor=new QRadioButton(QString::fromStdString("Actor principal"));
	QRadioButton* radio_sortare_an_gen=new QRadioButton(QString::fromStdString("Anul aparitiei+Gen"));
	QPushButton* butonSortare;


	//cosul cu filme
	QLabel* lblTitluCos=new QLabel{"Titlul filmului: "};
	QLabel* lblAnCos=new QLabel{"Anul de aparitie: "};
	QLabel* lblNumarCos=new QLabel{"Numarul de filme de adaugat: "};
	QLabel* lblFisierCos=new QLabel{"Numele fisierului pentru export:"};
	QLineEdit* editTitluCos;
	QLineEdit* editAnCos;
	QLineEdit* editNumarCos;
	QLineEdit* editFisierCos;

	QPushButton* buton_adaugaCos;
	QPushButton* buton_adauga_multipluCos;
	QPushButton* buton_sterge_totCos;
	QPushButton* buton_exportCSV;
	QPushButton* buton_cos_obisnuit;
	QPushButton* buton_cos_desenat;


	//Model, QTableView
	MyTableModel* model;
	QTableView* tabelView=new QTableView;
	

	void initializare_componente_GUI();
	void conectare_butoane();
	void reincarca_lista(vector <Film> filme);
	void reincarca_cosul(vector <Film> cos_filme);
public:
	StocareFilmeGUI(StocareFilme& serviceFilme): service{serviceFilme}
	{
		initializare_componente_GUI();
		conectare_butoane();
		//reincarca_lista(service.obtine_toate_filmele());
		model=new MyTableModel{serviceFilme.obtine_toate_filmele()};
		tabelView->setModel(model);
		reincarca_cosul(service.obtine_toate_filmele_din_cos());
	}

	//functionalitati pe lista de filme
	void GUI_birou_informatii();
	void GUI_cauta_film();
	void GUI_adauga_film();
	void GUI_actualizeaza_film();
	void GUI_sterge_film();
	void GUI_undo();
	void GUI_filme2022();
	void GUI_filtreaza_titlu();
	void GUI_filtreaza_an();
	void adaugaButoane(const std::vector<Film>& filme);
	void optiune();

	//functionalitati pe cosul cu filme
	void GUI_adauga_film_cos();
	void GUI_adauga_numar_filme_cos();
	void GUI_exportCSV();
	void GUI_golire_cos();
};
