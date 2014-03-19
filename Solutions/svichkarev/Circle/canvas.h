#ifndef CANVAS_H
#define CANVAS_H

#include <QColor>

// класс полотна, можем рисовать пикселы
class Canvas{
protected: // TODO: почему не private?
    int width;
    int height;
public:
    explicit Canvas( int w, int h ); // TODO: why explicit?
    virtual ~Canvas();
    virtual void drawPixel( int x, int y, const QColor& color) = 0; // TODO: why?
    virtual int getWidth() const;
    virtual int getHeight() const;
};

#endif // CANVAS_H
