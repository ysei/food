
#include <QDebug>

#include "mainwindow.h"
#include "datamodel.h"

/*
 * Konstruktor hlavniho okna
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	//vytvoreni akci v nabidce File
	CreateActions();
	//vytvoreni widgetu pro zobrazovani informaci, nabidky File a listy s tlacitkama
	CreateLayout();

	//nazev souboru s databazi
	QString foodDBName;
	foodDBName = "data.xml";

	//nacteni dat
	foodInfo = new DataModel;
	foodInfo->loadFoodFromFile(foodDBName);

	for (int i = 0; i < foodInfo->getFoodAmount(); i++) {
		foodList->insertItem(i, foodInfo->getFoodNameAtIndex(i));
	}

	//vygenerovani nahodneho cisla
	srand((unsigned)time(0));
	int randomNumber = rand() % (foodInfo->getFoodAmount());
	qDebug() << randomNumber;

	//zobrazeni informaci o nahodne vybranem jidle
	displayedFoodInfo = new QTextDocument;
	DisplayInfoAtIndex(randomNumber);
	foodList->setCurrentItem(foodList->item(randomNumber));
	
}

/*
 * Destruktor
 */
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

/*
 * soukroma metoda pro vytvoreni akci v nabidce File
 * vytvoreni signalu k prislusnym akcim
 */
void MainWindow::CreateActions() {
	quitAction = new QAction(tr("&Quit"), this);
	quitAction->setShortcut(tr("CTRL+Q"));
	connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

}

/*
 * vytvoreni widgetu pro zobrazovani informaci
 * vytvoreni nabidky File
 * FIXME vytvorit listu s tlacitkama
 */
void MainWindow::CreateLayout() {
	qDebug() << "vytvarim layout";
	
	//widget pro zobrazeni nazvu jidel
	foodList = new QListWidget;
	foodList->setSortingEnabled(1);

	//widget pro zobrazeni informaci o jidle
	foodDetail = new QTextEdit;
	foodDetail->setReadOnly(true);

	//layout umoznujici horizontalni usporadani widgetu
	boxLayout = new QHBoxLayout;
	boxLayout->addWidget(foodList);
	boxLayout->addWidget(foodDetail);

	//widget pro zobrazeni horizontalniho layoutu
	horizontalGroupBox = new QGroupBox;
	horizontalGroupBox->setLayout(boxLayout);

	//nabidka File
	menuBar = new QMenuBar(this);
	fileMenu = new QMenu;
	fileMenu = menuBar->addMenu(tr("&File"));
	fileMenu->addAction(quitAction);


	setMenuBar(menuBar);
	setCentralWidget(horizontalGroupBox);

	//oznaceni nazvu jidla -> zobrazeni informaci o tomto jidle
	connect(foodList, SIGNAL(itemActivated(QListWidgetItem *)), this, SLOT(ItemSelected(QListWidgetItem *)));
}


/*
 * soukroma metoda, ktera zobrazi informace o jidle, ktere se nachazi na urcitem indexu
 */
void MainWindow::DisplayInfoAtIndex (int index) {
	QString stringToDisplay;
	stringToDisplay = foodInfo->getFoodNameAtIndex(index);
	stringToDisplay += "\n\n";
	stringToDisplay += "Ingredients:\n" + foodInfo->getFoodIngredientsAtIndex(index);
	stringToDisplay += "\n\n";
	stringToDisplay += "Preparation:\n" + foodInfo->getFoodPreparationAtIndex(index);
	displayedFoodInfo->setPlainText(stringToDisplay);
	foodDetail->setDocument(displayedFoodInfo);
}

/*
 * soukromy slot
 * ukonceni aplikace
 */
void MainWindow::quit() {
	qApp->quit();
}


/*
 * soukromy slot
 * zjisti ktere jidlo bylo oznaceno a zobrazi o nem informace
 */
void MainWindow::ItemSelected(QListWidgetItem *item) {
	QString selectedItem;
	selectedItem = item->text();

	int selectedItemIndex;
	selectedItemIndex = foodInfo->indexOf(selectedItem);

	DisplayInfoAtIndex(selectedItemIndex);
}

