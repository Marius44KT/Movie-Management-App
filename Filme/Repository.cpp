#include "Repository.h"
#include <assert.h>


bool RepozitoriuFilme::exista2022()
{
	bool result=std::any_of(this->filme.begin(), this->filme.end(),[&](const Film& f) { return f.obtineAn()==2022; });
	return result;
}



bool RepozitoriuFilme::exista(const Film& film)
{
	try 
	{
		gaseste_film(film.obtineTitlu(),film.obtineAn());
		return true;
	}
	catch(ExceptieRepozitoriu)
	{
		return false; } 
}



const Film& RepozitoriuFilme::gaseste_film(string titlu,int an) 
{
	auto iterator=std::find_if(this->filme.begin(),this->filme.end(),[titlu,an](Film film)
	{
		if(film.obtineTitlu()==titlu && film.obtineAn()==an)
			return true;
		return false;
	});
	if(iterator==this->filme.end())
		throw ExceptieRepozitoriu("Filmul cu titlul " + titlu + " si anul de aparitie introdus nu exista in lista!\n");
	return *iterator;}
/*
	for(auto &film:filme)
		if(film.obtineTitlu()==titlu && film.obtineAn()==an)
		{
			return film;
		}
	throw ExceptieRepozitoriu("Filmul cu titlul "+titlu+" si anul de aparitie introdus nu exista in lista!\n"); } 
*/



void RepozitoriuFilme::adauga(const Film& film)
{
	if(exista(film))
	{
		throw ExceptieRepozitoriu("Filmul cu titlul "+film.obtineTitlu()+" si anul de aparitie introdus exista deja in lista!\n");
	}
	this->filme.push_back(film);
}



void RepozitoriuFilme::actualizeaza(const Film& film)
{
	if (exista(film))
	{
	for (auto& movie : filme)
		if (movie.obtineTitlu() == film.obtineTitlu() && movie.obtineAn() == film.obtineAn())
		{
			movie = film;
			break;}}
	else
		throw ExceptieRepozitoriu("Filmul cu titlul " + film.obtineTitlu() + " si anul de aparitie introdus nu exista in lista!\n");
}



void RepozitoriuFilme::sterge(string titlu, int an) 
{
	auto iterator=std::remove_if(this->filme.begin(), this->filme.end(), [titlu, an](Film film) {
		if (film.obtineTitlu()==titlu && film.obtineAn()==an)
			return true;
		return false;
		});
	if (iterator==this->filme.end())
		throw ExceptieRepozitoriu("Filmul cu titlul " + titlu + " si anul de aparitie introdus nu exista in lista!\n");
	this->filme.erase(iterator, this->filme.end());}




vector<Film>& RepozitoriuFilme::obtine_toate_filmele()
{
	return this->filme;
}

