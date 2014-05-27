#ifndef SQUARE_H
#define SQUARE_H

#include "canvas/canvas.h"
#include "triangle.h"

class Square : public QObject
{
    Q_OBJECT
private:
    double xc;
    double yc;
    double leftX, rightX;
    double downY, upY;
    Triangle leftDownTriangle;
    Triangle rightUpTriangle;
    int size;
    int maxX;
    int maxY;
public:
    // Задается стороной и центром
    Square(int size, double xc, double yc);
    void setDefault();
    void setMax(int maxX, int maxY);

signals:
    void angleChanged(double);
    void scaleXChanged(double);
    void scaleYChanged(double);
    void centerChanged(double);
public slots:
    void draw(Canvas& canvas, Texture* texture=0);
    void setCenter(double xc, double yc);
    void setSize(int size);
    void rotate(double agle);
    void scaleX(double scaleX);
    void scaleY(double scaleY);

};

#endif // SQUARE_H
