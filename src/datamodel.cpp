
#include <QDebug>
#include <QXmlStreamReader>
#include <QFile>

#include "datamodel.h"


//FIXME TODO vytvorit xml soubor s daty, napsat jeho nacitani
void DataModel::loadFoodFromFile(QString fileName) {
	QFile file(fileName);

	if (!file.open()(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}
	qDebug() << "ahoj";
	file.close();
}
