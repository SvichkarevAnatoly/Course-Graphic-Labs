#ifndef INTERFACE_DRAWABLE_H
#define INTERFACE_DRAWABLE_H

#include "mqpainter.h"

class iDrawable{
public:
    virtual void draw( MQPainter & painter ) = 0;
};

#endif // INTERFACE_DRAWABLE_H
