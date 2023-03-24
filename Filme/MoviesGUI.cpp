#include "MoviesGUI.h"
#include "CosFilmeDesenat.h"
#include "CosFilmeObisnuit.h"
#include "algorithm"
#include <set>
void StocareFilmeGUI::initializare_componente_GUI()
{
	//impartim fereastra in 2: stanga si dreapta
	//in stanga se afla gestiunea listei de filme, in dreapta se afla gestiunea cosului cu filme
	//"stanga" si "dreapta" pentru ca este QHBoxLayout
	//se adauga componente incepand din stanga, pe orizontala
	//aici:"left" component, then "right" component
	//care la randul lor contin alte componente

	QHBoxLayout* lyMain=new QHBoxLayout;
	this->setLayout(lyMain);










	//componenta stanga va contine tabelul cu filmele si functionalitatile pe care acesta le ofera
	QWidget* left=new QWidget;
	QVBoxLayout* lyLeft=new QVBoxLayout;
	left->setLayout(lyLeft);
	int nr_linii_filme=10;
	int nr_coloane_filme=4;
	this->listaFilme=new QTableWidget{nr_linii_filme,nr_coloane_filme};
	//header-ul tabelului
	QStringList HeaderTabel_Filme;
	HeaderTabel_Filme<<"Titlu"<<"Gen"<<"Actor principal"<<"Anul aparitiei";
	this->listaFilme->setHorizontalHeaderLabels(HeaderTabel_Filme);
	//optiune pentru a redimensiona celulele din tabel in functie de continut
	this->listaFilme->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);



	buton_informatii=new QPushButton("Informatii despre folosirea aplicatiei");
	buton_cauta=new QPushButton("Cautati un film");
	buton_adauga=new QPushButton("Adaugati un film");
	buton_actualizeaza=new QPushButton("Actualizati un film");
	buton_sterge=new QPushButton("Stergeti un film");
	buton_undo=new QPushButton("Realizati undo la ultima operatie");
	buton_filme2022=new QPushButton("Verificati daca in lista exista filme din 2022");
	buton_exportCSV=new QPushButton("Exportati lista de filme intr-un fisier de tip CSV");
	buton_filtrare_titlu=new QPushButton("Filtrati filmele dupa titlu");
	buton_filtrare_an=new QPushButton("Filtrati filmele dupa an");


	//parte din componenta stanga-necesar pentru implementarea comenzilor
	//folosim un QFormLayout pentru detaliile de adaugare a unui film
	QWidget* form=new QWidget;
	QFormLayout* lyForm=new QFormLayout;
	form->setLayout(lyForm);
	editTitlu=new QLineEdit;
	editActor=new QLineEdit;
	editGen=new QLineEdit;
	editAn=new QLineEdit;

	lyForm->addRow(lblTitlu,editTitlu);
	lyForm->addRow(lblGen,editGen);
	lyForm->addRow(lblActor,editActor);
	lyForm->addRow(lblAn,editAn);


	//adaugam toate componentele legate de operatiile pe lista de filme
	//in cateva layout-uri diferite pentru a economisi spatiu pe ecran
	//primul layout secundar contine form-ul unde se introduc datele necesare pentru unele comenzi
	QWidget* left_center1=new QWidget;
	QVBoxLayout* lyLeft_center1=new QVBoxLayout;
	left_center1->setLayout(lyLeft_center1);
	lyLeft_center1->addWidget(form);


	//al doilea layout secundar contine o parte din comenzi
	QWidget* left_center2=new QWidget;
	QHBoxLayout* lyLeft_center2=new QHBoxLayout;
	left_center2->setLayout(lyLeft_center2);
	lyLeft_center2->addWidget(buton_cauta);
	lyLeft_center2->addWidget(buton_adauga);
	lyLeft_center2->addWidget(buton_actualizeaza);
	lyLeft_center2->addWidget(buton_sterge);


	//al treilea layout secundar contine o parte din comenzi
	QWidget* left_center3=new QWidget;
	QHBoxLayout* lyLeft_center3=new QHBoxLayout;
	left_center3->setLayout(lyLeft_center3);
	lyLeft_center3->addWidget(buton_undo);
	lyLeft_center3->addWidget(buton_filme2022);



	//GroupBox cu radio-butoane care corespund celor 3 criterii de sortare
	QVBoxLayout* lyRadioBoxSortare=new QVBoxLayout;
	this->groupBoxSortare->setLayout(lyRadioBoxSortare);
	lyRadioBoxSortare->addWidget(radio_sortare_titlu);
	lyRadioBoxSortare->addWidget(radio_sortare_actor);
	lyRadioBoxSortare->addWidget(radio_sortare_an_gen);
	butonSortare=new QPushButton("Sortati filmele");
	lyRadioBoxSortare->addWidget(butonSortare);


	//al patrulea layout secundar contine doar filtrarea si butonul de informatii
	QWidget* left_center4=new QWidget;
	QVBoxLayout* lyLeft_center4=new QVBoxLayout;
	left_center4->setLayout(lyLeft_center4);
	lyLeft_center4->addWidget(buton_filtrare_titlu);
	lyLeft_center4->addWidget(buton_filtrare_an);
	lyLeft_center4->addWidget(buton_informatii);


	//al cincilea layout secundar contine filtrarea si sortarea
	QWidget* left_center5=new QWidget;
	QHBoxLayout* lyLeft_center5=new QHBoxLayout;
	left_center5->setLayout(lyLeft_center5);
	lyLeft_center5->addWidget(groupBoxSortare);
	lyLeft_center5->addWidget(left_center4);

	//componenta stanga este compusa din mai multe Widget-uri
	//lyLeft->addWidget(listaFilme);
	lyLeft->addWidget(tabelView);
	lyLeft->addWidget(left_center1);
	lyLeft->addWidget(left_center2);
	lyLeft->addWidget(left_center3);
	lyLeft->addWidget(left_center5);








	//componenta dreapta va contine cosul cu filme si functionalitatile pe care acesta le ofera
	QWidget* right=new QWidget;
	QVBoxLayout* lyRight=new QVBoxLayout;
	right->setLayout(lyRight);
	int nr_linii_cos=10;
	int nr_coloane_cos=4;
	this->cosFilme=new QTableWidget{nr_linii_cos,nr_coloane_cos};
	//header-ul tabelului
	QStringList HeaderTabel_Cos;
	HeaderTabel_Cos<<"Titlu"<<"Gen"<<"Actor principal"<<"Anul aparitiei";
	this->cosFilme->setHorizontalHeaderLabels(HeaderTabel_Cos);
	//optiune pentru a redimensiona celulele din tabel in functie de continut
	this->cosFilme->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


	buton_adaugaCos=new QPushButton("Adaugati un film din lista");
	buton_adauga_multipluCos=new QPushButton("Adaugati mai multe filme din lista");
	buton_sterge_totCos=new QPushButton("Goliti cosul");
	buton_exportCSV=new QPushButton("Exportati lista de filme intr-un fisier de tip CSV");
	buton_cos_obisnuit=new QPushButton("Afisare cos in mod normal");
	buton_cos_desenat=new QPushButton("Afisare desen specific");


	//parte din componenta dreapta-necesar pentru implementarea comenzilor
	//folosim un QFormLayout pentru detaliile de adaugare a unui film
	QWidget* formCos=new QWidget;
	QFormLayout* lyFormCos=new QFormLayout;
	formCos->setLayout(lyFormCos);
	editTitluCos=new QLineEdit;
	editAnCos=new QLineEdit;
	editNumarCos=new QLineEdit;
	editFisierCos=new QLineEdit;

	lyFormCos->addRow(lblTitluCos,editTitluCos);
	lyFormCos->addRow(lblAnCos,editAnCos);
	lyFormCos->addRow(lblNumarCos,editNumarCos);
	lyFormCos->addRow(lblFisierCos,editFisierCos);


	//adaugam toate componentele legate de operatiile pe lista de filme
	//in cateva layout-uri diferite pentru a economisi spatiu pe ecran
	//primul layout secundar contine form-ul unde se introduc datele necesare pentru unele comenzi
	QWidget* right_center1=new QWidget;
	QVBoxLayout* lyRight_center1=new QVBoxLayout;
	right_center1->setLayout(lyRight_center1);
	lyRight_center1->addWidget(formCos);
	lyRight_center1->addWidget(buton_cos_obisnuit);
	lyRight_center1->addWidget(buton_cos_desenat);
	lyRight_center1->addWidget(buton_adaugaCos);
	lyRight_center1->addWidget(buton_adauga_multipluCos);
	lyRight_center1->addWidget(buton_exportCSV);
	lyRight_center1->addWidget(buton_sterge_totCos);


	//componenta dreapta este compusa din mai multe Widget-uri
	//lyRight->addWidget(cosFilme);
	lyRight->addWidget(right_center1);


	lyBtnDy=new QVBoxLayout;
	btnDyn->setLayout(lyBtnDy);


	lyMain->addWidget(left);
	lyMain->addWidget(right);
	lyMain->addWidget(btnDyn);
}



