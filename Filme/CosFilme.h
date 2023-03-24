#pragma once
#include "Movie.h"
#include "Observer.h"
#include <vector>
#include <algorithm>
#include <random> 
#include <chrono>   

class CosFilme :public Observable
{
private:
	vector <Film> cos_filme;
public:
	CosFilme() = default;
	//constructorul de copiere
	//CosFilme(const CosFilme& ot)=delete;
	//virtual ~CosFilme()=default;
	friend class RepozitoriuFilme;
	/*
	Adauga un film in cos
	@param film: filmul care se adauga(Film)
	@return -
	post: filmul va fi adaugat in cos
	*/
	void adauga_film_in_cos(const Film& film);


	/*
	Genereaza un cos cu nr filme de inchiriat
	@param nr:numarul de filme pe care vreau sa le preiau din lista
	@return -
	post: cosul va fi actualizat
	*/
	void genereaza_cos(vector<Film> filmeOriginale, int nr);


	/*
	Sterge toate filmele din cos
	@param -
	@return -
	post: filmele din cos vor fi sterse
	@throws: ExceptieRepozitoriu daca cosul e deja gol
	*/
	void sterge_filmele_din_cos();


	vector<Film>& obtine_toate_filmele_din_cos();

	void exporta_fisier_CSV(string nume_fisier);
};