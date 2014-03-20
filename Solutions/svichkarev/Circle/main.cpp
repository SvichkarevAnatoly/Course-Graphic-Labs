#include "circle.h"
#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>
#include <iostream>

int main( int argc, char** argv ){
    if( argc > 1 ){

    } else {
        QApplication app(argc, argv);
        MainWindow window;
        window.show();
        return app.exec();
    }
    return 0;
}
