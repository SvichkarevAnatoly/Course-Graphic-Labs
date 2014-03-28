#include "polygon.h"

#include <QPen>

#include <QDebug> // TODO: убрать

Polygon::Polygon():
    canFillPolygon(false)
{
}

Polygon::~Polygon(){
    delete xIntervals;
}

void Polygon::draw( QImage * backBuffer, const QColor & color, QPainter & painter ){
    if( !backBuffer ){ // TODO: надо кидать исключение
        return;
    }

    backBuffer->fill( Qt::white );
    //painter.drawImage(0,0,*backBuffer);

    if( pointsList.size() >= 2 ){
        QPen pen( Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen( pen );

        QList<QPoint>::const_iterator it = pointsList.begin();
        QPoint start = *it;
        it++;
        while(it != pointsList.end()) {
            QPoint end = *it;

            // TODO подправить
            QPoint end1( end );
            QPoint start1( start );
            start1.setX( start.x() + backBuffer->width()/2 );
            start1.setY( start.y() + backBuffer->height()/2 );
            end1.setX( end.x() + backBuffer->width()/2 );
            end1.setY( end.y() + backBuffer->height()/2 );

            painter.drawLine( start1, end1 );
            start = end;
            it++;
        }
    }

    if( canFillPolygon ){
        // собственно здесь вся движуха лабы
        //TODO:
        createEdgeList();
        fillPolygon( backBuffer, color );
    }
}

void Polygon::createEdgeList(){
    QList<QPoint>::const_iterator it = pointsList.begin();
    QPoint start = *it;
    it++;
    Edge * newEdge;

    // TODO:
    int maxY = -5000;
    minY = 5000;

    while(it != pointsList.end()) {
        QPoint end = *it;

        // нужно упорядочить ребро, чтобы начальная точка по у была выше
        // TODO: нет аналога в QT?
        if( end.y() < start.y() ){ // TODO
            //qDebug() << "do swap: " << start.y() << " " << end.y(); //TODO
            std::swap( start, end );
            //qDebug() << "posle swap: " << start.y() << " " << end.y(); //TODO
        }

        // находим минимум и максимум, для создания вектора интервалов
        if( end.y() > maxY ){
            maxY = end.y();
        }
        //qDebug() << "curMax: " << maxY;
        if( start.y() < minY ){
            minY = start.y();
        }
        //qDebug() << "curMin: " << minY;

        // добавляем ребро в список рёбер
        newEdge = new Edge( start, end );
        edgesList.append( *newEdge );

        start = end;
        it++;
    }

    xIntervals = new QVector< QList< int > >( maxY - minY );
}

void Polygon::createXIntervals( const Edge & curEdge ){
    int y = curEdge.p1.y();
    double dx = 1.0 * ( curEdge.p2.x() - curEdge.p1.x() ) / ( curEdge.p2.y() - curEdge.p1.y() );
    double x = curEdge.p1.x() + dx;

    while ( y < curEdge.p2.y() ) {
        // добавляем в список интервалов
        (*xIntervals)[ y - minY ].append( (int)x );

        y++;
        x += dx;
    }
}

void Polygon::fillPolygon( QImage * backBuffer, const QColor & color ){
    QList< Edge >::const_iterator it = edgesList.begin();
    // для каждого ребра
    while(it != edgesList.end()) {
        createXIntervals( *it );

        it++;
    }

    //qDebug() << edgesList.size();

    // выполним сортировку по каждому
    foreach( QList<int> interval, *xIntervals ){
        //qDebug() << interval;
        qSort( interval );
        qDebug() << interval;
    }

    // начинаем закрашивать
    int curY = minY;
    foreach( const QList<int> interval, *xIntervals ){
        QList<int>::const_iterator it = interval.begin();

        while( it != interval.end() ){
            int start = *it;
            ++it;
            int end = *it;

            // отрисовать линию
            drawLine( curY, start, end, backBuffer, color );

            ++it;
            if( it == interval.end() ){
                break;
            }
            ++it;
        }

        curY++;
    }
}

void Polygon::drawLine( int y, int startX, int endX, QImage * backBuffer, const QColor & color ){
    int red = color.red();
    int green = color.green();
    int blue = color.blue();

    int w = backBuffer->width();
    int h = backBuffer->height();

    qDebug() << "w = " << w;
    qDebug() << "h = " << h;

    uchar * bytes = backBuffer->bits();
    int y_bpl = ( y + h/2 ) * backBuffer->bytesPerLine();

    startX += w / 2;
    endX += w / 2;
    for( int x = startX; x <= endX; x++ ){
        qDebug() << "ind = " << y_bpl + x*3 + 2;
        bytes[ y_bpl + x*3     ] = red;
        bytes[ y_bpl + x*3 + 1 ] = green;
        bytes[ y_bpl + x*3 + 2 ] = blue;
    }
}

void Polygon::append( QPoint &newPoint ){
    pointsList.append( newPoint );
    qDebug() << "New point: " << newPoint.x() << " " << newPoint.y(); //TODO
}

void Polygon::removeLast(){
    if( pointsList.size() > 0 ){
        pointsList.removeLast();
    }
}

int Polygon::getNumberPoints() const{
    return pointsList.size();
}

const QPoint & Polygon::getFirstPointCurrentPolygon() const{
    if( pointsList.empty() ){
        throw 77; //TODO: кинуть исключение
    }
    return pointsList.first();
}

void Polygon::closePolygon(){
    // TODO: нужна ли проверка
    // TODO: нужно ли добавлять новую точку
    // если рядом, то замкнуть
    if( (pointsList.size() > 2) ){
        pointsList.append( pointsList.first() );
        qDebug() << "Close points";
        // теперь при отрисовке можно закрашивать внутренность многоугольника
        canFillPolygon = true;
    }
}
