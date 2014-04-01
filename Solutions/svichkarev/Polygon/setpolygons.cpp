#include "setpolygons.h"

#include <qmath.h>

#include <QDebug> // TODO

SetPolygons::SetPolygons(){
    indexStartingNewPolygon.append( 0 );
}

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

int SetPolygons::getNumberEdgeCurrentPolygon(){
    return (edges.size() - indexStartingNewPolygon.last());
}

void SetPolygons::addPoint( QPoint & curPoint ){
    if( isEmptyCurrentPolygon() ){
        // начальное ребро каждого нового полигона вырожденное
        edges.append( Edge( curPoint, curPoint ) );
    } else{
        edges.append( Edge( getLastPoint(), curPoint ) );
        // определение замыкания
        if( curPoint == getFirstPointCurrentPolygon() ){
            // ставим индекс нового полигона
            indexStartingNewPolygon.append( edges.size() );
        }
    }
}

// TODO: стирать значения и в индексном массиве
void SetPolygons::removeLastPoint(){
    // <=> удалить последнее ребро
    edges.pop_back();
}

// TODO: сделать для текущего полигона
bool SetPolygons::isEmptyCurrentPolygon(){
    if( edges.empty() ){
        return true;
    }
    //qDebug() << edges.size() << indexStartingNewPolygon.last();
    return (edges.size() == indexStartingNewPolygon.last());
}

//TODO: при замыкании будет возникать пересечение, нужно что-то придумать
bool SetPolygons::isSelfIntersection( QPoint & checkPoint ){
    // <=> сравнить текущий отрезок со всеми уже существующими
    if( isEmptyCurrentPolygon() ){
        return false;
    }

    // текущий отрезок
    QPoint lastPoint( getLastPoint() );
    Edge checkEdge( lastPoint, checkPoint );

    // перебор всех существующих, кроме последнего!
    for( int i = 0; i < edges.size()-1; i++ ){
        // TODO: пересечение работает плохо
        if( checkEdge.isIntersection( edges[ i ] ) ){
            return true;
        }
    }

    return false;
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
