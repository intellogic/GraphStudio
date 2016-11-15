#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::desktop()->screenGeometry();
    MainWindow w;
    w.show();

    return a.exec();
}
