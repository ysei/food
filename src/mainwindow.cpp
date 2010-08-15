
#include <QDebug>

#include "mainwindow.h"

/*
 * Konstruktor hlavniho okna
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	//vytvoreni akci v nabidce File
	CreateActions();
	//vytvoreni widgetu pro zobrazovani informaci, nabidky File a listy s tlacitkama
	CreateLayout();
	config.LoadConfiguration();

	//nastaveni velikosti okna
	int x, y, width, height;
	config.GetWindowGeometry(x, y, width, height);
	setGeometry(x, y, width, height);

	//nacteni dat
	foodInfo = new DataModel;
	foodInfo->LoadFoodFromFile(config.GetDBFileName());

	for (int i = 0; i < foodInfo->GetFoodAmount(); i++) {
		foodList->insertItem(i, foodInfo->GetFoodNameAtIndex(i));
	}

	//vygenerovani nahodneho cisla
	//FIXME srand nechat v konstruktoru, samotne generovani cisla dat do samotne metody
	srand((unsigned)time(0));
	int randomNumber = rand() % (foodInfo->GetFoodAmount());
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
	QRect tmp = geometry();
	config.SetWindowGeometry(tmp.x(), tmp.y(), tmp.width(), tmp.height());
	config.SaveConfiguration();

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
	connect(quitAction, SIGNAL(triggered()), this, SLOT(Quit()));

}

/*
 * soukroma metoda pro vytvoreni widgetu pro zobrazovani informaci
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
	stringToDisplay = foodInfo->GetFoodNameAtIndex(index);
	stringToDisplay += "\n\n";
	stringToDisplay += "Ingredients:\n" + foodInfo->GetFoodIngredientsAtIndex(index);
	stringToDisplay += "\n\n";
	stringToDisplay += "Preparation:\n" + foodInfo->GetFoodPreparationAtIndex(index);
	displayedFoodInfo->setPlainText(stringToDisplay);
	foodDetail->setDocument(displayedFoodInfo);
}

/*
 * soukromy slot
 * ukonceni aplikace
 */
void MainWindow::Quit() {
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
	selectedItemIndex = foodInfo->IndexOf(selectedItem);

	DisplayInfoAtIndex(selectedItemIndex);
}

