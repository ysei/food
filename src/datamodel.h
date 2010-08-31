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
	QString GetFoodNameAtIndex (int pos);
	QString GetFoodTypeAtIndex (int pos);
	QString GetFoodIngredientsAtIndex (int pos);
	QString GetFoodPreparationAtIndex (int pos);
	int IndexOf (QString name);
	void AddNewFood (QStringList newFood);
	void RemoveFood (QString name);

private:
	QStringList food[4];
};

#endif
