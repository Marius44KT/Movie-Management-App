#pragma once 
#include "validators.h"
#include "Repository.h"
#include "Undo.h"
#include "VectorDinamic.h"
#include "CosFilme.h"
#include <functional>
using std::function;
using std::unique_ptr;


class ExceptieUndo {
	string msg;
public:
	ExceptieUndo(const string& m) :msg{ m } {};
	string getMsg()const { return msg; }
};


class StocareFilme
{
private:
	RepozitoriuFilme& repozitoriu;
	//CosFilme& cos_cu_filme;
	CosFilme cos_cu_filme;
	ValidatorFilm& validator;


	vector <unique_ptr<ActiuneUndo>> undoActions;
	vector<Film> filtrare(function<bool(const Film&)> functie);
public:
	StocareFilme(RepozitoriuFilme& repoFilm, CosFilme& cos, ValidatorFilm& val) :repozitoriu{ repoFilm }, cos_cu_filme{ cos }, validator{ val }{};

	//constructor de copiere
	StocareFilme(const StocareFilme& ot) = delete;


	CosFilme& get_program() {
		return this->cos_cu_filme;
	}

	void undo();

	/*
	Adauga un film cu titlul-titlu, genul-gen, actorul-actor si anul_aparitiei-an
	*@param titlu: titlul filmului care se adauga(string)
	*@param an: anul aparitiei pentru filmul care se adauga(int)
	*
	*@throws:
	*ExceptieRepozitoriu daca mai exista un alt film cu acelasi titlu si an al aparitiei
	*/
	const Film& cauta_film(string titlu, int an);



	/*
	Adauga un film cu titlul-titlu, genul-gen, actorul-actor si anul_aparitiei-an
	*@param titlu: titlul filmului care se adauga(string)
	*@param gen: genul filmului pe care dorim sa il adaugam(string)
	*@param actor:actorul principal al filmului care se adauga (string)
	*@param an: anul aparitiei pentru filmul care se adauga(int)
	*
	* @throws:
	*ExceptieRepozitoriu daca mai exista un alt film cu acelasi titlu si an al aparitiei
	*ValidationException daca filmul introdus nu este valid
	*/
	void adauga_film(string titlu, string gen, string actor, int an);




	/*
	Actualizeaza un film cu titlul-titlu, genul-gen, actorul-actor si anul_aparitiei-an
	*@param titlu: titlul filmului care se actualizeaza(string)
	*@param gen: genul filmului pe care dorim sa il actualizam(string)
	*@param actor:actorul principal al filmului pe care il actualizam(string)
	*@param an: anul aparitiei pentru filmul pe care il actualizam(int)
	*
	* @throws:
	*ExceptieRepozitoriu daca nu exista un alt film cu acelasi titlu si an al aparitiei
	*ValidationException daca filmul introdus nu este valid
	*/
	void actualizeaza_film(string titlu, string gen, string actor, int an);



	/*
	Sterge un film cu titlul-titlu, genul-gen, actorul-actor si anul_aparitiei-an
	*@param titlu: titlul filmului care se sterge(string)
	*@param an: anul aparitiei pentru filmul pe care il stergem(int)
	*
	* @throws:
	*ExceptieRepozitoriu daca nu exista un alt film cu acelasi titlu si an al aparitiei
	*/
	void sterge_film(string titlu, int an);

	/*
	Filtreaza filmele dupa un anumit titlu dat de la tastatura
	*@param titlu: titlul filmului(string)
	* @throws:-
	*/
	vector<Film> filtreaza_dupa_Titlu(string titlu);

	/*
	Filtreaza filmele dupa un anumit an dat de la tastatura
	*@param titlu: anul filmului(int)
	* @throws:-
	*/
	vector<Film> filtreaza_dupa_An(int an);

	vector<Film> sortareGenerala(bool(*maiMicF)(const Film&, const Film&));

	/*
	Sorteaza crescator filmele dupa titlu
	*@param-
	*@throws:-
	*/
	vector<Film> sorteaza_dupa_Titlu();

	/*
	Sorteaza crescator filmele dupa actor
	*@param-
	*@throws:-
	*/
	vector<Film> sorteaza_dupa_Actor();

	/*
	Sorteaza crescator filmele dupa an,daca anii sunt egali, atunci dupa gen
	*@param-
	*@throws:-
	*/
	vector<Film> sorteaza_dupa_AnGen();


	vector<Film>& obtine_toate_filmele()
	{
		return this->repozitoriu.obtine_toate_filmele();
	}

	//verifica daca in lista se afla un film aparut in anul 2022
	bool exista_film2022();

	/*
	Adauga un film cu titlul-titlu, genul-gen, actorul-actor si anul_aparitiei-an
	*@param titlu: titlul filmului care se adauga(string)
	*@param gen: genul filmului pe care dorim sa il adaugam(string)
	*@param actor:actorul principal al filmului care se adauga (string)
	*@param an: anul aparitiei pentru filmul care se adauga(int)
	*
	* @throws:
	*ExceptieRepozitoriu daca mai exista un alt film cu acelasi titlu si an al aparitiei
	*ValidationException daca filmul introdus nu este valid
	*/
	void adauga_film_in_cos(string titlu, int an);


	/*
	Extrage
	*@param: nr-numarul de filme pe care le extragem din lista si le punem in cos
	*@throws: exceptie daca vreau sa extrag din lista mai multe filme decat exista
	*/
	void genereaza_cos(int nr);


	/*
	Sterge toate filmele din cos
	*@param: -
	*@throws:-
	*ExceptieRepozitoriu daca cosul e deja gol
	*/
	void sterge_filmele_din_cos();

	/*
	Returneaza filmele care se afla in cos
	*@param: -
	*@throws:-
	*ExceptieRepozitoriu daca cosul e gol
	*/
	vector<Film>& obtine_toate_filmele_din_cos()
	{
		return this->cos_cu_filme.obtine_toate_filmele_din_cos();
	}

	/*
	Returneaza numarul de filme din cos
	*@param: -
	*@throws:-
	*/
	size_t obtine_marime_cos();

	void exporta_CSV(string nume_fisier);
};
