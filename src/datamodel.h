#ifndef __DATAMODEL_H__
#define __DATAMODEL_H__

//FIXME seradit podle abecedy
#include <QStringList>
#include <QDebug>
#include <QXmlStreamReader>
#include <QFile>
#include <QString>

enum INFO {
	infoFirst = 0,
	NAME = 0,
	TYPE = 1,
	INGREDIENTS = 2,
	PREPARATION = 3,
	infoLast = 3
};

class DataModel {
public:
	bool LoadFoodFromFile(QString fileName);
	int GetFoodAmount();
	QString GetFoodNameAtIndex (int pos);
	QString GetFoodTypeAtIndex (int pos);
	QString GetFoodIngredientsAtIndex (int pos);
	QString GetFoodPreparationAtIndex (int pos);
	int IndexOf (QString name);

private:
	QStringList food[4];
};

#endif
