/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
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
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "qchartview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label1;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QtCharts::QChartView *graphicsView3;
    QWidget *tab_2;
    QtCharts::QChartView *graphicsView2;
    QWidget *tab_3;
    QtCharts::QChartView *graphicsView1;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QLabel *label_3;
    QLabel *label_4;
    QLCDNumber *lcdNumber_2;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_6;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(948, 795);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label1 = new QLabel(centralwidget);
        label1->setObjectName(QStringLiteral("label1"));
        label1->setGeometry(QRect(200, 30, 511, 131));
        label1->setStyleSheet(QString::fromUtf8("border-image:url(:/images/QQ\346\210\252\345\233\2765.png);"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 180, 171, 81));
        pushButton->setStyleSheet(QString::fromUtf8("border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"background-color: rgb(0, 170, 127);"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(140, 280, 171, 81));
        pushButton_2->setStyleSheet(QString::fromUtf8("border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"background-color: rgb(0, 170, 127);"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(120, 380, 701, 361));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        graphicsView3 = new QtCharts::QChartView(tab);
        graphicsView3->setObjectName(QStringLiteral("graphicsView3"));
        graphicsView3->setGeometry(QRect(0, 0, 691, 331));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        graphicsView2 = new QtCharts::QChartView(tab_2);
        graphicsView2->setObjectName(QStringLiteral("graphicsView2"));
        graphicsView2->setGeometry(QRect(0, 0, 691, 331));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        graphicsView1 = new QtCharts::QChartView(tab_3);
        graphicsView1->setObjectName(QStringLiteral("graphicsView1"));
        graphicsView1->setGeometry(QRect(-5, 1, 701, 341));
        tabWidget->addTab(tab_3, QString());
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(570, 350, 271, 51));
        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(570, 210, 91, 51));
        lcdNumber->setSmallDecimalPoint(false);
        lcdNumber->setProperty("intValue", QVariant(50));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(510, 200, 91, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(510, 290, 211, 31));
        label_4->setFont(font);
        lcdNumber_2 = new QLCDNumber(centralwidget);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(570, 280, 91, 51));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(500, 210, 181, 51));
        label_2->setStyleSheet(QStringLiteral("background-color: rgb(15, 251, 255);"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(500, 280, 181, 51));
        label_5->setStyleSheet(QStringLiteral("background-color: rgb(8, 243, 255);"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(480, 190, 241, 161));
        label_6->setStyleSheet(QLatin1String("background-color: rgb(85, 170, 255);\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;"));
        MainWindow->setCentralWidget(centralwidget);
        label_6->raise();
        label_5->raise();
        label_2->raise();
        label1->raise();
        pushButton->raise();
        pushButton_2->raise();
        tabWidget->raise();
        label->raise();
        lcdNumber->raise();
        label_3->raise();
        label_4->raise();
        lcdNumber_2->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 948, 21));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addSeparator();

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label1->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "\346\225\231\345\256\244\345\256\236\346\227\266\345\217\226\346\231\257", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "\347\202\271\345\220\215\357\274\210\350\212\261\345\220\215\345\206\214\357\274\211", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "  \346\234\254\345\255\246\346\234\237", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\346\234\254\346\234\210  ", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "\346\234\254\346\230\237\346\234\237", Q_NULLPTR));
        label->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", " \345\272\224\345\210\260\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", " \345\256\236\345\210\260\357\274\232", Q_NULLPTR));
        label_2->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
        menu->setTitle(QApplication::translate("MainWindow", "\346\231\272\346\205\247\350\257\276\345\240\202\346\241\214\351\235\242\347\253\257", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
