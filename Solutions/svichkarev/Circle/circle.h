#ifndef CIRCLE_H
#define CIRCLE_H

#include "canvas.h"
#include <QObject>

class Circle : public QObject
{
    Q_OBJECT
    int centreX;
    int centreY;
    int radius;

    // TODO: почему мы храним параметры холста в круге
    int w;
    int h;
public:
    explicit Circle( int x, int y, int r, QObject *parent = 0 );
    void draw( Canvas* pBackBuffer, const QColor& color );
    void read( const std::string& fileName );
    void save( const std::string& fileName );

    // зачем эти методы?
    int getW() const;
    int getH() const;

signals:
    void changeX(int x);
    void changeY(int y);
    void changeR(int r);

public slots:
    void setX(int x);
    void setY(int y);
    void setR(int r);
};

#endif // CIRCLE_H
