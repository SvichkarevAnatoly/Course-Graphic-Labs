#ifndef POLYGON_H
#define POLYGON_H

#include "idrawable.h"
#include "edge.h"

#include <QImage>
#include <QPoint>
#include <QList>
#include <QVector>

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
    // список точек
    QList< Edge > edgesList;
    // для закрашиваемых интервалов
    QVector< QList< int > > * xIntervals;
    int minY;

    // флаг возможности заливки многоугольника
    bool canFillPolygon;

    // заполнение списка рёбер из списка вершин
    void createEdgeList();
    // закрашивание полигона
    void fillPolygon( QImage * backBuffer, const QColor & color );
    // заполнение интервалов по текущему ребру
    void createXIntervals( const Edge & curEdge );
    // закрасить линию
    void drawLine( int y, int startX, int endX, QImage * backBuffer, const QColor & color );
};

#endif // POLYGON_H
