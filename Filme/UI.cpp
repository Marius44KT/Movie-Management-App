#pragma once 
#include "UI.h"
#include "VectorDinamic.h"
#include <iostream>
#include <fstream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ofstream;
using namespace std;
void consolaIU::printareMeniu()
{
	cout<<"-------------------------------------------------------------------------------------------"<<endl;
	cout<<"-------------------------------------------------------------------------------------------"<<endl;
	cout<<"-------------------------------------------------------------------------------------------"<<endl;
	cout<<"Aveti posibilitatea de a gestiona o lista de filme."<<endl;
	cout<<"Fiecare film este caracterizat de:titlu,gen,actor principal,an aparitie"<<endl;
	cout<<"Apasati tasta corespunzatoare uneia dintre comenzile de mai jos:"<<endl;
	cout<<"1.Afisati toate filmele care compun lista."<<endl;
	cout<<"2.Adaugati un nou film la lista curenta."<<endl;
	cout<<"3.Actualizati un film din lista curenta.(gen/actor principal)"<<endl;
	cout<<"4.Stergeti un film care se afla in lista curenta."<<endl;
	cout<<"5.Cautati un film care se afla in lista curenta."<<endl;
	cout<<"6.Filtrati lista de filme dupa unul din urmatoarele criterii:1)titlu sau 2)anul aparitiei."<<endl;
	cout<<"7.Sortati dupa unul din urmatoarele criterii:1)titlu,2)actor principal sau 3)an aparitie+gen."<<endl;
	cout<<"8.Verificati daca lista de filme contine cel putin un film din 2022."<<endl;
	cout<<"9.Realizati Undo pentru ultima operatie efectuata."<<endl;
	cout<<"############################################################################################"<<endl;
	cout<<"Aveti, de asemenea, posibilitatea de a gestiona un cos de filme."<<endl;
	cout<<"10.Afisati toate filmele care compun cosul."<<endl;
	cout<<"11.Adaugati un nou film in cosul dumneavoastra."<<endl;
	cout<<"12.Adaugati un numar de filme la intamplare in cosul dumneavoastra."<<endl;
	cout<<"13.Exportati toate filmele din lista curenta intr-un fisier de tip CSV."<<endl;
	cout<<"14.Stergeti toate filmele din cos."<<endl;
	cout<<"15.Inchideti aplicatia."<<endl;
	cout<<"-------------------------------------------------------------------------------------------"<<endl;
	cout<<"-------------------------------------------------------------------------------------------"<<endl;
	cout<<"-------------------------------------------------------------------------------------------"<<endl;
}


void consolaIU::undo_adauga_modifica_sterge()
{
	service.undo();
}


void consolaIU::printeaza_toate_filmele_csv()
{
	//auto lista_filme=service.obtine_toate_filmele();
	string nume_fisier;
	cout<<"Numele fisierului cu extensia .csv este:";
	getline(cin>>ws,nume_fisier);
	try 
	{
		service.exporta_CSV(nume_fisier);
	}
	catch(ExceptieValidator& ve)
	{
		cout<<ve.obtine_mesaje_eroare();
	}
}



void consolaIU::printeaza_toate_filmele() 
{
	auto lista_filme=service.obtine_toate_filmele();
	if (lista_filme.size()==0)
		cout<<"Lista de filme este goala momentan."<<endl;
	else
		for (int i=0; i<lista_filme.size(); i++)
		{
			Film film=lista_filme[i];
			cout<<"Titlu: " <<film.obtineTitlu()<<" | Gen: "<<film.obtineGen()<<" | Actor principal: "<<film.obtineActor()<<" | Anul aparitiei: "<<film.obtineAn()<<endl;
		}
}



void consolaIU::printeaza_toate_filmele_din_cos() 
{
	auto lista_filme=service.obtine_toate_filmele_din_cos();
	if (lista_filme.size()==0)
		cout<<"Cosul de filme este gol momentan."<<endl;
	else
		for (int i=0; i<lista_filme.size(); i++)
		{
			Film film=lista_filme[i];
			cout<<"Titlu: " <<film.obtineTitlu()<<" | Gen: "<<film.obtineGen()<<" | Actor principal: "<<film.obtineActor()<<" | Anul aparitiei: "<<film.obtineAn()<<endl;
		}
}




