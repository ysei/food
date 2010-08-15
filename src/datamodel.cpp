

#include "datamodel.h"


/*
 * nacte data z xml souboru
 */
bool DataModel::LoadFoodFromFile(QString fileName) {
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

/*
 * vrati pocet nactenych jidel
 */
int DataModel::GetFoodAmount() {
	return food[NAME].size();
}

/*
 * zjisti nazev jidla na pozici index
 */
QString DataModel::GetFoodNameAtIndex (int index) {
	return food[NAME][index];
}

/*
 * zjisti typ jidla na pozici index
 */
QString DataModel::GetFoodTypeAtIndex (int index) {
	return food[TYPE][index];
}

/*
 * zjisti slozeni jidla pozici index
 */
QString DataModel::GetFoodIngredientsAtIndex (int index) {
	return food[INGREDIENTS][index];
}

/*
 * zjisti pripravu jidla na pozici index
 */ 
QString DataModel::GetFoodPreparationAtIndex (int index) {
	return food[PREPARATION][index];
}

/*
 * vrati index jidla s nazvem name
 */
int DataModel::IndexOf (QString name) {
	return food[NAME].indexOf(name);
}
