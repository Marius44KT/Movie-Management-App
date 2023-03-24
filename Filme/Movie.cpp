#include "Movie.h"
#include <assert.h>
#include <iostream>
#include <string.h>



string Film::obtineTitlu() const 
{
	return this->titlu;
}



string Film::obtineGen() const 
{
	return this->gen;
}



string Film::obtineActor() const 
{
	return this->actor_principal;
}



int Film::obtineAn() const 
{
	return this->an_aparitie;
}



void Film::atribuieTitlu(string titluNou)
{
	this->titlu=titluNou;
}



void Film::atribuieGen(string genNou)
{
	this->gen=genNou;
}



void Film::atribuieActor(string actorNou)
{
	this->actor_principal=actorNou;
}



void Film::atribuieAn(int anNou)
{
	this->an_aparitie=anNou;
}



bool cmpTitlu(const Film& film1,const Film& film2)
{
	return film1.obtineTitlu()<film2.obtineTitlu();
}



bool cmpActor(const Film& film1, const Film& film2)
{
	return film1.obtineActor()<film2.obtineActor();
}



bool cmpAnGen(const Film& film1, const Film& film2)
{
	if(film1.obtineAn()==film2.obtineAn())
		return (film1.obtineGen()<film2.obtineGen());
	return film1.obtineAn()<film2.obtineAn();
}


