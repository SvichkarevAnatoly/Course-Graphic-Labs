#include "canvas.h"

Canvas::Canvas(int w, int h) :
    width(w), height(h)
{
}

Canvas::~Canvas(){}

// TODO: зачем везде эти this?
int Canvas::getHeight() const {
    return this->height;
}

int Canvas::getWidth() const {
    return this->width;
}
