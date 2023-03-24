#include "Movie.h"
#include "Repository.h"
#include "Service.h"
#include <assert.h>
#include <fstream>



void test_obtine_atribuie()
{
	Film film1{"Driven to kill","action","Steven Seagal",2009};
	assert(film1.obtineTitlu()=="Driven to kill");
	assert(film1.obtineGen()=="action");
	assert(film1.obtineActor()=="Steven Seagal");
	assert(film1.obtineAn()==2009);

	film1.atribuieTitlu("Titanic");
	film1.atribuieGen("drama");
	film1.atribuieActor("Leonardo DiCaprio");
	film1.atribuieAn(1997);

	assert(film1.obtineTitlu()=="Titanic");
	assert(film1.obtineGen()=="drama");
	assert(film1.obtineActor()=="Leonardo DiCaprio");
	assert(film1.obtineAn()==1997);
}



void test_adauga_repozitoriu()
{
	RepozitoriuFilme testR;
	Film film1{"Stalingrad","history","Petr Fedrov",2013};
	Film film2{"Gridiron Gang","drama","Dwayne Johnson",2006};
	testR.adauga(film1);
	testR.adauga(film2);
	assert(testR.obtine_toate_filmele().size()==2);

	Film film3{"Stalingrad","history","Dominique Horwitz",2013};
	try
	{
		testR.adauga(film3);
		assert(false);
	}
	catch(ExceptieRepozitoriu)
	{
		assert(true);
	}
}



void test_actualizeaza_repozitoriu()
{
	RepozitoriuFilme testR;
	Film film1{"Stalingrad","history","Yanina Studilina",2013};
	Film film2{"Gridiron Gang","drama","Dwayne Johnson",2006};
	Film film3{"Stalingrad", "war", "Petr Fedorov", 2013};
	Film film4{ "Gridiron Gang","sport","Dwayne Johnson",2007};
	testR.adauga(film1);
	testR.adauga(film2);
	testR.actualizeaza(film3);
	try
	{
		testR.actualizeaza(film4);
	}
	catch(ExceptieRepozitoriu)
	{
		assert(true);
	}
}



void test_sterge_repozitoriu()
{
	RepozitoriuFilme testR;
	try
	{
		testR.sterge("Hart's War",2002);
		assert(false);
	}
	catch (ExceptieRepozitoriu)
	{
		assert(true);
	}
	Film film1{"Today You Die","action","Steven Seagal",2005};
	Film film2{"Der Untergang","history","Bruno Ganz",2004};
	Film film3{"Saving Private Ryan","war","Tom Hanks",1998};
	testR.adauga(film1);
	testR.adauga(film2);
	testR.adauga(film3);
	assert(testR.obtine_toate_filmele().size()==3);
	testR.sterge("Today You Die",2005);
	assert(testR.obtine_toate_filmele().size()==2);
	testR.sterge("Saving Private Ryan",1998);
	try
	{
		testR.sterge("Hart's War",2002);
	}
	catch (ExceptieRepozitoriu& ev)
	{
		assert(ev.obtineMesajeEroare() == "Filmul cu titlul Hart's War si anul de aparitie introdus nu exista in lista!\n");
	}
}



void test_gaseste_repozitoriu()
{
	RepozitoriuFilme testR;
	Film film1{"Olympus has fallen","action","Gerard Butler",2013};
	Film film2{"Stalingrad","history","Dominique Horwitz",1993};
	Film film3{"Hart's War","war","Bruce Wills",2002};
	testR.adauga(film1);
	testR.adauga(film2);

	assert(testR.exista(film1));
	assert(!testR.exista(film3));

	auto film_gasit=testR.gaseste_film("Stalingrad",1993);
	assert(film_gasit.obtineActor()=="Dominique Horwitz");
	assert(film_gasit.obtineGen()=="history");
	
	try 
	{
		testR.gaseste_film("Above the Law",1988);
	}
	catch(ExceptieRepozitoriu& ev)
	{
		assert(ev.obtineMesajeEroare()=="Filmul cu titlul Above the Law si anul de aparitie introdus nu exista in lista!\n");
	}
}



void test_generare_cos_repozitoriu()
{
	RepozitoriuFilme testR;
	CosFilme testC;
	Film film1{ "Stalingrad","history","Petr Fedrov",2013 };
	Film film2{ "Gridiron Gang","drama","Dwayne Johnson",2006 };
	Film film3{ "Driven to kill","action","Steven Seagal",2009 };
	testR.adauga(film1);
	testR.adauga(film2);
	testR.adauga(film3);
	assert(testC.obtine_toate_filmele_din_cos().size()==0);
	testC.genereaza_cos(testR.obtine_toate_filmele(),2);
	assert(testC.obtine_toate_filmele_din_cos().size()==2);
}


