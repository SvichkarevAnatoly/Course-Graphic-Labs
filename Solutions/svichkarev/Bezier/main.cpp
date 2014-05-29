#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QTextStream>
#include <iostream>

int main( int argc, char** argv ){
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
