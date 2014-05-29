#include "edge.h"

Edge::Edge( QPoint np1, QPoint np2 ):
    p1( np1 ), p2( np2 )
{
}

void Edge::draw( MQPainter & painter ){
    painter.drawLine( p1, p2 );
}

int Edge::area( const QPoint & a, const QPoint & b, const QPoint & c ){
    return (b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x());
}

bool Edge::intersect( int a, int b, int c, int d ){
    if( a > b )  std::swap( a, b );
    if( c > d )  std::swap( c, d );
    return std::max( a, c ) <= std::min( b, d );
}

bool Edge::isIntersection( Edge & e ){
    QPoint a( e.p1 );
    QPoint b( e.p2 );
    QPoint c( p1 );
    QPoint d( p2 );

    return intersect( a.x(), b.x(), c.x(), d.x() )
            && intersect( a.y(), b.y(), c.y(), d.y() )
            && area( a, b, c ) * area( a, b, d ) <= 0
            && area( c, d, a) * area( c, d, b ) <= 0;

    /*struct pt {
        int x, y;
    };

    inline int area (pt a, pt b, pt c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    inline bool intersect_1 (int a, int b, int c, int d) {
        if (a > b)  swap (a, b);
        if (c > d)  swap (c, d);
        return max(a,c) <= min(b,d);
    }

    bool intersect (pt a, pt b, pt c, pt d) {
        return intersect_1 (a.x, b.x, c.x, d.x)
            && intersect_1 (a.y, b.y, c.y, d.y)
            && area(a,b,c) * area(a,b,d) <= 0
            && area(c,d,a) * area(c,d,b) <= 0;
    }*/

}