void consolaIU::adaugare_iu()
{
	string titlu,gen,actor,an1;
	int an,ok=1;
	cout<<"Titlul filmului este:";
	getline(cin>>ws,titlu);
	cout<<"Genul filmului este:";
	getline(cin>>ws,gen);
	cout<<"Actorul principal care joaca in film este:";
	getline(cin>>ws,actor);
	cout<<"Anul in care filmul a fost lansat este:";
	getline(cin>>ws,an1);
	for (char const &c : an1) 
	{
        if(std::isdigit(c)==0) 
		{
			ok=0;
			break;
		}
    }
    if(ok==0)
		cout<<"Anul trebuie sa fie un NUMAR!"<<endl;
	else 
	{
		an=stoi(an1);
		try
		{
			service.adauga_film(titlu,gen,actor,an);
		}
		catch(ExceptieRepozitoriu& er)
		{
			cout<<er.obtineMesajeEroare();
			return;
		}
		catch(ExceptieValidator& ev)
		{
			cout<<"Filmul pe care doriti sa il adaugati nu este valid!"<<endl;
			cout<<ev.obtine_mesaje_eroare();
			return;
		}
		cout<<"Filmul dorit a fost adaugat cu succes!"<<endl;
	}
}



void consolaIU::actualizare_iu()
{
	string titlu,gen,actor,an1;
	int an,ok=1;
	cout<<"Titlul filmului este:";
	getline(cin>>ws,titlu);
	cout<<"Genul filmului este:";
	getline(cin>>ws,gen);
	cout<<"Actorul principal care joaca in film este:";
	getline(cin>>ws,actor);
	cout<<"Anul in care filmul a fost lansat este:";
	getline(cin>>ws,an1);
	for (char const &c : an1) 
	{
        if(std::isdigit(c)==0) 
		{
			ok=0;
			break;
		}
    }
	if(ok==0)
		cout<<"Anul trebuie sa fie un NUMAR!"<<endl;
	else 
	{
		an=stoi(an1);
		try
		{
			service.actualizeaza_film(titlu,gen,actor,an);
		}
		catch(ExceptieRepozitoriu& er)
		{
			cout<<er.obtineMesajeEroare();
			return;
		}
		catch(ExceptieValidator& ev)
		{
			cout<<"Filmul pe care doriti sa il actualizati nu este valid!"<<endl;
			cout<<ev.obtine_mesaje_eroare();
			return;
		}
		cout<<"Filmul dorit a fost actualizat cu succes!"<<endl;
	}
}



void consolaIU::stergere_iu()
{
	string titlu,an1;
	int an,ok=1;
	cout<<"Titlul filmului este:";
	getline(cin>>ws,titlu);
	cout<<"Anul in care filmul a fost lansat este:";
	getline(cin>>ws,an1);
	for (char const &c : an1) 
	{
        if(std::isdigit(c)==0) 
		{
			ok=0;
			break;
		}
    }
	if(ok==0)
		cout<<"Anul trebuie sa fie un NUMAR!"<<endl;
	else 
	{
		an=stoi(an1);
		try
		{
			service.sterge_film(titlu,an);
		}
		catch(ExceptieRepozitoriu& er)
		{
			cout<<er.obtineMesajeEroare();
			return;
		}
		cout<<"Filmul dorit a fost sters cu succes!"<<endl;
	}
}


void consolaIU::cautare_iu()
{
	string titlu,an1;
	int an,ok=1;
	cout<<"Titlul filmului este:";
	getline(cin>>ws,titlu);
	cout<<"Anul in care filmul a fost lansat este:";
	getline(cin>>ws,an1);
	for (char const& c:an1)
	{
		if (std::isdigit(c)==0)
		{
			ok=0;
			break;
		}
	}
	if (ok==0)
		cout<<"Anul trebuie sa fie un NUMAR!"<<endl;
	else 
	{
		an=stoi(an1);
		try
		{
			Film film1=service.cauta_film(titlu,an);
			cout<<"Titlu: "<<film1.obtineTitlu()<<" | Gen: "<<film1.obtineGen()<<" | Actor principal: "<<film1.obtineActor()<<" | Anul aparitiei: "<<film1.obtineAn()<<endl;
		}
		catch(ExceptieRepozitoriu& er)
		{
			cout<<er.obtineMesajeEroare();
		}
	}
}



