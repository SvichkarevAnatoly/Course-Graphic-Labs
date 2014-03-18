#ifndef CANVAS_H
#define CANVAS_H

#include "rgbcolor.h"

class Canvas
{

protected:
    int width;
    int height;
public:
    explicit Canvas(int w, int h);
    virtual ~Canvas();
    virtual void drawPixel(int x, int y, const RGBColor& color) = 0;
    virtual int getWidth() const;
    virtual int getHeight() const;

};

#endif // CANVAS_H
