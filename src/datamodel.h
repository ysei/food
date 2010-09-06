#ifndef __DATAMODEL_H__
#define __DATAMODEL_H__

//FIXME seradit podle abecedy
#include <QStringList>
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QString>


class DataModel {
public:
	bool LoadFoodFromFile (QString fileName);
	bool SaveFoodIntoFile (QString fileName);
	int GetFoodAmount();
	QString GetFoodNameAtIndex (int index);
	QString GetFoodTypeAtIndex (int index);
	QString GetFoodIngredientsAtIndex (int index);
	QString GetFoodPreparationAtIndex (int index);
	int IndexOf (QString name);
	void AddNewFood (QStringList newFood);
	void RemoveFood (QString name);
	void EditFoodAtIndex (QStringList newFood, int index);
	QStringList GetFoodTypes();

private:
	QStringList food[4];
};

#endif
