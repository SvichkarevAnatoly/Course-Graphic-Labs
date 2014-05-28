#include "view-controller/mainwindow.h"
#include <QApplication>
#include <QImage>
#include <QPainter>

#define APP
int main( int argc, char *argv[] ){
#ifdef APP
    QApplication a(argc, argv);
    MainWindow w(800, 600);
    w.show();

    return a.exec();
#else
    QImage image(400, 400, QImage::Format_RGB888);

    QPainter painter;
    image.fill(Qt::white);
    painter.begin(&image);
    painter.setPen(QPen(Qt::black,1));

    int s = 1;
    int c = 0;
    for (int i = 0; i < 400; i+=s) {
        for (int j = 0; j < 400; j+=s) {
            //painter.drawRect( i, 0 , i, 399 );
            //painter.drawRect( 0, j , 399, j );
            if( c % 2 ){
                painter.drawPoint( i+1, j+1 );
            }
            c++;
        }
        c++;
    }
    painter.end();
    image.save("шахматы2.png");

#endif
    

}
