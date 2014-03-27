#ifndef POLYGON_H
#define POLYGON_H

#include "idrawable.h"

#include <QImage>

class Polygon: public iDrawable{
public:
    Polygon();

    virtual void draw( QImage * backBuffer, const QColor & color );
};

#endif // POLYGON_H
