#pragma once 
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

class Film
{
private:
	string titlu;
	string gen;
	string actor_principal;
	int an_aparitie;
public:
	Film() = default;
	Film(string titlu, string gen, string actor_principal, int an_aparitie) : titlu{ titlu }, gen{ gen }, actor_principal{ actor_principal }, an_aparitie{ an_aparitie }{};
	Film(const Film& ot) :titlu{ ot.titlu }, gen{ ot.gen }, actor_principal{ ot.actor_principal }, an_aparitie{ ot.an_aparitie }
	{
		//cout << "[FILM] Constructorul de copiere a fost apelat." << endl;
	}
	string obtineTitlu() const;
	string obtineGen() const;
	string obtineActor() const;
	int obtineAn() const;

	void atribuieTitlu(string titluNou);
	void atribuieGen(string genNou);
	void atribuieActor(string actorNou);
	void atribuieAn(int anNou);
};
//IN AFARA CLASEI
bool cmpTitlu(const Film& film1, const Film& film2);
bool cmpActor(const Film& film1, const Film& film2);
bool cmpAnGen(const Film& film1, const Film& film2);

void testeDomeniu();