void consolaIU::filtrare_iu()
{
	int criteriu,an,ok=1;
	string titlu,an1;
	cout<<"Alegeti cifra corespunzatoare criteriului de filtrare:"<<endl;
	cout<<"1.Filtrare dupa titlu."<<endl;
	cout<<"2.Filtrare dupa anul aparitiei."<<endl;
	cout << "Criteriul dorit este: ";
	cin>>criteriu;
	if(criteriu==1)
	{
		cout<<"Titlul filmelor este:";
		getline(cin>>ws,titlu);
		auto lista_filme=service.filtreaza_dupa_Titlu(titlu);
		if (lista_filme.size()==0)
			cout<<"Lista nu contine niciun film cu proprietatea ceruta."<<endl;
		else
			for (int i=0; i<lista_filme.size(); i++)
			{
				Film film=lista_filme[i];
				cout<<"Titlu: "<<film.obtineTitlu()<<" | Gen: " << film.obtineGen()<<" | Actor principal: "<<film.obtineActor()<<" | Anul aparitiei: "<<film.obtineAn()<<endl;
			}
	}
	else if(criteriu==2)
	{
		cout<<"Anul de aparitie al filmelor este:";
		getline(cin>>ws,an1);
		for (char const& c:an1)
		{
			if (std::isdigit(c)==0)
			{
				ok=0;
				break;
			}
		}
		if (ok==0)
			cout<<"Anul trebuie sa fie un NUMAR!"<<endl;
		else 
		{
			an=stoi(an1);
			auto lista_filme=service.filtreaza_dupa_An(an);
			if (lista_filme.size()==0)
				cout<<"Lista nu contine niciun film cu proprietatea ceruta."<<endl;
			else
				for (int i=0; i<lista_filme.size(); i++)
				{
					Film film=lista_filme[i];
					cout<<"Titlu: "<<film.obtineTitlu()<<" | Gen: " << film.obtineGen()<<" | Actor principal: "<<film.obtineActor()<<" | Anul aparitiei: "<<film.obtineAn()<<endl;
				}
		}
	}
	else 
		cout<<"Criteriul ales nu este valid!"<<endl;
}


void consolaIU::sortare_iu()
{
	int criteriu;
	cout<<"Alegeti cifra corespunzatoare criteriului de sortare:\n";
	cout<<"1.Sortare dupa titlu.\n";
	cout<<"2.Sortare dupa actor principal.\n";
	cout<<"3.Sortare dupa anul aparitiei si dupa gen.\n";
	cout<<"Criteriul dorit este: ";
	cin>>criteriu;
	if(criteriu==1)
	{
		auto lista_filme=service.sorteaza_dupa_Titlu();
		if (lista_filme.size()==0)
			cout<<"Nu exista melodii."<<endl;
		else
			for (int i=0; i<lista_filme.size(); i++)
			{
				Film film=lista_filme[i];
				cout<<"Titlu: "<<film.obtineTitlu()<<" | Gen: "<<film.obtineGen()<<" | Actor principal: "<<film.obtineActor()<<" | Anul aparitiei: "<<film.obtineAn()<<endl;
			}
	}
	else if (criteriu==2)
	{
		auto lista_filme=service.sorteaza_dupa_Actor();
		if (lista_filme.size() ==0)
			cout<<"Nu exista melodii."<<endl;
		else
			for (int i=0; i<lista_filme.size(); i++)
			{
				Film film=lista_filme[i];
				cout<<"Titlu: "<<film.obtineTitlu()<<" | Gen: "<<film.obtineGen()<<" | Actor principal: "<<film.obtineActor()<<" | Anul aparitiei: "<<film.obtineAn()<<endl;
			}
	}
	else if(criteriu==3)
	{
		auto lista_filme = service.sorteaza_dupa_AnGen();
		if (lista_filme.size() ==0)
			cout<<"Nu exista melodii."<<endl;
		else
			for (int i=0; i<lista_filme.size(); i++)
			{
				Film film=lista_filme[i];
				cout<<"Titlu: "<<film.obtineTitlu()<<" | Gen: "<<film.obtineGen()<<" | Actor principal: "<<film.obtineActor()<<" | Anul aparitiei: "<<film.obtineAn()<<endl;
			}
	}
	else 
		cout<<"Criteriul ales nu este valid!"<<endl;
}



