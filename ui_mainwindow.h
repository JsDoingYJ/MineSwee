/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_9_9;
    QAction *action_10_15;
    QAction *action_10_17;
    QAction *gameStart;
    QAction *gameEnd;
    QAction *author;
    QAction *version;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_9_9_10_15_10_17;
    QMenu *menu_2;
    QMenu *menuClose;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        action_9_9 = new QAction(MainWindow);
        action_9_9->setObjectName(QStringLiteral("action_9_9"));
        action_10_15 = new QAction(MainWindow);
        action_10_15->setObjectName(QStringLiteral("action_10_15"));
        action_10_17 = new QAction(MainWindow);
        action_10_17->setObjectName(QStringLiteral("action_10_17"));
        gameStart = new QAction(MainWindow);
        gameStart->setObjectName(QStringLiteral("gameStart"));
        gameEnd = new QAction(MainWindow);
        gameEnd->setObjectName(QStringLiteral("gameEnd"));
        author = new QAction(MainWindow);
        author->setObjectName(QStringLiteral("author"));
        version = new QAction(MainWindow);
        version->setObjectName(QStringLiteral("version"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_9_9_10_15_10_17 = new QMenu(menuBar);
        menu_9_9_10_15_10_17->setObjectName(QStringLiteral("menu_9_9_10_15_10_17"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menuClose = new QMenu(menuBar);
        menuClose->setObjectName(QStringLiteral("menuClose"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_9_9_10_15_10_17->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menuClose->menuAction());
        menu->addAction(gameStart);
        menu->addAction(gameEnd);
        menu_9_9_10_15_10_17->addAction(action_9_9);
        menu_9_9_10_15_10_17->addAction(action_10_15);
        menu_9_9_10_15_10_17->addAction(action_10_17);
        menu_2->addAction(author);
        menu_2->addAction(version);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_9_9->setText(QApplication::translate("MainWindow", "\345\210\235\347\272\247: 9*9 ", 0));
        action_10_15->setText(QApplication::translate("MainWindow", "\344\270\255\347\272\247: 10*15 ", 0));
        action_10_17->setText(QApplication::translate("MainWindow", "\351\253\230\347\272\247: 10*17", 0));
        gameStart->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213/\351\207\215\346\226\260\345\274\200\345\247\213", 0));
        gameEnd->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237\346\234\254\345\261\200\346\270\270\346\210\217", 0));
        author->setText(QApplication::translate("MainWindow", "\344\275\234\350\200\205\357\274\232\346\270\270\345\256\266", 0));
        version->setText(QApplication::translate("MainWindow", "\347\211\210\346\234\254:v1.0 ", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\346\270\270\346\210\217", 0));
        menu_9_9_10_15_10_17->setTitle(QApplication::translate("MainWindow", "\351\232\276\345\272\246", 0));
        menu_2->setTitle(QApplication::translate("MainWindow", "\345\205\266\344\273\226", 0));
        menuClose->setTitle(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
