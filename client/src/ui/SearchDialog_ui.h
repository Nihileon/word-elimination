/********************************************************************************
** Form generated from reading UI file 'searchdialog_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SEARCHDIALOG_UI_H
#define SEARCHDIALOG_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include <qtmaterialradiobutton.h>
#include <qtmaterialraisedbutton.h>
#include <qtmaterialtextfield.h>

QT_BEGIN_NAMESPACE

class Ui_SearchDialogUi
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QtMaterialRadioButton *challengerRadioButton;
    QtMaterialRadioButton *wordRadioButton;
    QTableView *userTableView;
    QtMaterialTextField *userLineEdit;
    QtMaterialRaisedButton *backPushButton;
    QtMaterialRaisedButton *searchPushButton;

    void setupUi(QDialog *SearchDialogUi)
    {
        if (SearchDialogUi->objectName().isEmpty())
            SearchDialogUi->setObjectName(QStringLiteral("SearchDialogUi"));
        SearchDialogUi->resize(500, 400);
        layoutWidget = new QWidget(SearchDialogUi);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(100, 70, 281, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        challengerRadioButton = new QtMaterialRadioButton(layoutWidget);
        challengerRadioButton->setObjectName(QStringLiteral("challengerRadioButton"));

        horizontalLayout->addWidget(challengerRadioButton);

        wordRadioButton = new QtMaterialRadioButton(layoutWidget);
        wordRadioButton->setObjectName(QStringLiteral("wordRadioButton"));

        horizontalLayout->addWidget(wordRadioButton);

        userTableView = new QTableView(SearchDialogUi);
        userTableView->setObjectName(QStringLiteral("userTableView"));
        userTableView->setGeometry(QRect(110, 130, 280, 210));
        userLineEdit = new QtMaterialTextField(SearchDialogUi);
        userLineEdit->setObjectName(QStringLiteral("userLineEdit"));
        userLineEdit->setGeometry(QRect(100, 10, 241, 51));
        backPushButton = new QtMaterialRaisedButton(SearchDialogUi);
        backPushButton->setObjectName(QStringLiteral("backPushButton"));
        backPushButton->setGeometry(QRect(130, 340, 211, 41));
        searchPushButton = new QtMaterialRaisedButton(SearchDialogUi);
        searchPushButton->setObjectName(QStringLiteral("searchPushButton"));
        searchPushButton->setGeometry(QRect(370, 20, 81, 41));

        retranslateUi(SearchDialogUi);

        QMetaObject::connectSlotsByName(SearchDialogUi);
    } // setupUi

    void retranslateUi(QDialog *SearchDialogUi)
    {
        SearchDialogUi->setWindowTitle(QApplication::translate("SearchDialogUi", "Dialog", Q_NULLPTR));
        challengerRadioButton->setText(QApplication::translate("SearchDialogUi", "challenger", Q_NULLPTR));
        wordRadioButton->setText(QApplication::translate("SearchDialogUi", "word builder", Q_NULLPTR));
        backPushButton->setText(QApplication::translate("SearchDialogUi", "back", Q_NULLPTR));
        searchPushButton->setText(QApplication::translate("SearchDialogUi", "Search", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SearchDialogUi: public Ui_SearchDialogUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SEARCHDIALOG_UI_H
