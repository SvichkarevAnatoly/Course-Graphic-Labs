#ifndef CIRCLE_H
#define CIRCLE_H

#include "idrawable.h"
#include "drawpanel.h"

#include <QObject>

class DrawPanel;

class Circle : public QObject, public iDrawable{
public:
    static const int DEFAULT_CENTER_X = 0;
    static const int DEFAULT_CENTER_Y = 0;
    static const int DEFAULT_RADIUS   = 20;

private:
    Q_OBJECT
    int centreX;
    int centreY;
    int radius;

public:
    Circle( int x, int y, int r );

    void draw( QImage * backBuffer, const QColor & color );

    void read( const std::string& fileName );
    void save( const std::string& fileName );
signals:
    void changeX( int x );
    void changeY( int y );
    void changeR( int r );

public slots:
    void setX( int x );
    void setY( int y );
    void setR( int r );
};

#endif // CIRCLE_H
