#include "setpolygons.h"

#include <qmath.h>

const QColor SetPolygons::DEFAULT_CONTOUR_COLOR( 79, 192, 178 );
const QColor SetPolygons::DEFAULT_INNER_COLOR( 97, 156, 178 );

SetPolygons::SetPolygons(){
    indexStartingNewPolygon.append( 0 );
}

void SetPolygons::draw( MQPainter & painter ){
    if( indexStartingNewPolygon.size() > 1 ){
        // запустим алгоритм закраски
        fillPolygon( painter, DEFAULT_CONTOUR_COLOR );
    }

    painter.setColor( DEFAULT_INNER_COLOR );

    // сначала нарисуем все рёбра
    for( int i = 0; i < edges.size(); i++ ){
        edges[ i ].draw( painter );
    }

    painter.setColor( DEFAULT_CONTOUR_COLOR );
}

// TODO: простой алгоритм
void SetPolygons::fillPolygon( MQPainter & painter, const QColor & color ){
    // закрашиваем только замкнутые полигоны

    // вначале создаём копию массива рёбер и упорядочиваем
    //каждое ребро, чтобы меньший у был первым,
    //затем все рёбра по первому у
    QList< Edge > copyEdges;
    int maxY = -5000;
    int minY = 5000;

    int j = 0;
    for( int i = 0; i < indexStartingNewPolygon.last(); i++ ){
        // не добавляем первые вырожденные рёбра
        if( i == indexStartingNewPolygon[j]  ){
            j++;
        } else{
            Edge & curEdge = edges[ i ];
            // если нужно перевернуть - переворачиваем
            if( curEdge.p1.y() > curEdge.p2.y() ){
                std::swap( curEdge.p1, curEdge.p2 );
            }

            // находим минимум и максимум, для создания вектора интервалов
            if( curEdge.p2.y() > maxY ){
                maxY = curEdge.p2.y();
            }

            if( curEdge.p1.y() < minY ){
                minY = curEdge.p1.y();
            }

            // копируем в служебный
            copyEdges.append( curEdge );
        }
    }

    // для закрашиваемых интервалов
    QVector< QList< int > > xIntervals( maxY - minY );

    QList< Edge >::const_iterator it = copyEdges.begin();
    // для каждого ребра
    while(it != copyEdges.end()) {
        createXIntervals( *it, xIntervals, minY );

        it++;
    }

    // выполним сортировку по каждому
    QVector< QList< int > >::iterator it2 = xIntervals.begin();
    // для каждого ребра
    while(it2 != xIntervals.end()) {
        qSort( *it2 );
        it2++;
    }

    // начинаем закрашивать
    int curY = minY;
    foreach( const QList<int> interval, xIntervals ){
        QList<int>::const_iterator it = interval.begin();

        while( it != interval.end() ){
            int start = *it;
            ++it;
            int end = *it;

            // отрисовать линию
            painter.drawLine( curY, start, end, color );

            ++it;
            if( it == interval.end() ){
                break;
            }
        }

        curY++;
    }
}

void SetPolygons::createXIntervals( const Edge & curEdge, QVector< QList< int > > & xIntervals, int minY ){
    int y = curEdge.p1.y();
    double dx = 1.0 * ( curEdge.p2.x() - curEdge.p1.x() ) / ( curEdge.p2.y() - curEdge.p1.y() );
    double x = curEdge.p1.x() + dx;

    while ( y < curEdge.p2.y() ) {
        // добавляем в список интервалов
        xIntervals[ y - minY ].append( (int)x );

        y++;
        x += dx;
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
    int result = 0;
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
            result++;
        }
    }

    // если это замыкание, т.е. точки совпадают(+вырожденное ребро), то это не самопересечение
    if( (result == 2) && (checkPoint == getFirstPointCurrentPolygon()) ){
        result = 0;
    }

    return (result != 0);
}

bool SetPolygons::isNearClose( QPoint & checkPoint, int radius ){
    // TODO: в левой половине круга почему-то не работает
    QPoint nearVector = getFirstPointCurrentPolygon() - checkPoint;
    double length = sqrt( pow(nearVector.x(), 2) + pow(nearVector.y(), 2) );

    // TODO: константа
    if( length < radius ){ // внутри окрестности
        return true;
    }

    return false;
}
