#include "view-controller/mainwindow.h"
#include <QApplication>
#include <QImage>
#include <QPainter>

int main( int argc, char *argv[] ){

    QApplication a(argc, argv);
    MainWindow w(800, 600);
    w.show();
    
    return a.exec();
}
