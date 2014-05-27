#ifndef BILINEAR_H
#define BILINEAR_H

#include "filter.h"
#include "texture/texturedpoint.h"
#include <QColor>

class Texture;

class Bilinear : public Filter
{
public:
    Bilinear();
    virtual QColor filter(Texture* texture,const TexturedPoint& point );
};

#endif // BILINEAR_H
