#ifndef EDGE_H
#define EDGE_H

#include "idrawable.h"

#include <QPoint>

class Edge : public iDrawable {
public:
    Edge(){}
    Edge( QPoint p1, QPoint p2 );

    virtual void draw( MQPainter & painter );

    bool isIntersection( Edge & e );

    // чтобы легче было изменять
    QPoint p1, p2;

private:
    // подсчёт площади треугольника, нужна для определения пересечения
    int area( const QPoint & a, const QPoint & b, const QPoint & c );
    bool intersect(int a, int b, int c, int d);
};

#endif // EDGE_H