void StocareFilmeGUI::reincarca_lista(std::vector<Film> filme) {
	/*
	this->listaFilme->clearContents();
	this->listaFilme->setRowCount(filme.size());
	int lineNumber=0;
	for (auto& film: filme) {
		this->listaFilme->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(film.obtineTitlu())));
		this->listaFilme->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(film.obtineGen())));
		this->listaFilme->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(film.obtineActor())));
		this->listaFilme->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(film.obtineAn())));
		lineNumber++;
	}
	*/
	model->regenereaza_lista(filme);
	adaugaButoane(filme);
}



void StocareFilmeGUI::conectare_butoane()
{
	QObject::connect(buton_informatii, &QPushButton::clicked,this,&StocareFilmeGUI::GUI_birou_informatii);
	QObject::connect(buton_cauta, &QPushButton::clicked,this,&StocareFilmeGUI::GUI_cauta_film);
	QObject::connect(buton_adauga, &QPushButton::clicked,this,&StocareFilmeGUI::GUI_adauga_film);
	QObject::connect(buton_actualizeaza,&QPushButton::clicked,this,&StocareFilmeGUI::GUI_actualizeaza_film);
	QObject::connect(buton_sterge, &QPushButton::clicked,this,&StocareFilmeGUI::GUI_sterge_film);
	QObject::connect(buton_undo, &QPushButton::clicked,this,&StocareFilmeGUI::GUI_undo);
	QObject::connect(buton_filme2022, &QPushButton::clicked,this,&StocareFilmeGUI::GUI_filme2022);
	QObject::connect(buton_filtrare_titlu, &QPushButton::clicked,this,&StocareFilmeGUI::GUI_filtreaza_titlu);
	QObject::connect(buton_filtrare_an, &QPushButton::clicked,this,&StocareFilmeGUI::GUI_filtreaza_an);
	QObject::connect(butonSortare,&QPushButton::clicked, [&]()
		{
			if(this->radio_sortare_titlu->isChecked())
				this->reincarca_lista(service.sorteaza_dupa_Titlu());
			if(this->radio_sortare_actor->isChecked())
				this->reincarca_lista(service.sorteaza_dupa_Actor());
			if(this->radio_sortare_an_gen->isChecked())
				this->reincarca_lista(service.sorteaza_dupa_AnGen());
		});



	QObject::connect(buton_adaugaCos, &QPushButton::clicked, this, &StocareFilmeGUI::GUI_adauga_film_cos);
	QObject::connect(buton_adauga_multipluCos,&QPushButton::clicked,this,&StocareFilmeGUI::GUI_adauga_numar_filme_cos);
	QObject::connect(buton_exportCSV, &QPushButton::clicked, this, &StocareFilmeGUI::GUI_exportCSV);
	QObject::connect(buton_sterge_totCos, &QPushButton::clicked, this, &StocareFilmeGUI::GUI_golire_cos);
	//afisare fereastra normala
	QObject::connect(buton_cos_obisnuit, &QPushButton::clicked, [this] {
		auto cos_cu_filme=new programCRUDGUI(service.get_program(),service);
		cos_cu_filme->run();
		});

	//afisare fereastra desen
	QObject::connect(buton_cos_desenat, &QPushButton::clicked, [this] {
		auto cos_cu_filme=new programReadOnlyGUI(service.get_program());
		cos_cu_filme->show();
		});
}



