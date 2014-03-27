#ifndef POLYGON_H
#define POLYGON_H

#include "idrawable.h"

#include <QImage>
#include <QPoint>

class Polygon: public iDrawable{
public:
    Polygon();
    virtual ~Polygon();

    virtual void draw( QImage * backBuffer, const QColor & color, QPainter & painter );

    // добавление новой точки отрезка
    void append( QPoint & newPoint );
    // замыкание текущего многоугольника
    void closePolygon();
    // удаление последней точки отрезка
    void removeLast();

    // возвращает число точек
    int getNumberPoints() const;
    // возвращает первую точку будущего многоугольника
    const QPoint & getFirstPointCurrentPolygon() const;

private:
    // список точек
    QList< QPoint > pointsList;
};

#endif // POLYGON_H
