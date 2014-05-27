#ifndef MIPMAPPER_H
#define MIPMAPPER_H

#include "filter.h"
#include "bilinear.h"
#include "texture/texturedpoint.h"
#include <QColor>

class Texture;

class Mipmapper : public Filter
{
private:
    static double L1_THRESHOLD;
    static double L2_THRESHOLD;
    static double L3_THRESHOLD;
    static double L4_THRESHOLD;


    QColor bilinear(Texture* texture, const TexturedPoint& point, int level);
public:
    Mipmapper();
    QColor filter(Texture* texture, const TexturedPoint& point );
};

#endif // MIPMAPPER_H
