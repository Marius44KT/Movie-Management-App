#pragma once 
#include <iostream>
#include <vector>
#include <string>
#include "Movie.h"
using std::string;
using std::vector;
class ExceptieValidator
{
	vector <string> mesajEroare;
public:
	ExceptieValidator(vector <string> mesajeEroare):mesajEroare{mesajeEroare}{};
	string obtine_mesaje_eroare()
	{
		string mesaje="";
		for(const string msj: mesajEroare)
			mesaje=mesaje+msj+"\n";
		return mesaje;
	}
};




class ValidatorFilm
{
public:
	void valideaza(const Film& film)
	{
		vector <string> erori;
		if(film.obtineTitlu().length()<3)
			erori.push_back("Titlul filmului trebuie sa aiba cel putin 3 caractere.");
		if(film.obtineGen().length()<3)
			erori.push_back("Genul filmului trebuie sa aiba cel putin 3 caractere.");
		if(film.obtineActor().length()<3)
			erori.push_back("Numele actorului principal trebuie sa aiba cel putin 3 caractere.");
		if(film.obtineAn()<1900 || film.obtineAn()>2022)
			erori.push_back("Filmul nu apartine intervalului de timp corespunzator(1900-2022).");

		if(erori.size()>0)
			throw ExceptieValidator(erori);
	}
};




class ValidatorFisier{
public:
	static int valideaza(string nume_fisier)
	{
		vector <string> erori;
		int lungime=static_cast<int>(nume_fisier.size());
		int rezultat=0;
		if(lungime<4)
			erori.push_back("Numele fisierului trebuie sa aiba cel putin 4 caractere.");
		else 
		{
			string extensie=".csv";
			bool fisier_csv=true;
			size_t index_str;
			if((index_str=nume_fisier.find(extensie,0))!=string::npos)
			{
				if(static_cast<int>(index_str)+1!=lungime-3) fisier_csv=false;
			}
			else 
				fisier_csv=false;
			if(fisier_csv==false)
				erori.push_back("Numele fisierului nu are extensia csv.");
			else if(fisier_csv==true)
				rezultat=1;
		}
		if(erori.size()>0)
			throw ExceptieValidator(erori);
		return rezultat;
	}
};
