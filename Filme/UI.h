#pragma once 
#include "Service.h"
class consolaIU
{
private:
	StocareFilme& service;
public:
	consolaIU(StocareFilme& service) :service{ service } {};
	consolaIU(const consolaIU& ot) = delete;
	void printareMeniu();
	void undo_adauga_modifica_sterge();
	void printeaza_toate_filmele_csv();
	void printeaza_toate_filmele();
	void printeaza_toate_filmele_din_cos();
	void adaugare_iu();
	void actualizare_iu();
	void stergere_iu();
	void cautare_iu();
	void filtrare_iu();
	void sortare_iu();
	void rezultat_cerinta_lab();
	void generare_filme_iu();

	void adaugare_in_cos_iu();
	void generare_cos_iu();
	void stergere_filme_iu();
	void ruleaza();
};