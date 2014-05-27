#include <QDebug>
#include "texturedpoint.h"
#include <cmath>

TexturedPoint::TexturedPoint(double X, double Y):QPointF(X,Y)
{
    texX = INVALID;
    texY = INVALID;
}

TexturedPoint::TexturedPoint(double X, double Y, double texX, double texY)
    : QPointF(X, Y), texX(texX), texY(texY)
{

}


double TexturedPoint::getTexY() const
{
    return texY;
}

void TexturedPoint::setTexY(double value)
{
    texY = value;
}

double TexturedPoint::getTexX() const
{
    return texX;
}

void TexturedPoint::setTexX(double value)
{
    texX = value;
}

bool TexturedPoint::compX(const TexturedPoint &a, const TexturedPoint &b){
    return a.x() < b.x();
}

QColor TexturedPoint::transformToColor(double xt, double yt) {
    int r = floor(xt >= 1.0 ? 255 : fabs(xt) * 256.0);
    int g = floor(yt >= 1.0 ? 255 : fabs(yt) * 256.0);

   return QColor(r, g, 0);
}

double TexturedPoint::get_tex_in_pixX()const{
    return tex_in_pixX;
}

double TexturedPoint::get_tex_in_pixY()const{
    return tex_in_pixY;
}

void TexturedPoint::set_textured_coord(const TexturedPoint &a, const TexturedPoint &b){
    double ab_norm = norm(b.x() - a.x(), b.y() - a.y());
    double ab_tex_norm =  norm(b.getTexX() - a.getTexX(), b.getTexY() - a.getTexY());
    if (0 == ab_norm){
        // TODO:
        texX = a.getTexX();
        texY = a.getTexY();
        return;
    }
    double length = norm(x() - a.x(), y() - a.y());
    double vector_length = length / ab_norm * ab_tex_norm;

    texX = (b.getTexX() - a.getTexX())* vector_length / ab_tex_norm + a.getTexX();
    texY = (b.getTexY() - a.getTexY())* vector_length / ab_tex_norm + a.getTexY();
}

void TexturedPoint::calcTextureCoordinates(const TexturedPoint& a, const TexturedPoint& b){
    TexturedPoint neighbour(x()+1, y());
    set_textured_coord(a, b);
    neighbour.set_textured_coord(a,b);

    tex_in_pixX =  (neighbour.texX - texX);
    tex_in_pixY =  (neighbour.texY - texY);


}


