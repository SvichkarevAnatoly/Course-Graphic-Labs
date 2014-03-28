#ifndef EDGE_H
#define EDGE_H

#include <QPoint>

class Edge{
public:
    Edge();
    Edge( QPoint & p1, QPoint & p2 );
    virtual ~Edge();

    QPoint p1, p2;
};

#endif // EDGE_H