void test_cauta_film()
{
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};
	testService.adauga_film("Der Untergang", "history", "Bruno Ganz", 2004);
	testService.cauta_film("Der Untergang", 2004);
	assert(true);
}



void test_undo()
{
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};
	testService.adauga_film("Gridiron Gang", "drama", "Dwayne Johnson", 2006);
	testService.adauga_film("Stalingrad", "history", "Dominique Horwitz", 1993);
	testService.adauga_film("Hart's War", "war", "Collin Farell", 2002);
	assert(testService.obtine_toate_filmele().size()==3);
	//TEST STERGE
	testService.sterge_film("Gridiron Gang",2006);
	assert(testService.obtine_toate_filmele().size()==2);
	try 
	{
		testService.cauta_film("Gridiron Gang", 2006);
		assert(false);
	}
	catch (ExceptieRepozitoriu&)
	{assert(true);}
	testService.undo();
	assert(testService.obtine_toate_filmele().size()==3);
	try
	{
		testService.cauta_film("Gridiron Gang", 2006);
		assert(true);
	}
	catch (ExceptieRepozitoriu&)
	{assert(false);}
	//TEST ADAUGA
	try
	{
		testService.cauta_film("Hart's War",2002);
		assert(true);
	}
	catch (ExceptieRepozitoriu&)
	{assert(false);}
	testService.undo();
	assert(testService.obtine_toate_filmele().size()==2);
	try
	{
		testService.cauta_film("Hart's War", 2002);
		assert(false);
	}
	catch (ExceptieRepozitoriu&)
	{
		assert(true);
	}
	//TEST ACTUALIZEAZA
	Film film1=testService.cauta_film("Stalingrad",1993);
	assert(film1.obtineGen()=="history");
	testService.actualizeaza_film("Stalingrad", "war", "Dominique Horwitz", 1993);
	try
	{
		testService.cauta_film("Stalingrad",1993);
		assert(true);
	}
	catch (ExceptieRepozitoriu&)
	{assert(false);}
	Film film2=testService.cauta_film("Stalingrad",1993);
	assert(film2.obtineGen()=="war");
	testService.undo();
	Film film3=testService.cauta_film("Stalingrad",1993);
	assert(film3.obtineGen()=="history");
	testService.undo();
	testService.undo();
	try 
	{
		testService.undo();
		assert(false);
	}
	catch (ExceptieUndo& ex)
	{
		assert(ex.getMsg()=="Nu se mai poate efectua Undo!");
	}
}




void test_adauga_film()
{
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};

	testService.adauga_film("Gridiron Gang", "drama", "Dwayne Johnson", 2006);
	testService.adauga_film("Stalingrad", "history", "Dominique Horwitz", 1993);

	assert(testService.obtine_toate_filmele().size()==2);
	try
	{
		testService.adauga_film("Stalingrad", "war", "Petr Fedorov", 1993);
		assert(false);
	}
	catch (ExceptieRepozitoriu&)
	{
		assert(true);
	}
	try
	{
		testService.adauga_film("Der Untergang", "history", "Bruno Ganz", 2004);
		assert(true);
	}
	catch (ExceptieValidator&)
	{assert(false);}
	try
	{
		testService.adauga_film("SM", "SF", "Tom Holland", 2021);
	}
	catch (ExceptieValidator& ev)
	{
		assert(ev.obtine_mesaje_eroare() == "Titlul filmului trebuie sa aiba cel putin 3 caractere.\nGenul filmului trebuie sa aiba cel putin 3 caractere.\n");
	}
	try
	{
		testService.adauga_film("Aquaman and the Lost Kingdom", "science fiction", "AH", 2023);
	}
	catch (ExceptieValidator& ev)
	{
		assert(ev.obtine_mesaje_eroare() == "Numele actorului principal trebuie sa aiba cel putin 3 caractere.\nFilmul nu apartine intervalului de timp corespunzator(1900-2022).\n");
	}
}



void test_actualizeaza_film()
{
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};
	testService.adauga_film("Hart's War", "war", "Collin Farell", 2002);
	try
	{
		testService.actualizeaza_film("Hart's War", "drama", "Bruce Wills", 2002);
		assert(true);
	}
	catch (ExceptieRepozitoriu&)
	{assert(false);}
}