void StocareFilmeGUI::GUI_filtreaza_titlu()
{
	string film;
	string titlu=editTitlu->text().toStdString();
	editTitlu->clear();
	QListWidget *listWidgetFilme=new QListWidget;
	vector <Film> filtrare_titlu=service.filtreaza_dupa_Titlu(titlu);
	for(auto movie:filtrare_titlu)
	{
		film="Titlu:";
		film.append(movie.obtineTitlu());
		film.append("; ");
		film.append("Actor principal:");
		film.append(movie.obtineActor());
		film.append("; ");
		film.append("Gen:");
		film.append(movie.obtineGen());
		film.append("; ");
		film.append("Anul aparitiei:");
		film.append(std::to_string(movie.obtineAn()));
		QListWidgetItem* item=new QListWidgetItem(QString::fromStdString(film), listWidgetFilme);
	}
	listWidgetFilme->show();
}



void StocareFilmeGUI::GUI_filtreaza_an()
{
	string film;
	int an=editAn->text().toInt();
	editAn->clear();
	QListWidget* listWidgetFilme=new QListWidget;
	vector <Film> filtrare_an=service.filtreaza_dupa_An(an);
	for (auto movie : filtrare_an)
	{
		film = "Titlu:";
		film.append(movie.obtineTitlu());
		film.append("; ");
		film.append("Actor principal:");
		film.append(movie.obtineActor());
		film.append("; ");
		film.append("Gen:");
		film.append(movie.obtineGen());
		film.append("; ");
		film.append("Anul aparitiei:");
		film.append(std::to_string(movie.obtineAn()));
		QListWidgetItem* item2 = new QListWidgetItem(QString::fromStdString(film), listWidgetFilme);
	}
	listWidgetFilme->show();
}




void clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}



void StocareFilmeGUI::adaugaButoane(const std::vector<Film>& filme) {	
	//sterge
	clearLayout(lyBtnDy);
	//reconstruieste
	std::set <string> genuri_unice;
	vector<Film> vec=service.obtine_toate_filmele();
	for (size_t i=0; i<vec.size(); i++)
		genuri_unice.insert(vec[i].obtineGen());

	std::set<string>::iterator it;
	butoane_genuri_filme.clear();
	for (it= genuri_unice.begin(); it!= genuri_unice.end(); ++it) {
		QPushButton* ctr=new QPushButton(QString::fromStdString(*it));
		butoane_genuri_filme.push_back(ctr);
	}
	for (auto button:butoane_genuri_filme) {
		lyBtnDy->addWidget(button);
	}
	for (auto button:butoane_genuri_filme) {
		QObject::connect(button, &QPushButton::clicked, this, &StocareFilmeGUI::optiune);
	}
}



void StocareFilmeGUI::optiune()
{
	try {
		QPushButton* buttonSender=qobject_cast<QPushButton*>(sender()); // se retine butonul apasat
		QString buttonText=buttonSender->text(); // extragere text din buton
		vector <Film> filme;
		filme=service.obtine_toate_filmele();
		vector <Film> un_singur_gen;
		for(auto& film:filme)
		{
			if(QString::fromStdString(film.obtineGen())==buttonText)
				un_singur_gen.push_back(film);
		}
		string mesaj="Numarul filmelor de tipul selectat este: ";
		string message=std::to_string(un_singur_gen.size());
		mesaj.append(message);
		QMessageBox::information(this, "Info", QString::fromStdString(mesaj));
	}
	catch (ExceptieRepozitoriu& er) {
		QMessageBox::information(this, "Warning", QString::fromStdString(er.obtineMesajeEroare()));
	}
	catch (ExceptieValidator& ev) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ev.obtine_mesaje_eroare()));
	}
}




