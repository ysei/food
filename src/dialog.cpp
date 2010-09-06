#include "dialog.h"
#include "enum.h"

#include <QDebug>


/*
 * konstruktor
 * nastavi implicitni hodnoty pro pridavani noveho jidla
 * vytvori layout dialogoveho okna
 */
Dialog::Dialog(QStringList types, QStringList *currentFoodInformation) {
	foodTypes = types;


	//pripadne nastaveni hodnot pokud byl predan parametr currentFoodInformation
	if (currentFoodInformation != 0) {
		foodInformation = *currentFoodInformation;
	}
	else {
		for (int i = infoFirst; i <= infoLast; i++) {
			foodInformation.append(QString(""));
		}
		foodInformation[TYPE] = "meat";
	}


	CreateLayout();
	//InitializeLayout();

	setWindowTitle(tr("Add new food"));

	connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(foodName, SIGNAL(editingFinished()), this, SLOT(FoodNameInserted()));
	connect(foodType, SIGNAL(activated(const QString&)), this, SLOT(FoodTypeInserted(const QString &)));
	connect(foodIngredients, SIGNAL(editingFinished()), this, SLOT(FoodIngredientsInserted()));
	connect(foodPreparation, SIGNAL(textChanged()), this, SLOT(FoodPreparationInserted()));

}

/*
 * destruktor
 * maze dynamicky alokovane tridy 
 */
Dialog::~Dialog() {
	delete foodName;
	delete foodType;
	delete foodIngredients;
	delete foodPreparation;
	delete formLayout;
	delete buttonBox;
	delete box;
	delete mainLayout;
}


/*
 * vytvori layout a do jednotlivych policek nastavi hodnoty
 * zakladem je QVBoxLayout - do nej je pridan QGroupBox a QDialogButtonBox
 * QGroupBox je tvoren jednom QFormLayoutem
 * v QFormLayoutu jsou poporade QLineEdit QComboBox, QLineEdit a QTextEdit
 */
void Dialog::CreateLayout() {
	formLayout = new QFormLayout;
	mainLayout = new QVBoxLayout;
	box = new QGroupBox;
	foodName = new QLineEdit;
	foodType = new QComboBox;
	foodIngredients = new QLineEdit;
	foodPreparation = new QTextEdit;
	
	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

	for (int i = 0; i < foodTypes.count(); i++) {
		foodType->addItem(foodTypes[i]);
	}

	formLayout->addRow(new QLabel(tr("Name:")), foodName);
	formLayout->addRow(new QLabel(tr("Type:")), foodType);
	formLayout->addRow(new QLabel(tr("Ingredients:")), foodIngredients);
	formLayout->addRow(new QLabel(tr("Preparation:")), foodPreparation);

	box->setLayout(formLayout);

	mainLayout->addWidget(box);
	mainLayout->addWidget(buttonBox);

	setLayout(mainLayout);

	//nastaveni hodnot
	foodName->setText(foodInformation[NAME]);
	int indexOfCurrentType;
	indexOfCurrentType = foodType->findText(foodInformation[TYPE]);
	foodType->setCurrentIndex(indexOfCurrentType);
	foodIngredients->setText(foodInformation[INGREDIENTS]);
	foodPreparation->setText(foodInformation[PREPARATION]);
}


/*
 * soukroma metoda
 * inicializuje hodnoty v jednotlivych "prihradkach" v layoutu
 */
/*void Dialog::InitializeLayout() {
	
}*/

/*
 * verejna metoda
 * vrati hodnoty zjistene z dialogoveho okna
 */
QStringList Dialog::GetFoodInformation() {
	return foodInformation;
}


/*
 * soukromy slot
 * detekuje zmenu v poli foodname
 */
void Dialog::FoodNameInserted() {
	foodInformation[NAME] = foodName->displayText();
}


/*
 * soukromy slot
 * detekuje zmenu v poli foodname
 */
void Dialog::FoodTypeInserted(const QString &text) {	
	foodInformation[TYPE] = text;
}

void Dialog::FoodIngredientsInserted() {
	foodInformation[INGREDIENTS] = foodIngredients->displayText();
}

void Dialog::FoodPreparationInserted() {
	foodInformation[PREPARATION] = foodPreparation->toPlainText();
}
