//#define _CRTDBG_MAP_ALLOC
#include "filme.h"
#include <QtWidgets/QApplication>
#include "UI.h"
#include "Movie.h"
#include "VectorDinamic.h"
#include "Tests.h"
#include "Service.h"
#include "MoviesGUI.h"
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
using std::cout;
using std::endl;



void test_complet()
{
	teste_service();
	cout<<"Teste pe service finalizate."<<endl;
	testeRepozitoriu();
	cout<<"Teste pe repozitoriu finalizate."<<endl;
	testeDomeniu();
	cout<<"Teste pe domeniu finalizate."<<endl;
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RepozitoriuFilme repozitoriu;
	CosFilme cos;
	ValidatorFilm validator;
	StocareFilme service{repozitoriu,cos,validator};
	service.adauga_film("Today You Die", "action", "Steven Seagal", 2005);
	service.adauga_film("Downfall", "history", "Bruno Ganz", 2004);
	service.adauga_film("Force of Execution", "crime", "Steven Seagal", 2013);
	service.adauga_film("Saving Private Ryan", "war", "Tom Hanks", 1998);
	service.adauga_film("Stalingrad", "history", "Pyotr Fyodorov", 2013);
	service.adauga_film("Olympus has fallen", "action", "Gerard Butler", 2013);
	service.adauga_film("Gridiron Gang", "drama", "Dwayne Johnson", 2006);
	service.adauga_film("Driven to kill", "action", "Steven Seagal", 2009);
	service.adauga_film("After we met", "love", "Hero Fiennes-Tiffin", 2019);
	service.adauga_film("Stalingrad", "history", "Thomas Kretschmann", 1993);
	StocareFilmeGUI gui{service};
	gui.show();
    return a.exec();
}



/*
void pornireAplicatie()
{
	RepozitoriuFilme repozitoriu;
	ValidatorFilm validator;
	StocareFilme service{repozitoriu,validator};
	consolaIU iu(service);
	iu.ruleaza();
}
int main()
{
	test_complet();
	pornireAplicatie();
	_CrtDumpMemoryLeaks();
}
*/