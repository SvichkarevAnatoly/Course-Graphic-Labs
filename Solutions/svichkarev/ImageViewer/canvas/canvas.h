#ifndef CANVAS_H
#define CANVAS_H

#include <QImage>
#include <QColor>
#include <QPoint>
/*
 * QImage
 * drawPixel
 * drawLine
 */


class Canvas
{
protected:
    int width;
    int height;
    QImage image;
public:
    Canvas(const int width, const int height);
    Canvas(const Canvas& other);
    Canvas& operator=(const Canvas& c);
    virtual ~Canvas();
    const QImage& getImage() const;
    virtual void drawPixel(const int x, const int y, const QColor color = Qt::black);
    virtual void drawBresenhamLine(const QPoint& a, const QPoint& b, const QColor color = Qt::black);
    void setSize(int w, int h);
    void clear();
    int getWidth();
    int getHeight();
};

#endif // CANVAS_H
