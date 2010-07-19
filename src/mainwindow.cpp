#include <QListWidget>
#include <QString>

#include "mainwindow.h"
#include "datamodel.h"


MainWindow::MainWindow(QWidget *parent) {

	foodList = new QListWidget;

	setCentralWidget(foodList);

	foodInfo = new DataModel;

	QString foodDBName;
	foodDBName = "food.xml";
	foodInfo->loadFoodFromFile(foodDBName);

		
}
