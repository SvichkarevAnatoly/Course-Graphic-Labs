#include "drawpanel.h"

#include "mqpainter.h"

#include <QMainWindow>

const QColor DrawPanel::DEFAULT_BACKGROUND_COLOR( Qt::white );
const QColor DrawPanel::DEFAULT_WARNING_COLOR( 255, 10, 73 );
const QColor DrawPanel::DEFAULT_AUTO_CLOSE_COLOR( Qt::green );
const QColor DrawPanel::DEFAULT_MAIN_COLOR( Qt::black );

DrawPanel::DrawPanel( QWidget *parent ) :
    QWidget( parent ), flagMagnet( false ), mouseCurPoint( 0, 0 )
{
    // минимальные размеры устанавливаем
    setMinimumSize( DEFAULT_WIDTH, DEFAULT_HEIGHT );
    setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );

    imgBuffer = new QImage( DEFAULT_WIDTH, DEFAULT_HEIGHT, QImage::Format_RGB888 );

    // для отслеживания положения мыши
    setMouseTracking( true );
    installEventFilter( this );
}

DrawPanel::~DrawPanel(){
    delete imgBuffer;
}

// вызывается в repaint()
//отвечает так же за перерисовку при изменении окна
void DrawPanel::paintEvent( QPaintEvent * ){
    // если изменились размеры - пересоздать буфер
    if( (imgBuffer->height() != height()) ||
        (imgBuffer->width()  != width()) ){

        delete imgBuffer;
        imgBuffer = new QImage( width(), height(), QImage::Format_RGB888 );
        imgBuffer->fill( DEFAULT_BACKGROUND_COLOR );
    }

    painter.refreshImageBuffer( imgBuffer );

    // TODO: здесь отрисовка
    QPoint p1(0, 0);
    QPoint p2(0, 100);
    QPoint p3(200, 200);
    QPoint p4(200, 0);

    painter.setColor( DEFAULT_MAIN_COLOR );
    painter.drawLine( p1, p2 );
    painter.drawLine( p2, p3 );
    painter.drawLine( p3, p4 );

    painter.setColor( DEFAULT_WARNING_COLOR );
    painter.drawBezier( p1, p2, p3, p4 );

    painter.drawImage( this );

    imgBuffer->fill( DEFAULT_BACKGROUND_COLOR );
}

// обработка нажатия на панеле
//всё действо через этот метод
void DrawPanel::mousePressEvent(QMouseEvent * event){
    /*if( event->button() == Qt::LeftButton ){
        // преобразуем координаты в систему центра экрана
        int xCoord = event->pos().x() - width() / 2;
        int yCoord = event->pos().y() - height() / 2;
        QPoint curPoint( xCoord, yCoord );

        // проверяем нет ли самопересечения
        if( ! polygons.isSelfIntersection( curPoint ) ){
            // добавляем новую точку
            // если работает магнит, то точку добавить в начальную
            if( flagMagnet ){
                curPoint = polygons.getFirstPointCurrentPolygon();
                flagMagnet = false;
            }

            polygons.addPoint( curPoint );
        }
        // иначе просто игнорим нажатие

        update();
        event->accept();
    }else if( event->button() == Qt::RightButton ){
        // удаляем последнюю точку
        polygons.removeLastPoint();

        update();
        event->accept();
    }*/
    update();
    event->accept();
}

// для протягивания прямой за мышкой
bool DrawPanel::eventFilter(QObject *, QEvent * event){
    /*if( event->type() == QEvent::MouseMove ){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>( event );

        int xCoord = mouseEvent->pos().x() - width() / 2;
        int yCoord = mouseEvent->pos().y() - height() / 2;
        mouseCurPoint.setX( xCoord );
        mouseCurPoint.setY( yCoord );

        // проверяем, если ещё многоугольник не замкнут, то тянем прямую к мышке
        //и рисуем кружок у первой точки многоугольника
        if( ! polygons.isEmptyCurrentPolygon() ){ // пустой полигон считаем замкнутым
            // если число рёбер в полигоне больше 2, то можно попробовать замкнуть
            if( polygons.getNumberEdgeCurrentPolygon() > 2 ){
                // если точка близка к начальной, то примагнитить её
                if( polygons.isNearClose( mouseCurPoint, CLOSE_DISTANCE ) ){
                    QPoint checkPoint( polygons.getFirstPointCurrentPolygon() );
                    if( ! polygons.isSelfIntersection( checkPoint ) ){
                        mouseCurPoint = checkPoint;
                        colorCurEdge = DEFAULT_AUTO_CLOSE_COLOR;
                        flagMagnet = true;

                        // нарисовать отрезок до мышки
                        update();
                        return false;
                    }
                } else{
                    flagMagnet = false;
                }
            }

        }

        if( polygons.isSelfIntersection( mouseCurPoint ) ){
            colorCurEdge = DEFAULT_WARNING_COLOR;
        } else{
            colorCurEdge = DEFAULT_MAIN_COLOR;
        }

        // нарисовать отрезок до мышки
        update();
    }*/

    return false;
}
