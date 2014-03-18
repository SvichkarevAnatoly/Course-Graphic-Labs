#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <QImage>
#include "canvas.h"

class Field : public Canvas
{
    QImage image;
public:
    Field(int w, int h);
    ~Field();
    void setW(int w);
    void setH(int h);

    void save(const std::string & fileName);
    void drawPixel(int x, int y, const RGBColor& color);
};

#endif // FIELD_H
