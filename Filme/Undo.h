#pragma once
#include "Movie.h"
#include "Repository.h"


class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo()=default;
};



class UndoAdauga :public ActiuneUndo {
	Film filmAdaugat;
	RepozitoriuFilme& rep;
public:
	UndoAdauga(RepozitoriuFilme& rep, const Film& f) :rep{rep}, filmAdaugat{f}{}
	void doUndo() override {
		rep.sterge_undo(filmAdaugat.obtineTitlu(), filmAdaugat.obtineAn());
	}
};



class UndoActualizeaza:public ActiuneUndo {
	Film filmActualizat;
	RepozitoriuFilme& rep;
public:
	UndoActualizeaza(RepozitoriuFilme& rep, const Film& f) :rep{rep}, filmActualizat{f}{}
	void doUndo() override {
		rep.actualizeaza_undo(filmActualizat);
	}
};



class UndoSterge :public ActiuneUndo {
	Film filmSters;
	RepozitoriuFilme& rep;
public:
	UndoSterge(RepozitoriuFilme& rep, const Film& f) :rep{rep}, filmSters{f}{}
	void doUndo() override {
		rep.adauga_undo(filmSters);
	}
};