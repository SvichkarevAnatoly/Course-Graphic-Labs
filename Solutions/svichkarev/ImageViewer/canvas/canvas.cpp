#include "canvas.h"
#include <QImage>

Canvas::Canvas(int w, int h)
    : width(w), height(h), image(w,h, QImage::Format_RGB888)
{
    clear();
}

Canvas::Canvas(const Canvas& other)
{
    width = other.width;
    height = other.height;
    image = other.image;
}

Canvas& Canvas::operator=(const Canvas& c){
    width = c.width;
    height = c.height;
    image = c.image;
    return *this;
 }

Canvas::~Canvas(){

}

int Canvas::getWidth() {
    return width;
}

int Canvas::getHeight() {
    return height;
}

const QImage& Canvas::getImage() const{
    return image;
}

void Canvas::drawPixel(const int x, const int y, const QColor color){
    int r, g, b;
    color.getRgb(&r, &g, &b);
    uchar* bytes = image.bits();
    bytes[ y * image.bytesPerLine() + x * 3    ] = r;
    bytes[ y * image.bytesPerLine() + x * 3 + 1] = g;
    bytes[ y * image.bytesPerLine() + x * 3 + 2] = b;
}

void Canvas::drawBresenhamLine(const QPoint& a, const QPoint& b, const QColor color){
    if (a.x() == b.x() && a.y() == b.y() ) return;
    const int deltaX = abs(b.x() - a.x());
    const int deltaY = abs(b.y() - a.y());
    const int signX = a.x() < b.x() ? 1 : -1;
    const int signY = a.y() < b.y() ? 1 : -1;

    int error = deltaX - deltaY;

    drawPixel(b.x(), b.y(), color);
    int x1 = a.x(), x2 = b.x(), y1 = a.y(), y2 = b.y();

    while(x1 != x2 || y1 != y2) {

        drawPixel(x1, y1, color);
        const int error2 = error * 2;

        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}

void Canvas::setSize(int w, int h){
    width = w;
    height = h;
    image = QImage(w,h,QImage::Format_RGB888);
    clear();
}

void Canvas::clear(){
    image.fill(Qt::white);
}
