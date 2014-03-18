#ifndef CIRCLE_H
#define CIRCLE_H

#include "canvas.h"
#include <QObject>

class Circle : public QObject
{
    Q_OBJECT
    int centreX;
    int centreY;
    int radius;

    int w;
    int h;
public:
    explicit Circle(int x, int y, int r, QObject *parent = 0);
    void draw(Canvas* pBackBuffer, const QColor& color);
    void read(const std::string& fileName);
    void save(const std::string& fileName);
    int getW() const;
    int getH() const;

signals:
    void changeX(int x);
    void changeY(int y);
    void changeR(int r);

public slots:
    void setX(int x);
    void setY(int y);
    void setR(int r);
};

#endif // CIRCLE_H
