
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

	bool configFileExists;
	configFileExists = config.LoadConfiguration("config.xml");
	if (configFileExists == false) {
		//FIXME dialogove okynko ve kterem pude naklepat cesta ke konfiguracnimu souboru
		QString newConfigFileName;
		newConfigFileName = QFileDialog::getOpenFileName(this);
		qDebug() << newConfigFileName;
		exit(0);
	}

	//nastaveni velikosti okna
	int x, y, width, height;
	config.GetWindowGeometry(x, y, width, height);
	setGeometry(x, y, width, height);

	//nastaveni generatoru pseudonahodnych cisel
	srand((unsigned)time(0));

	//nacteni dat
	foodInfo = new DataModel;
	bool foodDBExists;
	QString DBFileName;
	DBFileName = config.GetDBFileName();
	foodDBExists = foodInfo->LoadFoodFromFile(DBFileName);
	if (foodDBExists == false) {
		QMessageBox msgBox;
		msgBox.setText("Unable to read from file " + DBFileName);
		msgBox.setInformativeText("Do you want to create new food DB file?");
		msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
		msgBox.setDefaultButton(QMessageBox::Yes);
		int ret = msgBox.exec();
		if (ret == QMessageBox::No) {
			exit(0);
		}
	}
	else {
		for (int i = 0; i < foodInfo->GetFoodAmount(); i++) {
			foodList->insertItem(i, foodInfo->GetFoodNameAtIndex(i));
		}
	}

	displayedFoodInfo = new QTextDocument;

	if (foodInfo->GetFoodAmount() != 0) {
		int randomNumber = GenerateRandomNumber();

		//zobrazeni informaci o nahodne vybranem jidle
		DisplayInfoAtIndex(randomNumber);
		foodList->setCurrentItem(foodList->item(randomNumber));
	}

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
	delete editFoodAction;
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
	addFoodAction->setShortcut(tr("CTRL+N"));
	addFoodAction->setIcon(QIcon(QPixmap("src/img/add.png")));
	addFoodAction->setStatusTip(tr("Add new food"));
	connect(addFoodAction, SIGNAL(triggered()), this, SLOT(AddFood()));

	removeFoodAction = new QAction(tr("Remove food"), this);
	removeFoodAction->setShortcut(tr("Delete"));
	removeFoodAction->setIcon(QIcon(QPixmap("src/img/remove.png")));
	removeFoodAction->setStatusTip(tr("Remove currently selected food"));
	connect(removeFoodAction, SIGNAL(triggered()), this, SLOT(RemoveFood()));

	chooseRandomFoodAction = new QAction(tr("Choose random food"), this);
	chooseRandomFoodAction->setIcon(QIcon(QPixmap("src/img/dice.png")));
	chooseRandomFoodAction->setStatusTip(tr("Choose random food"));
	connect(chooseRandomFoodAction, SIGNAL(triggered()), this, SLOT(ChooseRandomFood()));

	editFoodAction = new QAction(tr("Edit food"), this);
	editFoodAction->setIcon(QIcon(QPixmap("src/img/edit.png")));
	editFoodAction->setStatusTip(tr("Edit currently selected food"));
	connect(editFoodAction, SIGNAL(triggered()), this, SLOT(EditFood()));
	
	
}

/*
 * soukroma metoda pro vytvoreni widgetu pro zobrazovani informaci
 * vytvoreni nabidky File
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
	fileMenu->addAction(editFoodAction);
	fileMenu->addAction(quitAction);

	statusBar = new QStatusBar(this);
	setStatusBar(statusBar);

	setMenuBar(menuBar);
	setCentralWidget(horizontalGroupBox);

	//zobrazeni informace o nove oznacenem jidle
	connect(foodList, SIGNAL(itemSelectionChanged()), this, SLOT(AnotherFoodSelected()));
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
	toolBar->addAction(editFoodAction);
}

/*
 * soukroma metoda, ktera zobrazi informace o jidle, ktere se nachazi na urcitem indexu
 */
void MainWindow::DisplayInfoAtIndex (int index) {
	QString stringToDisplay;
	stringToDisplay = foodInfo->GetFoodNameAtIndex(index);
	stringToDisplay += "\n\n";
	stringToDisplay += "Type:\n" + foodInfo->GetFoodTypeAtIndex(index);
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
 * pri oznaceni jineho jidla zobrazuje informaci o tomto jidle
 */
void MainWindow::AnotherFoodSelected() {
	QString selectedItem;
	selectedItem = foodList->currentItem()->text();

	int selectedItemIndex;
	selectedItemIndex = foodInfo->IndexOf(selectedItem);

	DisplayInfoAtIndex(selectedItemIndex);
}


/*
 * soukromy slot
 * prida nove jidlo do seznamu jidel pomoci dialogoveho okna
 */
void MainWindow::AddFood() {
	QStringList newFoodInformation;
	Dialog dialog(foodInfo->GetFoodTypes());
	int result;

	result = dialog.exec();
	if (result == QDialog::Accepted) {
		newFoodInformation = dialog.GetFoodInformation();
		foodInfo->AddNewFood(newFoodInformation);
		foodList->addItem(newFoodInformation[NAME]);
		foodInfo->SaveFoodIntoFile(config.GetDBFileName());
	}
}

/*
 * soukromy slot
 * zepta se, jestli se ma jidlo odstranit
 * pokud uzivatel klikne na "ok", odstrani se jidlo ze seznamu jidel
 */
void MainWindow::RemoveFood() {
	QListWidgetItem *item;
	item = foodList->currentItem();

	QString itemName;
	itemName = item->text();

	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Question);
	msgBox.setWindowTitle("Removing " + itemName);
	msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	msgBox.setText("Do you really want to remove food " + itemName + "?");

	int result;
	result = msgBox.exec();
	if (result == QMessageBox::Ok) {
		foodInfo->RemoveFood(itemName);

		int indexOfRemovedItem;
		indexOfRemovedItem = foodList->row(item);
		foodList->removeItemWidget(item);
		foodList->takeItem(indexOfRemovedItem);
		foodInfo->SaveFoodIntoFile(config.GetDBFileName());
	}
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
}

/*
 * soukromy slot
 * edituje momentalne zobrazene jidlo
 */
void MainWindow::EditFood() {
	QListWidgetItem *item;
	item = foodList->currentItem();

	QStringList currentFoodInformation;
	//nazev jidla
	currentFoodInformation.append(item->text());
	int index;
	index = foodInfo->IndexOf(item->text());
	//typ, ingredience a priprava
	currentFoodInformation.append(foodInfo->GetFoodTypeAtIndex(index));
	currentFoodInformation.append(foodInfo->GetFoodIngredientsAtIndex(index));
	currentFoodInformation.append(foodInfo->GetFoodPreparationAtIndex(index));

	
	Dialog dialog(foodInfo->GetFoodTypes(), &currentFoodInformation);

	QStringList newFoodInformation;
	int result;
	result = dialog.exec();
	if (result == QDialog::Accepted) {
		newFoodInformation = dialog.GetFoodInformation();
		item->setText(newFoodInformation[NAME]);
		foodInfo->EditFoodAtIndex(newFoodInformation, index);
		this->AnotherFoodSelected();
		foodInfo->SaveFoodIntoFile(config.GetDBFileName());
	}
}