void test_sterge_film()
{
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};
	testService.adauga_film("The Expendables 3", "action", "Sylvester Stallone", 2014);
	testService.adauga_film("Hart's War", "war", "Collin Farell", 2002);
	try
	{
		testService.sterge_film("Hart's War", 2002);
		assert(true);
	}
	catch (ExceptieRepozitoriu&)
	{assert(false);}
}




void test_filtreaza()
{
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};
	testService.adauga_film("Hart's War", "war", "Collin Farell", 2002);
	testService.adauga_film("Downfall", "history", "Bruno Ganz", 2004);
	testService.adauga_film("Force of Execution", "crime", "Steven Seagal", 2013);
	testService.adauga_film("Saving Private Ryan", "war", "Tom Hanks", 1998);
	testService.adauga_film("Stalingrad", "history", "Pyotr Fyodorov", 2013);
	testService.adauga_film("Olympus has fallen", "action", "Gerard Butler", 2013);
	testService.adauga_film("Gridiron Gang", "drama", "Dwayne Johnson", 2006);
	testService.adauga_film("Stalingrad", "history", "Thomas Kretschmann", 1993);
	vector<Film> test_titlu=testService.filtreaza_dupa_Titlu("Stalingrad");
	assert(test_titlu.size()==2);
	testService.filtreaza_dupa_An(2013);
	vector<Film> test_an=testService.filtreaza_dupa_An(2013);
	assert(test_an.size()==3);
}



void test_sorteaza()
{
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};
	testService.adauga_film("Hart's War", "war", "Collin Farell", 2002);
	testService.adauga_film("Today You Die", "action", "Steven Seagal", 2005);
	testService.adauga_film("Downfall", "history", "Bruno Ganz", 2004);
	testService.adauga_film("Force of Execution", "crime", "Steven Seagal", 2013);
	testService.adauga_film("Saving Private Ryan", "war", "Tom Hanks", 1998);
	testService.adauga_film("Stalingrad", "history", "Pyotr Fyodorov", 2013);
	testService.adauga_film("Olympus has fallen", "action", "Gerard Butler", 2013);
	testService.adauga_film("Gridiron Gang", "drama", "Dwayne Johnson", 2006);
	testService.adauga_film("Driven to kill", "action", "Steven Seagal", 2009);
	testService.adauga_film("After we met", "love", "Hero Fiennes-Tiffin", 2019);
	testService.adauga_film("Stalingrad", "history", "Thomas Kretschmann", 1993);

	vector<Film> test_titlu=testService.sorteaza_dupa_Titlu();
	assert(test_titlu[1].obtineActor()=="Bruno Ganz");
	assert(test_titlu[10].obtineTitlu()=="Today You Die");

	vector<Film> test_actor=testService.sorteaza_dupa_Actor();
	assert(test_actor[2].obtineAn()==2006);
	assert(test_actor[6].obtineActor()=="Steven Seagal");
	assert(test_actor[10].obtineActor()=="Tom Hanks");

	vector<Film> test_AnGen=testService.sorteaza_dupa_AnGen();
	assert(test_AnGen[7].obtineGen()=="action");
	assert(test_AnGen[8].obtineGen()=="crime");
	assert(test_AnGen[9].obtineGen()=="history");
}


void test_adauga_film_in_cos()
{
	vector<Film>filme;
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};
	testService.adauga_film("Hart's War", "war", "Collin Farell", 2002);
	testService.adauga_film("Today You Die", "action", "Steven Seagal", 2005);
	testService.adauga_film_in_cos("Hart's War", 2002);
	testService.adauga_film_in_cos("Today You Die", 2005);
	assert(testService.obtine_toate_filmele_din_cos().size()==2);
}


void test_sterge_filmele_din_cos()
{
	vector<Film>cos_filme;
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};
	testService.adauga_film("The Expendables 3", "action", "Sylvester Stallone", 2014);
	testService.adauga_film("Hart's War", "war", "Collin Farell", 2002);
	testService.adauga_film("Force of Execution", "crime", "Steven Seagal", 2013);
	testService.adauga_film_in_cos("Hart's War", 2002);
	testService.adauga_film_in_cos("The Expendables 3",2014);
	testService.adauga_film_in_cos("Force of Execution", 2013);
	assert(testService.obtine_toate_filmele_din_cos().size()==3);
	testService.sterge_filmele_din_cos();
	assert(testService.obtine_toate_filmele_din_cos().size()==0);
}



void test_generare_cos()
{
	vector<Film>cos_filme;
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};
	testService.adauga_film("Force of Execution", "crime", "Steven Seagal", 2013);
	testService.adauga_film("The Expendables 3", "action", "Sylvester Stallone", 2014);
	testService.adauga_film("Saving Private Ryan", "war", "Tom Hanks", 1998);
	testService.adauga_film("Today You Die", "action", "Steven Seagal", 2005);
	testService.genereaza_cos(3);
	assert(testService.obtine_marime_cos()==3);
}


