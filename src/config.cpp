#include "config.h"

Configuration::Configuration() : x(0), y(0), width(400), height(300) {
}

bool Configuration::LoadConfiguration(QString fileName) {
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return false;
	}
	
	//prirazovat hodnotu do teto promenne pouze pokud se podari soubor otevrit
	configurationFileName = fileName;
	
	QXmlStreamReader xml(&file);
	QXmlStreamReader::TokenType token;

	do {
		token = xml.readNext();
		if (token == QXmlStreamReader::StartElement) {
			QString elementName = xml.name().toString();
			token = xml.readNext();
			if (elementName == "windowGeometry") {
				QString readValue = xml.text().toString();
				if (!readValue.isEmpty()) {
					QStringList tmpStringList;
					tmpStringList = readValue.split(" ");
					x = tmpStringList[0].toInt();
					y = tmpStringList[1].toInt();
					width = tmpStringList[2].toInt();
					height = tmpStringList[3].toInt();
				}
			}
			if (elementName == "foodDB") {
				DBFileName = xml.text().toString();
			}
		}
	} while (!(xml.atEnd()));


	file.close();
	return true;
}

bool Configuration::SaveConfiguration() {
	QFile file(configurationFileName);

	if (!file.open(QIODevice::WriteOnly)) {
		return false;
	}

	QXmlStreamWriter stream(&file);
	stream.setAutoFormatting(true);
	stream.writeStartDocument();
	stream.writeStartElement("configuration");
		QString windowGeometry;
		windowGeometry = QString::number(x) + " " + QString::number(y) + " " + QString::number(width) + " " + QString::number(height);
		stream.writeTextElement("windowGeometry", windowGeometry);
		//stream.writeTextElement("windowGeometry", QString(QString::number(x)));
		stream.writeTextElement("foodDB", DBFileName);
	stream.writeEndElement();
	stream.writeEndDocument();

	file.close();
	return true;
}

QString Configuration::GetDBFileName() {
	return DBFileName;
}

void Configuration::GetWindowGeometry(int &_x, int &_y, int &_width, int &_height) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}

void Configuration::SetWindowGeometry(int _x, int _y, int _width, int _height) {
	x = _x;
	y = _y;
	width = _width;
	height = _height;
}
