#ifndef __CONFIG_H__
#define __CONFIG_H__

//FIXME seradit podle abecedy
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QString>
#include <QStringList>

#include <QDebug>

class Configuration {
	public:
		Configuration();
		QString GetDBFileName();
		bool LoadConfiguration();
		bool SaveConfiguration();
		void GetWindowGeometry(int &_x, int &_y, int &_width, int &_height);
		void SetWindowGeometry(int _x, int _y, int _width, int _height);

	private:
		QString configurationFileName;
		QString DBFileName;
		int x;
		int y;
		int width;
		int height;
};

#endif
