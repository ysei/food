#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H_

#include <QMainWindow>
#include <QListWidget>
#include <QString>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QTextDocument>
#include <QMenuBar>
#include <QAction>
#include <QApplication>

#include <cstdlib> 
#include <ctime> 

#include "datamodel.h"

class QListWidget;

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	QListWidget *foodList;
	QTextEdit *foodDetail;
	QMenuBar *menuBar;
	QMenu *fileMenu;
	QAction *quitAction;
	QHBoxLayout *boxLayout;
	QGroupBox *horizontalGroupBox;
	DataModel *foodInfo;
	QTextDocument *displayedFoodInfo;

	void CreateActions();
	void CreateLayout();
	

private slots:
	void quit(void);
	
};

#endif
