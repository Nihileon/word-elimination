#ifndef MATERIALMESSAGEBOX_H
#define MATERIALMESSAGEBOX_H

#include <QHBoxLayout>
#include <QLabel>
#include <qtmaterialdialog.h>
#include <qtmaterialflatbutton.h>

class MaterialMessageBox:public QtMaterialDialog
{
public:
    MaterialMessageBox(QWidget *parent){
        this->setParent(parent);
        dialogWidget = new QWidget;
        QVBoxLayout *dialogWidgetLayout = new QVBoxLayout;
        dialogWidget->setLayout(dialogWidgetLayout);
        closeButton = new QtMaterialFlatButton("Close");
        anotherButton  = new QtMaterialFlatButton("Agree");
        qlabel = new QLabel;
        QFont ft;
        ft.setPointSize(14);
        qlabel->setFont(ft);
        dialogWidgetLayout->addWidget(qlabel);
        dialogWidgetLayout->setAlignment(qlabel, Qt::AlignBottom| Qt::AlignCenter);
        dialogWidgetLayout->addWidget(anotherButton);
        dialogWidgetLayout->setAlignment(anotherButton,
                                         Qt::AlignBottom | Qt::AlignCenter);
        this->anotherButton->hide();
        dialogWidgetLayout->addWidget(closeButton);
        dialogWidgetLayout->setAlignment(closeButton, Qt::AlignBottom| Qt::AlignCenter);
        closeButton->setMaximumWidth(150);
        QVBoxLayout *dialogLayout = new QVBoxLayout;
        this->setWindowLayout(dialogLayout);
        dialogWidget->setMinimumHeight(150);
        dialogWidget->setMinimumWidth(300);
        dialogLayout->addWidget(dialogWidget);
        connect(closeButton, SIGNAL(pressed()), this, SLOT(hideDialog()));
        connect(anotherButton, SIGNAL(pressed()), this, SLOT(hideDialog()));
//        this->showDialog();
    }

    ~MaterialMessageBox(){
        delete dialogWidget;
        delete qlabel;
        delete closeButton;
    }

    void setMinimumWidth(int width){
        dialogWidget->setMinimumWidth(width);
    }

    void setMinimumHeight(int height){
        dialogWidget->setMinimumHeight(height);
    }

    void setText(QString qs){
        qlabel->setText(qs);
    }

    QWidget *dialogWidget;
    QLabel* qlabel;
    QtMaterialFlatButton * closeButton;
    QtMaterialFlatButton * anotherButton;
};

#endif // MATERIALMESSAGEBOX_H
