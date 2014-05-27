#include <QDebug>
#include "triangle.h"
#include "edge.h"
#include <cmath>

const double Triangle::RAD_IN_GRAD = M_PI / 180.0;
const double Triangle::MIN_SCALE_X = 0.0;
const double Triangle::MAX_SCALE_X = 10.0;
const double Triangle::MIN_SCALE_Y = 0.0;
const double Triangle::MAX_SCALE_Y = 10.0;
const double Triangle::MAX_ANGLE = 360.0;
const double Triangle::DEFAULT_SCALE_X = 1.0;
const double Triangle::DEFAULT_SCALE_Y = 1.0;

Triangle::Triangle()
{
}


void Triangle::changePoints(const TexturedPoint& a, const TexturedPoint& b, const TexturedPoint& c){
    points.clear();
    points.push_back(a);
    points.push_back(b);
    points.push_back(c);
    currAngle = 0;
    currScaleX = DEFAULT_SCALE_X;
    currScaleY = DEFAULT_SCALE_Y;
    rotCenterX = (a.x() + b.x() + c.x())/3.;
    rotCenterY = (a.y() + b.y() + c.y())/3.;
}

void Triangle::setRotateCenter(double xc, double yc){
    rotCenterX = xc;
    rotCenterY = yc;
//TODO: emit ?
}

void Triangle::scaleX(double q){
    currScaleX = q;
}

void Triangle::scaleY(double q){
    currScaleY = q;
}


void Triangle::rotate(double angle) {
    currAngle = angle;
}


void Triangle::setMaxX(int maxX){
    this->maxX = maxX;
}

void Triangle::setMaxY(int maxY){
    this->maxY = maxY;
}

void Triangle::transform(std::vector<TexturedPoint> &new_points){
    double tr_mat[3][2];    
    double radians = currAngle * RAD_IN_GRAD;// TODO : radians теряет точность
    double sinval = sin(radians);
    double cosval = cos(radians);
    tr_mat[0][0] = currScaleX * cosval;
    tr_mat[0][1] = currScaleX * sinval;
    tr_mat[1][0] = -currScaleY * sinval;
    tr_mat[1][1] = currScaleY * cosval;
    tr_mat[2][0] = rotCenterX*(1-currScaleX*cosval) + currScaleY * rotCenterY*sinval;
    tr_mat[2][1] = rotCenterY*(1-currScaleY*cosval) - currScaleX * rotCenterX*sinval;

    for (int i = 0; i < (int) points.size(); ++i) {
        double x0 = points[i].x();
        double y0 = points[i].y();

        double x = tr_mat[0][0]*x0+ tr_mat[1][0]*y0+tr_mat[2][0];
        double y = tr_mat[0][1]*x0+ tr_mat[1][1]*y0+tr_mat[2][1];

        TexturedPoint new_point(x,y, points[i].getTexX(), points[i].getTexY());
        new_points.push_back(new_point);
    }
}

void Triangle::draw(Canvas& canvas, Texture* texture = 0) {
    std::vector<TexturedPoint> points;
    transform(points);
    std::sort(points.begin(), points.end());

    std::vector<Edge> edges;

    int minY = (points.front().y() < 0) ? 0: points.front().y();
    int maxY = (points.back().y() < this->maxY) ? points.back().y() : this->maxY - 1;

    int curY = minY;
    int i = 0;

    while (curY < maxY) {
        int nextY = maxY;

        while ( i != (int)points.size() && trunc( points[i].y()) <= curY ){
            TexturedPoint a = points[i];
            TexturedPoint b = points[(points.size() - i - 1 ) % points.size()];
            TexturedPoint c = points[(i + 1) % points.size()];

            if (b.y() > curY ) {
                edges.push_back(Edge(a,b));
                if ( b.y() < nextY ) {
                    nextY = b.y() ;
                }
            }
            if (c.y() > curY) {
                edges.push_back(Edge(a,c));
                if ( c.y() < nextY) {
                    nextY = c.y();
                }
            }
            ++i;
        }

        while(curY <= nextY && curY <= maxY) {

            std::vector<TexturedPoint> borderX;
            for (int i = 0; i < (int)edges.size(); ++i) {
                int n = curY - edges[i].getA().y();
                double curX = (edges[i].getA().x()) + n * edges[i].getK();
                TexturedPoint texCoord(curX, curY);
                texCoord.calcTextureCoordinates(edges[i].getA(), edges[i].getB());
                borderX.push_back(texCoord);
            }

            std::sort(borderX.begin(), borderX.end(), TexturedPoint::compX);
            int begin = borderX.front().x() > 0 ? borderX.front().x() : 0;

            for (int x = begin; x < borderX.back().x() && x < maxX; ++x) {
                TexturedPoint curPoint(x, curY);

                curPoint.calcTextureCoordinates(borderX.front(),borderX.back());

                if (0 == texture) {

                    canvas.drawPixel(x, curY, TexturedPoint::transformToColor(curPoint.getTexX(), curPoint.getTexY()));
                }
                else {

                    canvas.drawPixel(x, curY, texture->get_color(curPoint));
                }
            }

            ++curY;
        }

        std::vector<Edge>::iterator iter = edges.begin();
        while (iter != edges.end()) {
           if ( (*iter).getB().y() < curY) {
               edges.erase(iter);
           }
           else {
               ++iter;
           }
        }

   }
}
