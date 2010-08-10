#include <QListWidget>
#include <QString>

#include <QDebug>

#include "mainwindow.h"
#include "datamodel.h"


MainWindow::MainWindow(QWidget *parent) {
	CreateLayout();
	foodList = new QListWidget;
	foodList->setSortingEnabled(1);

	setCentralWidget(foodList);

	foodInfo = new DataModel;

	QString foodDBName;
	foodDBName = "data.xml";
	foodInfo->loadFoodFromFile(foodDBName);

	for (int i = 0; i < foodInfo->getFoodAmount(); i++) {
		foodList->insertItem(i + 1, foodInfo->getFoodNameAtPos(i));
	}
}

void MainWindow::CreateLayout() {
	qDebug() << "vytvarim layout";
}
