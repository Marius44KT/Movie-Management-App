#pragma once
#include <QAbstractTableModel>
#include "Movie.h"
#include <vector>
#include <qdebug.h>

class MyTableModel :public QAbstractTableModel {
	std::vector<Film> filme;
public:
	MyTableModel(const std::vector<Film>& filme):filme{filme} {
	}


	int rowCount(const QModelIndex& parent=QModelIndex()) const override{
		return filme.size();
	}


	int columnCount(const QModelIndex& parent=QModelIndex()) const override {
		return 4;
	}


	QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override {
		if (role==Qt::DisplayRole) {
			Film film=filme[index.row()];
			if (index.column()==0) 
				return QString::fromStdString(film.obtineTitlu());
			else if (index.column()==1) 
				return QString::fromStdString(film.obtineGen());
			else if (index.column()==2) 
				return QString::fromStdString(film.obtineActor());
			else if (index.column()==3) 
				return QString::number(film.obtineAn());
		}
		return QVariant{};
	}


	void regenereaza_lista(const vector<Film>& movies) {
		this->filme=movies;
		auto topLeft=createIndex(0,0);
		auto bottomR=createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
		emit layoutChanged();
	}
};