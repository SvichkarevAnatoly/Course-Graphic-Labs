#include "texturedpoint.h"
#include "square.h"
#include <QDebug>

Square::Square(int size, double xc, double yc){
    setCenter(xc,yc);
    setSize(size);
    setMax(rightX, upY);
}

// отрисовка квадрата через его треугольники
void Square::draw(Canvas &canvas, Texture* texture){
    // очищаем полотно
    canvas.clear();
    // отрисовываем каждый треугольник заданной текстурой
    rightUpTriangle.draw(canvas, texture);
    leftDownTriangle.draw(canvas, texture);
}

// установка центра для квадрата и для его треугольников
void Square::setCenter(double xc, double yc){
    this->xc = xc;
    this->yc = yc;

    leftDownTriangle.setRotateCenter(xc, yc);
    rightUpTriangle.setRotateCenter(xc, yc);
}

//?
void Square::setMax(int maxX, int maxY){
    rightUpTriangle.setMaxX(maxX);
    rightUpTriangle.setMaxY(maxY);
    leftDownTriangle.setMaxX(maxX);
    leftDownTriangle.setMaxY(maxY);
}

void Square::setSize(int size) {
    this->size = size;
    //вычисляем края
    leftX = xc-size*1.0/2;
    rightX = xc+size*1.0/2;
    downY = yc-size*1.0/2;
    upY = yc+size*1.0/2;

    // устанавливаем положение треугольников(Y вниз)
    leftDownTriangle.changePoints(TexturedPoint(leftX, downY, 0, 0), TexturedPoint(leftX, upY, 0, 1),
                    TexturedPoint(rightX, upY, 1, 1));

    rightUpTriangle.changePoints(TexturedPoint(leftX, downY, 0, 0), TexturedPoint(rightX, downY, 1, 0),
                    TexturedPoint(rightX, upY, 1, 1));
    setCenter(xc,yc);
}

// установка начального положения: нет поворота и сжатий
void Square::setDefault(){
    rotate(0);
    scaleX(Triangle::DEFAULT_SCALE_X);
    scaleY(Triangle::DEFAULT_SCALE_Y);
}

// поворот квадрата через поворот его треугольников
//и вызов события изменения
void Square::rotate(double angle) {
    leftDownTriangle.rotate(angle);
    rightUpTriangle.rotate(angle);
    emit angleChanged(angle);
}

void Square::scaleX(double scaleX) {
    leftDownTriangle.scaleX(scaleX);
    rightUpTriangle.scaleX(scaleX);
    emit scaleXChanged(scaleX);
}

void Square::scaleY(double scaleY) {
    leftDownTriangle.scaleY(scaleY);
    rightUpTriangle.scaleY(scaleY);
    emit scaleYChanged(scaleY);
}
