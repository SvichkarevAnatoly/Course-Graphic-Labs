#include "bilinear.h"
#include "texture/texture.h"
#include <cmath>
#include <QDebug>

Bilinear::Bilinear(){
    this->type = 1;
}


QColor Bilinear::filter(Texture* texture, const TexturedPoint& point ){
    int size = texture->get_size();
    if (!texture)
        return QColor();
    double fx = point.getTexX() * size;
    double fy = point.getTexY() * size;

    if (fx >= size) fx =size-1;
    if (fy >= size) fy =size-1;
    if (fx < 0) fx = 0;
    if (fy < 0) fy = 0;

    int ix = fx;
    int iy = fy;
    fx = fx - ix;
    fy = fy - iy;

    double x_opp = fx;
    double y_opp = fy;
    fx = 1. - x_opp;
    fy = 1. - y_opp;

    if (ix != size -1 && iy != size -1 ){

        QColor p1 = texture->get_color(QPoint(ix  , iy  ));
        QColor p2 = texture->get_color(QPoint(ix+1, iy  ));
        QColor p3 = texture->get_color(QPoint(ix  , iy+1));
        QColor p4 = texture->get_color(QPoint(ix+1, iy+1));

        QColor a, b, c;

        a.setRed  ( p2.red()  * x_opp + p1.red()  * fx);
        a.setGreen( p2.green()* x_opp + p1.green()* fx);
        a.setBlue ( p2.blue() * x_opp + p1.blue() * fx);

        b.setRed  ( p4.red()  * x_opp + p3.red()  * fx);
        b.setGreen( p4.green()* x_opp + p3.green()* fx);
        b.setBlue ( p4.blue() * x_opp + p3.blue() * fx);

        c.setRed  ( b.red()  * y_opp + a.red()  * fy);
        c.setGreen( b.green()* y_opp + a.green()* fy);
        c.setBlue ( b.blue() * y_opp + a.blue() * fy);

        return c;
    }

    return texture->get_color(QPoint(ix,iy));
}
