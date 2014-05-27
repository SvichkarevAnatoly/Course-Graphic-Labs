#include "mipmapper.h"
#include "texture/texture.h"
#include <QDebug>



double Mipmapper::L1_THRESHOLD = 0.6;
double Mipmapper::L2_THRESHOLD = 0.35;
double Mipmapper::L3_THRESHOLD = 0.15;
double Mipmapper::L4_THRESHOLD = 0.05;

Mipmapper::Mipmapper()
{
    this->type = 2;
}

QColor Mipmapper::filter(Texture *texture, const TexturedPoint &point ){

    int level = 0;

    double scaleX = texture->getScaleX();
    double scaleY = texture->getScaleY();

    double scale = std::min(scaleX, scaleY);

    // scale [0;1] [1;10]
    if (scale >= 1) {
        level = 0;
    }
    else {
        // level
        if (scale <= L4_THRESHOLD){
            level = 4;
        }
        if (scale <= L3_THRESHOLD){
            level = 3;
        }
        else
        if (scale <= L2_THRESHOLD) {
            level = 2;
        }
        else
        if (scale <= L1_THRESHOLD) {
            level = 1;
        }
        else {
            level = 0;
        }
    }
    return bilinear(texture, point, level);
}

QColor Mipmapper::bilinear(Texture* texture, const TexturedPoint& point, int level){
    int size = texture->get_LOD(level).width();
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

    const QImage& LOD = texture->get_LOD(level);

    int dx = 1, dy = 1;
    if (ix >= size -1) dx=-1;
    if (iy >= size -1) dy=-1;

   // if (ix != size -1 && iy != size -1 )
    {

        QColor p1 = LOD.pixel(ix  , iy);
        QColor p2 = LOD.pixel(ix+dx, iy);
        QColor p3 = LOD.pixel(ix  , iy+dy);
        QColor p4 = LOD.pixel(ix+dx, iy+dy);

        QColor a, b, c;

        a.setRed( p2.red() * x_opp + p1.red()*fx);
        b.setRed( p4.red() * x_opp + p3.red()*fx);
        c.setRed(b.red()*y_opp + a.red()*fy);

        a.setGreen( p2.green() * x_opp + p1.green()*fx);
        b.setGreen( p4.green() * x_opp + p3.green()*fx);
        c.setGreen(b.green()*y_opp + a.green()*fy);

        a.setBlue( p2.blue() * x_opp + p1.blue()*fx);
        b.setBlue( p4.blue() * x_opp + p3.blue()*fx);
        c.setBlue(b.blue()*y_opp + a.blue()*fy);

        return c;
    }

    //return LOD.pixel(ix, iy);
}
