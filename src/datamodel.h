#ifndef __DATAMODEL_H__
#define __DATAMODEL_H__

#include <QStringList>
#include <QString>

enum INFO {
	infoFirst = 0,
	name = 0,
	type = 1,
	ingredients = 2,
	preparation = 3,
	infoLast = 3
};

class DataModel {
public:
	void loadFoodFromFile(QString fileName);

private:
	QStringList food[4];
};

#endif
