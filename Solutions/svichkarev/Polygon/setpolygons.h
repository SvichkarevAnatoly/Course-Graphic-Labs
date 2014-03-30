#ifndef SETPOLYGONS_H
#define SETPOLYGONS_H

#include "idrawable.h"
#include "edge.h"

#include <QVector>
#include <QPoint>

class SetPolygons: public iDrawable{
public:
    virtual void draw( MQPainter & painter );

    QPoint getFirstPointCurrentPolygon();
    QPoint getLastPoint();

    void addPoint( QPoint & curPoint ); //TODO:
    void removeLastPoint();

    // проверяем нет ли самопересечения, если есть, вернёт true, иначе false
    bool isSelfIntersection( QPoint & checkPoint ); //TODO
    // проверка на замкнутость последнего многоугольника
    bool isClose();
    // можно ли замкнуть многоугольник
    bool isNearClose( QPoint & checkPoint );

private:
    QVector< Edge > edges;
    QVector< int > indexStartingNewPolygon;

};

#endif // SETPOLYGONS_H
