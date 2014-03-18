#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include "circle.h"
#include "canvas.h"
#include <QObject>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>

class DrawPanel : public QWidget, Canvas
{
    Q_OBJECT
    Circle* pCircle;
    QImage backBuffer;
public:
    explicit DrawPanel(int w, int h, int r, QWidget *parent = 0);
    void drawPixel(int x, int y, const RGBColor& color);
    Circle* getCircle() const;
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent (QResizeEvent* event );
    virtual int getWidth() const;
    virtual int getHeight() const;

signals:

public slots:
};

#endif // DRAWPANEL_H
