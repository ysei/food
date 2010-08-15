#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H_


//FIXME seradit podle abecedy
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
#include <QRect>
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>
#include <QStatusBar>

#include <cstdlib> 
#include <ctime> 

#include "datamodel.h"
#include "config.h"

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
	QHBoxLayout *boxLayout;
	QGroupBox *horizontalGroupBox;
	DataModel *foodInfo;
	QTextDocument *displayedFoodInfo;
	QToolBar *toolBar;

	Configuration config;

	void CreateActions();
	void CreateLayout();
	void DisplayInfoAtIndex(int index);
	int GenerateRandomNumber();
	
	QAction *quitAction;
	QAction *addFoodAction;
	QAction *removeFoodAction;
	QAction *chooseRandomFoodAction;

private slots:
	void Quit();
	void ItemSelected(QListWidgetItem *item);
	void AddFood();
	void RemoveFood();
	void ChooseRandomFood();
};


#endif
