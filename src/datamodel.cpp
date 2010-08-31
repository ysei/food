

#include "datamodel.h"
#include "enum.h"


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
 * verejna metoda
 * ulozi jidla do xml souboru
 */
bool DataModel::SaveFoodIntoFile (QString fileName) {
	QFile file(fileName);

	if (!file.open(QIODevice::WriteOnly)) {
		return false;
	}
	
	QXmlStreamWriter stream(&file);
	stream.setAutoFormatting(true);
	stream.writeStartDocument();
	stream.writeStartElement("root");
	for (int i = 0; i < this->GetFoodAmount(); i++) {
		stream.writeStartElement("item");

		stream.writeStartElement("name");
		stream.writeCharacters(food[NAME][i]);
		stream.writeEndElement();

		stream.writeStartElement("type");
		stream.writeCharacters(food[TYPE][i]);
		stream.writeEndElement();

		stream.writeStartElement("ingredients");
		stream.writeCharacters(food[INGREDIENTS][i]);
		stream.writeEndElement();

		stream.writeStartElement("preparation");
		stream.writeCharacters(food[PREPARATION][i]);
		stream.writeEndElement();

		stream.writeEndElement();
	}
	stream.writeEndElement();
	stream.writeEndDocument();

	file.close();
	qDebug() << "zkurvene statnice";
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

/*
 * verejna metoda pro pridani noveho jidla
 */
void DataModel::AddNewFood (QStringList newFood) {
	food[NAME].append(newFood[NAME]);
	food[TYPE].append(newFood[TYPE]);
	food[INGREDIENTS].append(newFood[INGREDIENTS]);
	food[PREPARATION].append(newFood[PREPARATION]);
	qDebug() << "pridavam nove jidlo";
}

/*
 * verejna metoda pro odebrani jidla
 */
void DataModel::RemoveFood (QString name) {
	int index;
	index = food[NAME].indexOf(name);
	food[NAME].removeAt(index);
	food[TYPE].removeAt(index);
	food[INGREDIENTS].removeAt(index);
	food[PREPARATION].removeAt(index);
}

