#include "dialog.h"
#include "enum.h"

#include <QDebug>


/*
 * konstruktor
 * nastavi implicitni hodnoty pro pridavani noveho jidla
 * vytvori layout dialogoveho okna
 */
Dialog::Dialog() {
	for (int i = infoFirst; i <= infoLast; i++) {
		newFoodInformation.append(QString(""));
	}

	//nastaveni implicitnich hodnot
	newFoodInformation[TYPE] = "meat";

	CreateLayout();

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
 * vytvori layout
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

	foodType->addItem(QString("meat"));

	formLayout->addRow(new QLabel(tr("Name:")), foodName);
	formLayout->addRow(new QLabel(tr("Type:")), foodType);
	formLayout->addRow(new QLabel(tr("Ingredients:")), foodIngredients);
	formLayout->addRow(new QLabel(tr("Preparation:")), foodPreparation);

	box->setLayout(formLayout);

	mainLayout->addWidget(box);
	mainLayout->addWidget(buttonBox);

	setLayout(mainLayout);
}

/*
 * verejna metoda
 * vrati hodnoty zjistene z dialogoveho okna
 */
QStringList Dialog::GetNewFoodInformation() {
	return newFoodInformation;
}


/*
 * soukromy slot
 * detekuje zmenu v poli foodname
 */
void Dialog::FoodNameInserted() {
	newFoodInformation[NAME] = foodName->displayText();
}


/*
 * soukromy slot
 * detekuje zmenu v poli foodname
 */
void Dialog::FoodTypeInserted(const QString &text) {	
	newFoodInformation[TYPE] = text;
}

void Dialog::FoodIngredientsInserted() {
	newFoodInformation[INGREDIENTS] = foodIngredients->displayText();
}

void Dialog::FoodPreparationInserted() {
	newFoodInformation[PREPARATION] = foodPreparation->toPlainText();
}
