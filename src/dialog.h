#ifndef __DIALOG_H__
#define __DIALOG_H__

#include <QDialog>
#include <QGroupBox>
#include <QComboBox>
#include <QTextEdit>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QStringList>

class Dialog : public QDialog {
	Q_OBJECT

	public:
		Dialog(QStringList types, QStringList *currentFoodInformation = 0);
		~Dialog();
		QStringList GetFoodInformation();

	private:
		QVBoxLayout *mainLayout;
		QFormLayout *formLayout;
		QGroupBox *box;
		QLineEdit *foodName;
		QComboBox *foodType;
		QLineEdit *foodIngredients;
		QTextEdit *foodPreparation;
		QDialogButtonBox *buttonBox;
		QStringList foodInformation;
		QStringList foodTypes;

		void CreateLayout();
	//	void InitializeLayout();

	private slots:
		void FoodNameInserted();
		void FoodTypeInserted(const QString & text);	
		void FoodIngredientsInserted();
		void FoodPreparationInserted();
};

#endif
