#include "mainwindow.h"

#include <QApplication>
//#include <QtWebEngineQuick>

int main(int argc, char *argv[])
{
    //QtWebEngine::initialize()
    QCoreApplication::setOrganizationName("Patrik Navratil");
    QCoreApplication::setApplicationName("UltraWide");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
