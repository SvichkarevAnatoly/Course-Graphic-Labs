#include "view-controller/mainwindow.h"
#include <QApplication>
#include <QImage>
#include <QPainter>
int main(int argc, char *argv[])
{

    /*QImage image(800, 600, QImage::Format_RGB888);

    QPainter painter;
    image.fill(Qt::white);
    painter.begin(&image);
    painter.setPen(QPen(Qt::black,1));
    for (int i = 0; i < 800; i+=2) {

        painter.drawLine(QPointF(0, i), QPointF(599, i));
    }
    painter.end();
    image.save("/home/baira/cells.png");*/

    QApplication a(argc, argv);
    MainWindow w(800, 600);
    w.show();
    
    return a.exec();
}
