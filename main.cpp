#include "widget.h"
#include <QApplication>
#include "fballwidget.h"
#include"mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    FBallWidget w;
    w.show();

    return a.exec();
}
