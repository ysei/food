
#include <QDebug>
#include <QXmlStreamReader>
#include <QFile>
#include <QString>

#include "datamodel.h"


//FIXME TODO vytvorit xml soubor s daty, napsat jeho nacitani
bool DataModel::loadFoodFromFile(QString fileName) {
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return false;
	}

	QXmlStreamReader xml(&file);
	QXmlStreamReader::TokenType token;

	do {
		token = xml.readNext();
		if (token == QXmlStreamReader::StartElement) {
			QString elementName = xml.name().toString();
			token = xml.readNext();
			if (elementName == "name") {
				food[NAME].append(xml.text().toString());
			}
			if (elementName == "type") {
				food[TYPE].append(xml.text().toString());
			}
			if (elementName == "ingredients") {
				food[INGREDIENTS].append(xml.text().toString());
			}
			if (elementName == "preparation") {
				food[PREPARATION].append(xml.text().toString());
			}
		}
	} while (!(xml.atEnd()));

/* FIXME do pryc s timhle
	for (int i = 0; i < food[NAME].size(); i++) {
		qDebug() << food[NAME][i];
		qDebug() << food[TYPE][i];
		qDebug() << food[INGREDIENTS][i];
		qDebug() << food[PREPARATION][i];
		qDebug() << " ";
	}
*/
	file.close();
	return true;
}

int DataModel::getFoodAmount() {
	return food[NAME].size();
}

QString DataModel::getFoodNameAtPos (int pos) {
	return food[NAME][pos];
}
