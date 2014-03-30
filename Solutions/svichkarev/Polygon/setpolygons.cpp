#include "setpolygons.h"

#include <qmath.h>

void SetPolygons::draw( MQPainter & painter ){
    // TODO:
    // сначала нарисуем все рёбра
    for( int i = 0; i < edges.size(); i++ ){
        edges[ i ].draw( painter );
    }
}

QPoint SetPolygons::getFirstPointCurrentPolygon(){
    return edges[ indexStartingNewPolygon.last() ].p1;
}

QPoint SetPolygons::getLastPoint(){
    return edges.last().p2;
}

void SetPolygons::addPoint( QPoint & curPoint ){
    static QPoint * firstPoint = NULL;
    if( edges.empty() ){
        if( firstPoint == NULL ){
            firstPoint = new QPoint( curPoint );
            return;
        }
        if( *firstPoint != curPoint ){ // TODO:
            indexStartingNewPolygon.append( 0 );
            // TODO: костыль
            edges.append( Edge( *firstPoint, curPoint ) );
        }
    } else{
        edges.append( Edge( getLastPoint(), curPoint ) );
    }
}

// TODO: стирать значения и в индексном массиве
void SetPolygons::removeLastPoint(){
    // <=> удалить последнее ребро
    edges.pop_back();
}

//TODO: при замыкании будет возникать пересечение, нужно что-то придумать
bool SetPolygons::isSelfIntersection( QPoint & checkPoint ){
    // <=> сравнить текущий отрезок со всеми уже существующими
    // текущий отрезок
    if( edges.empty() ){
        return false;
    }

    QPoint lastPoint( getLastPoint() );
    Edge checkEdge( lastPoint, checkPoint );

    // перебор всех существующих, кроме последнего!
    for( int i = 0; i < edges.size()-1; i++ ){
        if( checkEdge.isIntersection( edges[ i ] ) ){
            return true;
        }
    }

    return false;
}

bool SetPolygons::isClose(){
    // TODO: нормальное ли равенство?
    // <=> сравнить первую и последнюю точку в текущем многоугольнике
    if( edges.empty() ){
        return true;
    }

    //TODO:
    QPoint fp = getFirstPointCurrentPolygon();
    QPoint lp = getLastPoint();

    return ( getFirstPointCurrentPolygon() == getLastPoint() );
}

bool SetPolygons::isNearClose( QPoint & checkPoint ){
    QPoint nearVector = getFirstPointCurrentPolygon() - checkPoint;
    double length = sqrt( pow(nearVector.x(), 2) + pow(nearVector.y(), 2) );

    // TODO: константа
    if( length < 20 ){ // внутри окрестности
        return true;
    }

    return false;
}