void StocareFilmeGUI::GUI_birou_informatii()
{
	string mesaj="Inainte de a adauga/actualiza un film completati toate cele 4 casute.\nInainte de a sterge/cauta un film introduceti doar titlul si anul aparitiei.";
	QMessageBox::information(this, "Info", QString::fromStdString(mesaj));
}



void StocareFilmeGUI::GUI_cauta_film()
{
	try
	{
		string titlu=editTitlu->text().toStdString();
		int an=editAn->text().toInt();

		editTitlu->clear();
		editAn->clear();

		Film film1=this->service.cauta_film(titlu, an);
		string an2=std::to_string(an);
		QMessageBox::information(this, "Info", QString::fromStdString("Titlu: "+
			film1.obtineTitlu()+'\n'+"Gen: "+film1.obtineGen()+'\n'+"Actor principal: "+
			film1.obtineActor()+'\n'+"Anul aparitiei: "+an2+'\n'));
	}
	catch (ExceptieRepozitoriu& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.obtineMesajeEroare()));
	}
	catch (ExceptieValidator& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.obtine_mesaje_eroare()));
	}
}



void StocareFilmeGUI::GUI_adauga_film()
{
	try 
	{
		string titlu=editTitlu->text().toStdString();
		string gen=editGen->text().toStdString();
		string actor=editActor->text().toStdString();
		int an=editAn->text().toInt();

		editTitlu->clear();
		editActor->clear();
		editGen->clear();
		editAn->clear();

		this->service.adauga_film(titlu,gen,actor,an);
		this->reincarca_lista(this->service.obtine_toate_filmele());
		QMessageBox::information(this, "Info", QString::fromStdString("Film adaugat cu succes."));
	}
	catch (ExceptieRepozitoriu& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.obtineMesajeEroare()));
	}
	catch (ExceptieValidator& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.obtine_mesaje_eroare()));
	}
}



void StocareFilmeGUI::GUI_actualizeaza_film()
{
	try 
	{
		string titlu=editTitlu->text().toStdString();
		string gen=editGen->text().toStdString();
		string actor=editActor->text().toStdString();
		int an=editAn->text().toInt();

		editTitlu->clear();
		editActor->clear();
		editGen->clear();
		editAn->clear();

		this->service.actualizeaza_film(titlu,gen,actor,an);
		this->reincarca_lista(this->service.obtine_toate_filmele());
		QMessageBox::information(this, "Info", QString::fromStdString("Film actualizat cu succes."));
	}
	catch (ExceptieRepozitoriu& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.obtineMesajeEroare()));
	}
	catch (ExceptieValidator& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.obtine_mesaje_eroare()));
	}
}



void StocareFilmeGUI::GUI_sterge_film()
{
	try 
	{
		string titlu=editTitlu->text().toStdString();
		int an=editAn->text().toInt();

		editTitlu->clear();
		editAn->clear();

		this->service.sterge_film(titlu,an);
		this->reincarca_lista(this->service.obtine_toate_filmele());
		QMessageBox::information(this, "Info", QString::fromStdString("Film eliminat cu succes."));
	}
	catch (ExceptieRepozitoriu& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.obtineMesajeEroare()));
	}
	catch (ExceptieValidator& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.obtine_mesaje_eroare()));
	}
}



