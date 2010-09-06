

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

	int namesAmount;
	int typesAmount;
	int ingredientsAmount;
	int preparationAmount;
	namesAmount = food[NAME].count();
	typesAmount = food[TYPE].count();
	ingredientsAmount = food[INGREDIENTS].count();
	preparationAmount = food[PREPARATION].count();


	//jednoducha kontrola, jestli nechybi nejaka polozka, vseho musi byt nacteno stejne
	//pokud se v teto fazi zjisti chyba, je potreba vsecky dosud ulozene informace zahodit
	//FIXME neresi urcite pripady, zamysli se nad tim, zda-li ma cenu detekovat slozitejsi chyby
	if ((namesAmount != typesAmount) || (namesAmount != ingredientsAmount) || (namesAmount != preparationAmount)) {
		food[NAME].erase(food[NAME].begin(), food[NAME].end());
		food[TYPE].erase(food[TYPE].begin(), food[TYPE].end());
		food[INGREDIENTS].erase(food[INGREDIENTS].begin(), food[INGREDIENTS].end());
		food[PREPARATION].erase(food[PREPARATION].begin(), food[PREPARATION].end());
		return false;
	}

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

		//</item>
		stream.writeEndElement();
	}

	//</root>
	stream.writeEndElement();
	stream.writeEndDocument();

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

/*
 * verejna metoda pro pridani noveho jidla
 */
void DataModel::AddNewFood (QStringList newFood) {
	food[NAME].append(newFood[NAME]);
	food[TYPE].append(newFood[TYPE]);
	food[INGREDIENTS].append(newFood[INGREDIENTS]);
	food[PREPARATION].append(newFood[PREPARATION]);
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


/*
 * verejna metoda pro zmenu informaci o jidle
 */
void DataModel::EditFoodAtIndex (QStringList newFood, int index) {
	food[NAME][index] = newFood[NAME];
	food[TYPE][index] = newFood[TYPE];
	food[INGREDIENTS][index] = newFood[INGREDIENTS];
	food[PREPARATION][index] = newFood[PREPARATION];
	
}

/*
 * verejna metoda pro zjisteni vsech typu jidla
 */
QStringList DataModel::GetFoodTypes() {
	QStringList foodTypes;
	foodTypes = food[TYPE];
	foodTypes.removeDuplicates();
	return foodTypes;
}