void test_obtine_marime_cos()
{
	vector<Film>cos_filme;
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};
	testService.adauga_film("Hart's War", "war", "Collin Farell", 2002);
	testService.adauga_film("Today You Die", "action", "Steven Seagal", 2005);
	testService.adauga_film("Downfall", "history", "Bruno Ganz", 2004);
	testService.adauga_film_in_cos("Hart's War", 2002);
	testService.adauga_film_in_cos("Today You Die", 2005);
	testService.adauga_film_in_cos("Downfall", 2004);
	assert(testService.obtine_marime_cos() ==3);
}


void test_exista_film2022()
{
	vector<Film>cos_filme;
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};
	testService.adauga_film("Hart's War", "war", "Collin Farell", 2002);
	testService.adauga_film("Today You Die", "action", "Steven Seagal", 2005);
	testService.adauga_film_in_cos("Hart's War", 2002);
	testService.adauga_film_in_cos("Today You Die", 2005);
	assert(testService.exista_film2022()==false);
	testService.adauga_film("Ambulance","thriller","Jake Gyllenhaal",2022);
	assert(testService.exista_film2022()==true);
}


void test_export_CSV()
{
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};
	testService.adauga_film("Hart's War", "war", "Collin Farell", 2002);
	testService.adauga_film("Today You Die", "action", "Steven Seagal", 2005);
	testService.adauga_film("Downfall", "history", "Bruno Ganz", 2004);
	testService.adauga_film_in_cos("Hart's War", 2002);
	testService.adauga_film_in_cos("Today You Die", 2005);
	testService.adauga_film_in_cos("Downfall", 2004);

	vector <Film> filme;
	Film film1{"Hart's War", "war", "Collin Farell", 2002};
	Film film2{"Today You Die", "action", "Steven Seagal", 2005};
	Film film3{"Downfall", "history", "Bruno Ganz", 2004};
	filme.push_back(film1);
	filme.push_back(film2);
	filme.push_back(film3);

	string nume_fisier="test.csv";
	testService.exporta_CSV(nume_fisier);
	std::ifstream in(nume_fisier);
	string linie,delimitator=",";
	size_t pozitie,numar_linie=0;
	vector <string> cuvinte;
	getline(in,linie);
	while(getline(in,linie))
	{
		cuvinte.erase(cuvinte.begin(),cuvinte.end());
		while((pozitie=linie.find(delimitator))!=linie.npos)
		{
			string cuvant=linie.substr(0,pozitie);
			cuvinte.push_back(cuvant);
			linie.erase(linie.begin(),linie.begin()+pozitie+delimitator.length());
		}
		cuvinte.push_back(linie);
		assert(cuvinte[0]==filme[numar_linie].obtineTitlu());
		assert(cuvinte[1]==filme[numar_linie].obtineGen());
		assert(cuvinte[2]==filme[numar_linie].obtineActor());
		numar_linie++;
	}
	in.close();
	remove("test.csv");
}



void test_validator_fisier()
{
	RepozitoriuFilme testR;
	CosFilme testC;
	ValidatorFilm testV;
	StocareFilme testService{testR,testC,testV};
	try
	{
		testService.exporta_CSV("as");
		assert(false);
	}
	catch (ExceptieValidator& ev)
	{assert(ev.obtine_mesaje_eroare()=="Numele fisierului trebuie sa aiba cel putin 4 caractere.\n");}
	try
	{
		testService.exporta_CSV("lolp.re");
		assert(false);
	}
	catch (ExceptieValidator& ev)
	{assert(ev.obtine_mesaje_eroare()=="Numele fisierului nu are extensia csv.\n");}
}



void testeDomeniu()
{
	test_obtine_atribuie();
}



void testeRepozitoriu()
{
	test_adauga_repozitoriu();
	test_actualizeaza_repozitoriu();
	test_sterge_repozitoriu();
	test_gaseste_repozitoriu();
	test_generare_cos_repozitoriu();
	test_validator_fisier();
}



void teste_service()
{
	test_undo();
	test_cauta_film();
	test_adauga_film();
	test_actualizeaza_film();
	test_sterge_film();
	test_filtreaza();
	test_sorteaza();

	test_adauga_film_in_cos();
	test_sterge_filmele_din_cos();
	test_generare_cos();
	test_obtine_marime_cos();
	test_exista_film2022();
	test_export_CSV();
}