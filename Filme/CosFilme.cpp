#include "CosFilme.h"
using std::shuffle;
#include <exception>
#include <iostream>
#include <fstream>
using namespace std;


void CosFilme::adauga_film_in_cos(const Film& film)
{
	this->cos_filme.push_back(film);
}



void CosFilme::sterge_filmele_din_cos()
{
	this->cos_filme.clear();
}



void CosFilme::genereaza_cos(vector <Film> filmeOriginale, int nr)
{
	/*
	shuffle(filmeOriginale.begin(), filmeOriginale.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	while (cos_filme.size()<nr && filmeOriginale.size()>0)
	{
		cos_filme.push_back(filmeOriginale.back());
		filmeOriginale.pop_back();
	}
	*/
	vector<Film> copie(filmeOriginale.size());
	int numar_random;
	copy(filmeOriginale.begin(), filmeOriginale.end(), copie.begin());
	for (int i = 0; i < nr; i++)
	{
		//facem o copie a vectorului de produse si o amestecam de nr ori
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(copie.begin(), copie.end(), std::default_random_engine(int(seed))); //amesteca vectorul
		// generam o pozitie random cuprinsa intre 0 si lungimea copiei - 1
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, int(copie.size() - 1));
		numar_random = dist(mt);
		//adaugam in cos un film cu indice random
		this->cos_filme.push_back(copie[numar_random]);
	}
}


vector<Film>& CosFilme::obtine_toate_filmele_din_cos()
{
	return this->cos_filme;
}


void CosFilme::exporta_fisier_CSV(string nume_fisier)
{
	//cout<<nume_fisier<<endl;
	std::ofstream out(nume_fisier);
	out << "Titlu,Gen,Actor principal,Anul aparitiei" << endl;
	for (auto film : this->cos_filme)
		out << film.obtineTitlu() << "," << film.obtineGen() << "," << film.obtineActor() << "," << film.obtineAn() << endl;
	out.close();
}