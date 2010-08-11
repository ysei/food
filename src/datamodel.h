#ifndef __DATAMODEL_H__
#define __DATAMODEL_H__

#include <QStringList>
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
	bool loadFoodFromFile(QString fileName);
	int getFoodAmount();
	QString getFoodNameAtPos (int pos);
	QString getFoodTypeAtPos (int pos);
	QString getFoodIngredientsAtPos (int pos);
	QString getFoodPreparationAtPos (int pos);

private:
	QStringList food[4];
};

#endif
