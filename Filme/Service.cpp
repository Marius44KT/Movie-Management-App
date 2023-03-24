#pragma once 
#include "Service.h"
#include "Repository.h"
#include "Movie.h"
#include "Undo.h"
#include "validators.h"
#include "VectorDinamic.h"
#include <assert.h>
#include <functional>
#include <algorithm>


void StocareFilme::undo()
{
	//EROARE AICI
	if(undoActions.empty()==true)
		throw ExceptieUndo("Nu se mai poate efectua Undo!");
	else 
	{
		undoActions.back()->doUndo();
		undoActions.pop_back();
	}
}


bool StocareFilme::exista_film2022()
{
	return repozitoriu.exista2022();
}


const Film& StocareFilme::cauta_film(string titlu,int an)
{
	return repozitoriu.gaseste_film(titlu,an);
}



void StocareFilme::adauga_film(string titlu, string gen, string actor, int an)
{
	Film film1{titlu,gen,actor,an};
	validator.valideaza(film1);
	repozitoriu.adauga(film1);
	undoActions.push_back(std::make_unique<UndoAdauga>(repozitoriu,film1));
}



void StocareFilme::actualizeaza_film(string titlu,string gen, string actor, int an)
{
	Film film1=cauta_film(titlu,an);
	Film film2{titlu,gen,actor,an};
	validator.valideaza(film2);
	repozitoriu.actualizeaza(film2);
	undoActions.push_back(std::make_unique<UndoActualizeaza>(repozitoriu, film1));
}



void StocareFilme::sterge_film(string titlu, int an)
{
	Film film1=cauta_film(titlu,an);
	repozitoriu.sterge(titlu,an);
	undoActions.push_back(std::make_unique<UndoSterge>(repozitoriu,film1));
}




vector<Film> StocareFilme::filtreaza_dupa_Titlu(string titlu)
{
	return filtrare([titlu](const Film& film)
	{
		return film.obtineTitlu()==titlu;
	});
}



vector<Film> StocareFilme::filtreaza_dupa_An(int an)
{
	return filtrare([an](const Film& film)
		{
			return film.obtineAn()==an;
		});
}


vector<Film> StocareFilme::filtrare(function <bool(const Film&)> functie)
{
	vector<Film> v{repozitoriu.obtine_toate_filmele()};
	vector<Film> filme_filtrate;
	for (int i=0; i<v.size(); i++)
	{
		if (functie(v[i]))
			filme_filtrate.push_back(v[i]);
	}
	return filme_filtrate;
}


vector<Film> StocareFilme::sorteaza_dupa_Titlu()
{
	return sortareGenerala(cmpTitlu);
}



vector<Film> StocareFilme::sorteaza_dupa_Actor()
{
	return sortareGenerala(cmpActor);
}



vector<Film> StocareFilme::sorteaza_dupa_AnGen()
{
	return sortareGenerala(cmpAnGen);
}



vector<Film> StocareFilme::sortareGenerala(bool(*maiMicF)(const Film&, const Film&))
{
	vector<Film> v{ repozitoriu.obtine_toate_filmele() };
	for (int i=0; i<v.size(); i++)
	{
		for (int j=i+1; j<v.size(); j++)
		{
			if (!maiMicF(v[i],v[j]))
			{
				Film aux=v[i];
				v[i]=v[j];
				v[j]=aux;
			}
		}
	}
	return v;
}








void StocareFilme::adauga_film_in_cos(string titlu,int an)
{
	const auto& film=repozitoriu.gaseste_film(titlu,an);
	cos_cu_filme.adauga_film_in_cos(film);
}



void StocareFilme::genereaza_cos(int nr)
{
	cos_cu_filme.genereaza_cos(this->obtine_toate_filmele(),nr);
}



void StocareFilme::sterge_filmele_din_cos()
{
	cos_cu_filme.sterge_filmele_din_cos();
}



size_t StocareFilme::obtine_marime_cos()
{
	size_t numar=0;
	numar=cos_cu_filme.obtine_toate_filmele_din_cos().size();
	return numar;
}


void StocareFilme::exporta_CSV(string nume_fisier)
{
	int validare=0;
	validare=ValidatorFisier::valideaza(nume_fisier);
	if(validare==1)
		cos_cu_filme.exporta_fisier_CSV(nume_fisier);
}