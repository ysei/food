#include <QListWidget>

#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) {

	foodList = new QListWidget;

	setCentralWidget(foodList);

		
}