void StocareFilmeGUI::GUI_undo()
{
	try
	{
		this->service.undo();
		this->reincarca_lista(this->service.obtine_toate_filmele());
		QMessageBox::information(this, "Info", QString::fromStdString("Undo realizat cu succes."));
	}
	catch (ExceptieUndo& eu) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(eu.getMsg()));
	}
}





void StocareFilmeGUI::GUI_filme2022()
{
	if (this->service.exista_film2022() == true)
	{
		string mesaj="In lista se afla cel putin un film aparut in anul 2022.";
		QMessageBox::information(this, "Info", QString::fromStdString(mesaj));
	}
	else
	{
		string mesaj="In lista nu se afla niciun film aparut in anul 2022.";
		QMessageBox::information(this, "Info", QString::fromStdString(mesaj));
	}
}






















void StocareFilmeGUI::reincarca_cosul(vector<Film> cos_filme) {
	this->cosFilme->clearContents();
	this->cosFilme->setRowCount(cos_filme.size());
	int lineNumber=0;
	for (auto& film: cos_filme) {
		this->cosFilme->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(film.obtineTitlu())));
		this->cosFilme->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(film.obtineGen())));
		this->cosFilme->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(film.obtineActor())));
		this->cosFilme->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(film.obtineAn())));
		lineNumber++;
	}
}



void StocareFilmeGUI::GUI_adauga_film_cos()
{
	try 
	{
		string titlu=editTitluCos->text().toStdString();
		int an=editAnCos->text().toInt();

		editTitluCos->clear();
		editAnCos->clear();

		this->service.adauga_film_in_cos(titlu,an);
		this->reincarca_cosul(this->service.obtine_toate_filmele_din_cos());
		string mesaj="Numarul filmelor din cos este in prezent: ";
		string message=std::to_string(service.obtine_marime_cos());
		mesaj.append(message);
		QMessageBox::information(this, "Info", QString::fromStdString(mesaj));
	}
	catch (ExceptieRepozitoriu& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.obtineMesajeEroare()));
	}
}



void StocareFilmeGUI::GUI_adauga_numar_filme_cos()
{

	int numar=editNumarCos->text().toInt();
	editNumarCos->clear();
	if(numar<=0)
		QMessageBox::information(this, "Info", QString::fromStdString("Numarul introdus trebuie sa fie pozitiv!"));
	else if(numar>service.obtine_toate_filmele().size())
		QMessageBox::information(this, "Info", QString::fromStdString("Numarul introdus depaseste lungimea listei!"));
	else 
	{
		this->service.genereaza_cos(numar);
		this->reincarca_cosul(this->service.obtine_toate_filmele_din_cos());
		string mesaj="Numarul filmelor din cos este in prezent: ";
		string message=std::to_string(service.obtine_marime_cos());
		mesaj.append(message);
		QMessageBox::information(this, "Info", QString::fromStdString(mesaj));
	}
}



void StocareFilmeGUI::GUI_golire_cos()
{

	this->service.sterge_filmele_din_cos();
	this->reincarca_cosul(this->service.obtine_toate_filmele_din_cos());
	string mesaj="Numarul filmelor din cos este in prezent: ";
	string message=std::to_string(service.obtine_marime_cos());
	mesaj.append(message);
	QMessageBox::information(this, "Info", QString::fromStdString(mesaj));
}



void StocareFilmeGUI::GUI_exportCSV()
{
	try
	{
		string nume_fisier=editFisierCos->text().toStdString();
		editFisierCos->clear();
		this->service.exporta_CSV(nume_fisier);
		QMessageBox::information(this, "Info", QString::fromStdString("Export realizat cu succes."));
	}
	catch (ExceptieValidator& ev) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ev.obtine_mesaje_eroare()));
	}
}