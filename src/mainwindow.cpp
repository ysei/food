
#include <QDebug>

#include "mainwindow.h"
#include "datamodel.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	CreateActions();
	CreateLayout();


	QString foodDBName;
	foodDBName = "data.xml";

	foodInfo = new DataModel;
	foodInfo->loadFoodFromFile(foodDBName);

	for (int i = 0; i < foodInfo->getFoodAmount(); i++) {
		foodList->insertItem(i + 1, foodInfo->getFoodNameAtPos(i));
	}

	srand((unsigned)time(0));
	int randomNumber = rand() % (foodInfo->getFoodAmount());
	qDebug() << randomNumber;

	displayedFoodInfo = new QTextDocument;
	QString stringToDisplay;
	stringToDisplay = foodInfo->getFoodNameAtPos(randomNumber);
	stringToDisplay += "\n\n";
	stringToDisplay += "Ingredients:\n" + foodInfo->getFoodIngredientsAtPos(randomNumber);
	stringToDisplay += "\n\n";
	stringToDisplay += "Preparation:\n" + foodInfo->getFoodPreparationAtPos(randomNumber);
	displayedFoodInfo->setPlainText(stringToDisplay);
	foodDetail->setDocument(displayedFoodInfo);
	
}

MainWindow::~MainWindow() {
	delete foodList;
	delete foodDetail;
	delete quitAction;
	delete fileMenu;
	delete menuBar;
	delete boxLayout;
	delete horizontalGroupBox;
	delete foodInfo;
	delete displayedFoodInfo;
}

void MainWindow::CreateActions() {
	quitAction = new QAction(tr("&Quit"), this);
	quitAction->setShortcut(tr("CTRL+Q"));
	connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));
}

void MainWindow::CreateLayout() {
	qDebug() << "vytvarim layout";
	
	foodList = new QListWidget;
	foodList->setSortingEnabled(1);

	foodDetail = new QTextEdit;
	foodDetail->setReadOnly(true);

	boxLayout = new QHBoxLayout;
	boxLayout->addWidget(foodList);
	boxLayout->addWidget(foodDetail);

	horizontalGroupBox = new QGroupBox;
	horizontalGroupBox->setLayout(boxLayout);

	
	menuBar = new QMenuBar(this);
	fileMenu = new QMenu;
	fileMenu = menuBar->addMenu(tr("&File"));
	fileMenu->addAction(quitAction);


	setMenuBar(menuBar);
	setCentralWidget(horizontalGroupBox);
}

void MainWindow::quit() {
	qDebug() << "ukoncuji se";
	qApp->quit();
}
