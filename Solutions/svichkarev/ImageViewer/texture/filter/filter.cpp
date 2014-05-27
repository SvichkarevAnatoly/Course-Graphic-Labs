#include "filter.h"
#include "texture/texture.h"
#include <QDebug>
Filter::Filter( )
{
    type = 0;
}

int Filter::getType() {
    return type;
}


QColor Filter::filter(Texture* texture,const TexturedPoint& point) {

    int size = texture->get_size();
    int x = point.getTexX() * (size+1);
    int y = point.getTexY() * (size+1)  ;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= size) x = size-1;
    if (y >= size) y = size-1;
    return texture->get_color(QPoint(x,y));
}