void consolaIU::rezultat_cerinta_lab()
{
	if(service.exista_film2022()==true)
		cout<<"Lista contine cel putin un film lansat in 2022."<<endl;
	else 
		cout<<"Lista nu contine niciun film lansat in 2022."<<endl;
}



void consolaIU::adaugare_in_cos_iu()
{
	size_t cnt_filme;
	auto filme=service.obtine_toate_filmele();
	if(filme.size()==0)
	{
		cout<<"Lista de filme este goala momentan!";
	}
	string titlu,an1;
	int an,ok=1;
	cout<<"Titlul filmului este:";
	getline(cin>>ws,titlu);
	cout<<"Anul in care filmul a fost lansat este:";
	getline(cin>>ws,an1);
	for (char const &c : an1) 
	{
        if(std::isdigit(c)==0) 
		{
			ok=0;
			break;
		}
    }
	if(ok==0)
		cout<<"Anul trebuie sa fie un NUMAR!"<<endl;
	else 
	{
		an=stoi(an1);
		try
		{
			service.adauga_film_in_cos(titlu,an);
			cnt_filme=service.obtine_marime_cos();
			cout<<"In cos se afla momentan "<<cnt_filme<<" filme."<<endl;
		}
		catch(ExceptieRepozitoriu& er)
		{
			cout<<er.obtineMesajeEroare();
		}
	}
}



void consolaIU::generare_cos_iu()
{
	int numar,ok=1;
	size_t cnt_filme;
	auto filme=service.obtine_toate_filmele();
	if(filme.size()==0)
	{
		cout<<"Lista de filme este goala momentan!";
	}
	string nr;
	cout<<"Introduceti numarul dorit: ";
	getline(cin>>ws,nr);
	for (char const &c : nr) 
	{
        if(std::isdigit(c)==0) 
		{
			ok=0;
			break;
		}
    }
	if(ok==0)
		cout<<"Trebuie sa introduceti un NUMAR pozitiv!"<<endl;
	else 
	{
		try
		{
			numar=stoi(nr);
			if(numar>filme.size())
			{
				cout<<"Numarul dorit depaseste lungimea listei!"<<endl;
				return;
			}
			service.genereaza_cos(numar);
			cnt_filme=service.obtine_marime_cos();
			cout<<"In cos se afla momentan "<<cnt_filme<<" filme."<<endl;
		}
		catch(ExceptieValidator& ev)
		{
			cout<<ev.obtine_mesaje_eroare();
		}
	}
}



void consolaIU::stergere_filme_iu()
{
	size_t cnt_filme;
	auto cos=service.obtine_toate_filmele_din_cos();
	if(cos.size()==0)
	{
		cout<<"Cosul este deja gol!"<<endl;
		return;
	}
	service.sterge_filmele_din_cos();
	cnt_filme=service.obtine_marime_cos();
	cout<<"In cos se afla momentan "<<cnt_filme<<" filme."<<endl;
}



void consolaIU::generare_filme_iu()
{
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
}





void consolaIU::ruleaza()
{
	int comanda,ok=1;
	generare_filme_iu();
	while(ok)
	{
		printareMeniu();
		cout<<"Introduceti o comanda:";
		cin>>comanda;
		switch(comanda)
		{
			case 1:
				printeaza_toate_filmele();
				break;
			case 2:
				adaugare_iu();
				break;
			case 3:
				actualizare_iu();
				break;
			case 4:
				stergere_iu();
				break;
			case 5:
				cautare_iu();
				break;
			case 6:
				filtrare_iu();
				break;
			case 7:
				sortare_iu();
				break;
			case 8:
				rezultat_cerinta_lab(); 
				break;
			case 9:
				undo_adauga_modifica_sterge();
				break;
			case 10:
				printeaza_toate_filmele_din_cos();
				break;
			case 11:
				adaugare_in_cos_iu();
				break;
			case 12:
				generare_cos_iu();
				break;
			case 13:
				printeaza_toate_filmele_csv();
				break;
			case 14:
				stergere_filme_iu();
				break;
			case 15:
				ok=0;
				break;
			default:
				break;
		}
	}
}