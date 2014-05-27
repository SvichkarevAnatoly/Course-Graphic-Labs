#ifndef EDGE_H
#define EDGE_H

#include "texturedpoint.h"

class Edge
{
private:
    TexturedPoint a;
    TexturedPoint b;
    double k;
public:
    Edge(const TexturedPoint& a, const TexturedPoint& b);

    TexturedPoint getA() const;
    TexturedPoint getB() const;

    double getK() const;

    // сравнение двух рёбер по первой точке
    friend bool operator<(const Edge& a, const Edge& b)  {
        return a.getA() < b.getA();
    }
};

#endif // EDGE_H
