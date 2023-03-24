/********************************************************************************
** Form generated from reading UI file 'filme.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILME_H
#define UI_FILME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilmeClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FilmeClass)
    {
        if (FilmeClass->objectName().isEmpty())
            FilmeClass->setObjectName(QString::fromUtf8("FilmeClass"));
        FilmeClass->resize(600, 400);
        menuBar = new QMenuBar(FilmeClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        FilmeClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FilmeClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        FilmeClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(FilmeClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        FilmeClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(FilmeClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        FilmeClass->setStatusBar(statusBar);

        retranslateUi(FilmeClass);

        QMetaObject::connectSlotsByName(FilmeClass);
    } // setupUi

    void retranslateUi(QMainWindow *FilmeClass)
    {
        FilmeClass->setWindowTitle(QCoreApplication::translate("FilmeClass", "Filme", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilmeClass: public Ui_FilmeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILME_H
