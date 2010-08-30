
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
	CreateToolBar();

	config.LoadConfiguration();

	//nastaveni velikosti okna
	int x, y, width, height;
	config.GetWindowGeometry(x, y, width, height);
	setGeometry(x, y, width, height);

	//nacteni dat
	foodInfo = new DataModel;
	if (foodInfo->LoadFoodFromFile(config.GetDBFileName()) != true) {
		QMessageBox msgBox;
		msgBox.setText("Unable to open DB file");
		msgBox.setInformativeText("Do you want to create new DB file?");
		msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
		msgBox.setDefaultButton(QMessageBox::Yes);
		int ret = msgBox.exec();
		if (ret == QMessageBox::No) {
			exit(0);
		}
		//FIXME tohle zrusit a pokracovat s prazdnym souborem
		exit(0);
	}

	for (int i = 0; i < foodInfo->GetFoodAmount(); i++) {
		foodList->insertItem(i, foodInfo->GetFoodNameAtIndex(i));
	}

	//nastaveni generatoru pseudonahodnych cisel
	srand((unsigned)time(0));

	int randomNumber = GenerateRandomNumber();

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
	delete addFoodAction;
	delete removeFoodAction;
	delete chooseRandomFoodAction;
	delete fileMenu;
	delete menuBar;
	delete statusBar;
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

	addFoodAction = new QAction(tr("Add food"), this);
	//FIXME popremyslet nad tou zkratkou - nechat/najit lepsi
	addFoodAction->setShortcut(tr("CTRL+N"));
	addFoodAction->setIcon(QIcon(QPixmap("src/img/add.png")));
	addFoodAction->setStatusTip(tr("Add new food"));
	connect(addFoodAction, SIGNAL(triggered()), this, SLOT(AddFood()));

	removeFoodAction = new QAction(tr("Remove food"), this);
	//FIXME popremyslet nad tou zkratkou - zrusit/najit lepsi
	//removeFoodAction->setShortcut(tr("CTRL+R"));
	removeFoodAction->setIcon(QIcon(QPixmap("src/img/remove.png")));
	removeFoodAction->setStatusTip(tr("Remove currently selected food"));
	connect(removeFoodAction, SIGNAL(triggered()), this, SLOT(RemoveFood()));

	chooseRandomFoodAction = new QAction(tr("Choose random food"), this);
	//FIXME popremyslet nad tou zkratkou - najit lepsi
	//chooseRandomFoodAction->setShortCut(tr("SPACE"));
	chooseRandomFoodAction->setIcon(QIcon(QPixmap("src/img/dice.png")));
	chooseRandomFoodAction->setStatusTip(tr("Choose random food"));
	connect(chooseRandomFoodAction, SIGNAL(triggered()), this, SLOT(ChooseRandomFood()));
}

/*
 * soukroma metoda pro vytvoreni widgetu pro zobrazovani informaci
 * vytvoreni nabidky File
 * FIXME vytvorit listu s tlacitkama
 */
void MainWindow::CreateLayout() {
	
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
	fileMenu->addAction(addFoodAction);
	fileMenu->addAction(chooseRandomFoodAction);
	fileMenu->addAction(removeFoodAction);
	fileMenu->addAction(quitAction);

	statusBar = new QStatusBar(this);
	setStatusBar(statusBar);

	setMenuBar(menuBar);
	setCentralWidget(horizontalGroupBox);

	//oznaceni nazvu jidla -> zobrazeni informaci o tomto jidle
	connect(foodList, SIGNAL(itemActivated(QListWidgetItem *)), this, SLOT(ItemSelected(QListWidgetItem *)));
}

/*
 * soukroma metoda
 * vytvori panel nastroju
 */
void MainWindow::CreateToolBar() {
	toolBar = addToolBar("main toolbar");
	toolBar->addAction(addFoodAction);
	toolBar->addAction(chooseRandomFoodAction);
	toolBar->addAction(removeFoodAction);
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
 * soukroma metoda
 * vygeneruje nahodne cislo
 */
int MainWindow::GenerateRandomNumber() {
	int randomNumber = rand() % (foodInfo->GetFoodAmount());
	return randomNumber;
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


/*
 * soukromy slot
 * prida nove jidlo do seznamu jidel
 */
void MainWindow::AddFood() {
	//FIXME udelat dialog, ve kterem bude nazev jidla, ingredience, typ a postup pripravy
	/*QMessageBox msgBox;
	msgBox.setText("zde bude dialogove okno pro pridani noveho jidla");
	msgBox.exec();*/
	QStringList newFoodInformation;
	Dialog dialog;
	int result;
	result = dialog.exec();
	if (result == 1) {
		qDebug() << "stisknuto OK";
		newFoodInformation = dialog.GetNewFoodInformation();
		qDebug() << newFoodInformation;
		foodInfo->addNewFood(newFoodInformation);
		foodList->addItem(newFoodInformation[NAME]);
	}
	if (result == 0) {
		qDebug() << "stisknuto Cancel";
	}
}

/*
 * soukromy slot
 * odstrani jidlo ze seznamu jidel
 */
void MainWindow::RemoveFood() {
	//FIXME odebirat momentalne oznacene jidlo
	//zeptat se, jestli se ma jidlo opravdu odebrat
	//pripadne prekreslit zobrazene informace
	QMessageBox msgBox;
	msgBox.setText("momentalne oznacene jidlo se odebere");
	msgBox.exec();
}

/*
 * soukromy slot
 * vybere nahodne jidlo
 */
void MainWindow::ChooseRandomFood() {
	int randomNumber = GenerateRandomNumber();
	QListWidgetItem *item;
	item = foodList->item(randomNumber);
	foodList->setCurrentItem(item);
	ItemSelected(item);
}
