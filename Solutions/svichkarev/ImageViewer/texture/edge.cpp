#include <QDebug>
#include "edge.h"

Edge::Edge(const TexturedPoint &a, const TexturedPoint &b) : a(a), b(b)
{

    if (a.y() > b.y()) {
        std::swap(this->a,this->b);
    }

    if(b.y() == a.y()){
        k = 0;
    } else
        k = (this->b.x() - this->a.x()) *1.0/ (this->b.y() - this->a.y());
}

double Edge::getK() const {
    return k;
}

TexturedPoint Edge::getB() const
{
    return b;
}


TexturedPoint Edge::getA() const
{
    return a;
}

