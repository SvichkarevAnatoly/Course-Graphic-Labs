#include "drawpanel.h"

#include "mqpainter.h"

#include <QDebug>  //TODO: убрать

#include <QMainWindow>

const QColor DrawPanel::DEFAULT_CONTOUR_COLOR( 100, 200, 120 );
const QColor DrawPanel::DEFAULT_INNER_COLOR( 100, 200, 120 ); //TODO: поменять

DrawPanel::DrawPanel( QWidget *parent ) :
    QWidget( parent ), flagMagnet( false ), mouseCurPoint( 0, 0 ) // TODO: не будет ли лагов с мышкой
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
        imgBuffer->fill( Qt::white );
        qDebug() << "recreate bg"; //TODO: убрать
    }

    // TODO: цвет
    polygons.draw( painter );

    if( ! polygons.isEmptyCurrentPolygon() ){
        if( ! flagMagnet ){
            // TODO: константа
            // нарисовать кружок рядом с начальной точкой
            painter.drawCircle( polygons.getFirstPointCurrentPolygon(), 20 );
        }
        painter.drawLine( polygons.getLastPoint(), mouseCurPoint );
    }

    painter.refreshImageBuffer( imgBuffer );
    painter.drawImage( this );

    imgBuffer->fill( Qt::white );
}

// обработка нажатия на панеле
//всё действо через этот метод
void DrawPanel::mousePressEvent(QMouseEvent * event){
    if( event->button() == Qt::LeftButton ){
        qDebug() << "mousePressEvent::LeftButton";
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
        qDebug() << "mousePressEvent::RightButton";
        // удаляем последнюю точку
        polygons.removeLastPoint();

        update();
        event->accept();
    }
}

//TODO: после щелчка тоже бы надо перерисовать
// для протягивания прямой за мышкой
bool DrawPanel::eventFilter(QObject *, QEvent * event){
    if( event->type() == QEvent::MouseMove ){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>( event );

        int xCoord = mouseEvent->pos().x() - width() / 2;
        int yCoord = mouseEvent->pos().y() - height() / 2;
        mouseCurPoint.setX( xCoord );
        mouseCurPoint.setY( yCoord );

        // проверяем, если ещё многоугольник не замкнут, то тянем прямую к мышке
        //и рисуем кружок у первой точки многоугольника
        if( ! polygons.isEmptyCurrentPolygon() ){ // пустой полигон считаем замкнутым
            // если точка близка к начальной, то примагнитить её
            if( polygons.isNearClose( mouseCurPoint ) ){
                mouseCurPoint = polygons.getFirstPointCurrentPolygon();
                flagMagnet = true;
            } else{
                flagMagnet = false;
            }
        }

        // нарисовать отрезок до мышки
        update();
    }

    return false;
}
