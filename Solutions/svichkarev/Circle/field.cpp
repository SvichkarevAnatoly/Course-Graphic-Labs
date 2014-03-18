#include <fstream>
#include <ios>
#include <cstring>
#include <QImage>
#include <QIODevice>
#include <QDebug>
#include <QByteArray>
#include <QBuffer>
#include "field.h"

// FOR CONSOLE
Field::Field(int w, int h) : Canvas(w,h), image(w,h,QImage::Format_RGB888)
{
    memset(image.bits(), 0, image.bytesPerLine()*image.height());
}
Field::~Field() {
}


void Field::save(const std::string& fileName) {
    try {
        image.save(QString(fileName.c_str()), "PNG");

    }
    catch (...) {

        // TODO : handle exception
        qDebug() << "err";
    }


}

void Field::drawPixel(int x, int y, const RGBColor& color) {
    image.bits()[y * this->width*3 + x*3    ] = color.R;
    image.bits()[y * this->width*3 + x*3 + 1] = color.G;
    image.bits()[y * this->width*3 + x*3 + 2] = color.B;

}
