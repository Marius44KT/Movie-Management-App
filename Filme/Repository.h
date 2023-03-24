#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <chrono>
#include "Movie.h"
#include "VectorDinamic.h"
using std::default_random_engine;
using std::chrono::system_clock;
using std::vector;
using std::string;
using std::copy;
using std::find_if;
using std::find;
using std::any_of;

//Clasa de exceptii specifice Repozitoriului
class ExceptieRepozitoriu
{
private:
	string mesajEroare;
public:
	ExceptieRepozitoriu(string mesajEroare): mesajEroare{mesajEroare}{};
	string obtineMesajeEroare()
	{
		return this->mesajEroare;
	}
};


class RepozitoriuFilme
{
private:
	vector <Film> filme;
public:
	RepozitoriuFilme()=default;
	//constructorul de copiere
	RepozitoriuFilme(const RepozitoriuFilme& ot)=delete;
	virtual ~RepozitoriuFilme()=default;

	/*
	Verifica daca lista contine cel putin un film care a aparut in anul 2022
	@param:-
	@returns:true daca cel putin un film a aparut in 2022, false in caz contrar
	*/
	bool exista2022();



	/*
	Verifica daca un anumit film exista in lista

	@param s: filmul care se cauta in lista
	@return: true daca filmul exista, false altfel
	*/
	bool exista(const Film& film);


	/*
	Cauta un film cu titlul si anul de aparitie dat

	@param titlu: titlul dupa care se cauta
	@param an: anul de aparitie dupa care se cauta
	@returns: entitatea Film cu titlul si anul dat (daca aceasta exista)
	@throws: ExceptieRepozitoriu daca nu exista film cu titlul si anul dat
	*/
	const Film& gaseste_film(string titlu,int an);



	/*
	Adauga un film in lista
	@param film: filmul care se adauga(Film)
	@return -
	post: filmul va fi adaugat in lista
	@throws: ExceptieRepozitoriu daca o un film cu acelasi titlu si acelasi an de aparitie
			 exista deja
	*/
	void adauga(const Film& film);



	/*
	Actualizeaza un film din lista
	@param film: filmul care se actualizeaza(Film)
	@return -
	post: filmul din lista va fi actualizat
	@throws: ExceptieRepozitoriu daca nu exista un film cu acelasi titlu si acelasi an de aparitie
	*/
	void actualizeaza(const Film& film);



	/*
	Sterge un film din lista
	@param film: filmul care se sterge(Film)
	@return -
	post: filmul din lista va fi sters
	@throws: ExceptieRepozitoriu daca nu exista un film cu acelasi titlu si acelasi an de aparitie
	*/
	void sterge(string titlu,int an);

	/*
	Returneaza o lista cu toate filmele
	@return: lista cu filmele (vector de obiecte Film)
	*/
	vector<Film>& obtine_toate_filmele();



	virtual void sterge_undo(string titlu, int an) {
		auto iterator = std::remove_if(this->filme.begin(), this->filme.end(), [titlu, an](Film film) {
			if (film.obtineTitlu() == titlu && film.obtineAn() == an)
				return true;
			return false;
			});
		if (iterator == this->filme.end())
			throw ExceptieRepozitoriu("Filmul cu titlul " + titlu + " si anul de aparitie introdus nu exista in lista!\n");
		this->filme.erase(iterator, this->filme.end());
	}



	virtual void actualizeaza_undo(const Film& film) {
		if (exista(film))
		{
		for (auto& movie:filme)
			if (movie.obtineTitlu() == film.obtineTitlu() && movie.obtineAn() == film.obtineAn())
			{
				movie=film;
				break;}}
		else throw ExceptieRepozitoriu("Filmul cu titlul " + film.obtineTitlu() + " si anul de aparitie introdus nu exista in lista!\n");
	}



	virtual void adauga_undo(const Film& film) {
		if (exista(film))
		{
			throw ExceptieRepozitoriu("Filmul cu titlul " + film.obtineTitlu() + " si anul de aparitie introdus exista deja in lista!\n");
		}
		this->filme.push_back(film);
	}
};

