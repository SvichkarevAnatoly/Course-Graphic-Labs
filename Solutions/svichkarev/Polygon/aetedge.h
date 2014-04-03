#ifndef AETEDGE_H
#define AETEDGE_H

class AETEdge
{
public:
    AETEdge();
    AETEdge( int _yEnd, double _dx, int _xStart);

public: // TODO
    int yEnd;
    double dx;
    double xCurrent;
};

#endif // AETEDGE_H
