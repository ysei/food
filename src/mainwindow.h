#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H_

#include <QMainWindow>

#include "datamodel.h"

class QListWidget;

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

private:
	QListWidget *foodList;
	DataModel *foodInfo;
	
};

#endif
