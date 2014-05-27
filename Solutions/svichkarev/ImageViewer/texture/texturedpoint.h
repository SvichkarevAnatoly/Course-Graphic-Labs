#ifndef TEXTUREDPOINT_H
#define TEXTUREDPOINT_H

#include <QPointF>
#include <QColor>
#include <cmath>

class TexturedPoint : public QPointF
{
private:
    double texX;
    double texY;
    double tex_in_pixX;
    double tex_in_pixY;
private:
    void set_textured_coord(const TexturedPoint& a, const TexturedPoint& b);
public:
    TexturedPoint(double X,  double Y, double texX, double texY);
    TexturedPoint(double X,  double Y);

    void calcTextureCoordinates(const TexturedPoint& a, const TexturedPoint& b);
    double getTexX() const;
    double getTexY() const;
    double get_tex_in_pixX() const;
    double get_tex_in_pixY() const;
    void setTexX(double value);
    void setTexY(double value);

    static QColor transformToColor(double tx, double ty);
    static bool compX(const TexturedPoint& a, const TexturedPoint& b);

    friend bool operator<(const TexturedPoint& a, const TexturedPoint& b)  {
        return a.y() < b.y();
    }


private:
    static double norm(double x, double y) {
        return sqrt(pow(x, 2)+pow(y,2));
    }

    static const double INVALID = -1;
};

#endif // TEXTUREDPOINT_H
