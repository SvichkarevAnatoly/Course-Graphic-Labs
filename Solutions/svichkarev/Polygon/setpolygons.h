#ifndef SETPOLYGONS_H
#define SETPOLYGONS_H

#include "idrawable.h"
#include "edge.h"

#include <QVector>
#include <QPoint>

class SetPolygons: public iDrawable{
public:
    static const QColor DEFAULT_CONTOUR_COLOR;
    static const QColor DEFAULT_INNER_COLOR;

    SetPolygons();

    virtual void draw( MQPainter & painter );

    QPoint getFirstPointCurrentPolygon();
    QPoint getLastPoint();
    int getNumberEdgeCurrentPolygon();

    void addPoint( QPoint & curPoint );
    void removeLastPoint();

    // проверяет, есть ли рёбра
    bool isEmptyCurrentPolygon();
    // проверяем нет ли самопересечения, если есть, вернёт true, иначе false
    bool isSelfIntersection( QPoint & checkPoint );
    // можно ли замкнуть многоугольник
    bool isNearClose( QPoint & checkPoint, int radius );

private:
    QVector< Edge > edges;
    QVector< int > indexStartingNewPolygon;

    // закрашивание полигона
    void fillPolygon( MQPainter & painter, const QColor & color );
    // заполнение интервалов по текущему ребру
    void createXIntervals( const Edge & curEdge, QVector< QList< int > > & xIntervals, int minY );
};

#endif // SETPOLYGONS_H
