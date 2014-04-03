#include "setpolygons.h"

#include "aetedge.h"

#include <qmath.h>

#include <QDebug>

// TODO: цвета
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

    // нарисуем все рёбра
    for( int i = 0; i < edges.size(); i++ ){
        edges[ i ].draw( painter );
    }

    painter.setColor( DEFAULT_CONTOUR_COLOR );
}

// TODO: можно поддерживать состояние служебного списка AET с основным,
//а не создавать новый каждый раз, но тогда нужны механизмы синхронизации
// TODO: заполнять служебный список вместе с основным
// алгоритм со списком активных рёбер(AET)
void SetPolygons::fillPolygon( MQPainter & painter, const QColor & color ){
    // закрашиваем только замкнутые полигоны

    // вначале создаём копию массива рёбер и упорядочиваем
    //каждое ребро, чтобы меньший у был первым,
    //затем все рёбра по первому у
    int minY = INT_MAX;
    int maxY = INT_MIN;
    QVector< Edge > copyEdges;

    int j = 0;
    for( int i = 0; i < indexStartingNewPolygon.last(); i++ ){
        // не добавляем первые вырожденные рёбра
        if( i == indexStartingNewPolygon[j]  ){
            j++;
        } else{
            Edge curEdge = edges[ i ];
            // если нужно перевернуть - переворачиваем
            if( curEdge.p1.y() > curEdge.p2.y() ){
                std::swap( curEdge.p1, curEdge.p2 );
            }

            // находим минимум, для точки начала алгоритма
            if( curEdge.p1.y() < minY ){
                minY = curEdge.p1.y();
            }

            if( curEdge.p2.y() > maxY ){
                maxY = curEdge.p2.y();
            }

            // копируем в служебный
            copyEdges.append( curEdge );
        }
    }

    // сортировка по y
    qSort( copyEdges );

    QVector< AETEdge > aet;
    int yNext;

    QVector< Edge >::ConstIterator it = copyEdges.begin();
    // основной цикл по строкам
    int curY = minY;
    while( curY < maxY ){ //TODO
        // определение yNext
        yNext = INT_MAX;
        // добавление новых рёбер в AET
        while( curY == it->p1.y() ){
            // горизонтальные рёбра сразу отрисовываем
            if( it->p1.y() == it->p2.y() ){// TODO: использовать swap
                if( it->p1.x() <= it->p2.x() ){ // определяем х начальное
                    painter.drawLine( curY, it->p1.x(), it->p2.x(), color );
                }else{
                    painter.drawLine( curY, it->p2.x(), it->p1.x(), color );
                }
            } else{
                aet.append( AETEdge( it->p2.y(), (double)( it->p2.x() - it->p1.x() ) / ( it->p2.y() - it->p1.y() ), it->p1.x() ) );
                if( it->p2.y() < yNext ){
                    yNext = it->p2.y();
                }
            }
            ++it;
        }

        // перепроверяем следующий ближайший yNext по активным рёбрам
        QVector< AETEdge >::Iterator it2 = aet.begin();
        while( it2 != aet.end() ){
            if( it2->yEnd < yNext ){
                yNext = it2->yEnd;
            }

            ++it2;
        }

        // проверим начало ближайшего следующего ребра, может быть ближе,
        //чем ближайший конец из активного списка
        if( ( it != copyEdges.end() ) && (it->p1.y() < yNext) ){
            // но не забудем прошлого значения, потом может быть ближайшим
            yNext = it->p1.y();
        }

        // не заботимся о y, просто инкрементируем
        while( curY < yNext ){
            QVector< int > xInterval;

            QVector< AETEdge >::Iterator itEdge = aet.begin();
            for( ; itEdge != aet.end(); ++itEdge ){
                xInterval.append( (int)itEdge->xCurrent );
                itEdge->xCurrent += itEdge->dx;
            }
            qSort( xInterval );

            QVector< int >::const_iterator itX = xInterval.begin();
            while( itX != xInterval.end() ){
                int start = *itX;
                ++itX;
                int end = *itX;

                // отрисовать линию
                painter.drawLine( curY, start, end, color );

                ++itX;
            }

            curY++;
        }

        // выкинуть все рёбра из AET, которые закончились
        QVector< AETEdge >::Iterator it = aet.begin();
        while( it != aet.end() ){
            if( curY == it->yEnd ){
                it = aet.erase( it );
            } else{
                ++it;
            }
        }
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

QList< QPoint > SetPolygons::getListCurrentPoints(){
    QList< QPoint > listPoints;

    foreach ( const Edge edge , edges) {
        listPoints.append( edge.p2 );
    }

    return listPoints;
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

void SetPolygons::removeLastPoint(){
    // <=> удалить последнее ребро
    if( ! edges.empty() ){
        if( isEmptyCurrentPolygon() ){
            indexStartingNewPolygon.pop_back();
        }
        edges.pop_back();
    }
}

void SetPolygons::removeAll(){
    while( ! edges.empty() ){
        removeLastPoint();
    }
}

bool SetPolygons::isEmptyCurrentPolygon(){
    if( edges.empty() ){
        return true;
    }
    return (edges.size() == indexStartingNewPolygon.last());
}

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

    if( length < radius ){ // внутри окрестности
        return true;
    }

    return false;
}
