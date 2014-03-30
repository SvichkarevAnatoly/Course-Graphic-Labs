#include "drawpanel.h"

#include "mqpainter.h"

#include <QDebug>  //TODO: убрать

#include <QMainWindow>

const QColor DrawPanel::DEFAULT_CONTOUR_COLOR( 100, 200, 120 );
const QColor DrawPanel::DEFAULT_INNER_COLOR( 100, 200, 120 ); //TODO: поменять

DrawPanel::DrawPanel( QWidget *parent ) :
    QWidget( parent ), flagMagnet( false )
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
        //qDebug() << "MouseMove";
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>( event );

        // проверяем, если ещё многоугольник не замкнут, то тянем прямую к мышке
        //и рисуем кружок у первой точки многоугольника
        if( ! polygons.isClose() ){ // пустой полигон считаем замкнутым
            int xCoord = mouseEvent->pos().x() - width() / 2;
            int yCoord = mouseEvent->pos().y() - height() / 2;
            QPoint curPoint( xCoord, yCoord );

            // если точка близка к начальной, то примагнитить её
            if( polygons.isNearClose( curPoint ) ){
                curPoint = polygons.getFirstPointCurrentPolygon();
                flagMagnet = true;
            } else{
                // иначе нарисовать кружок рядом с начальной
                painter.drawCircle( polygons.getFirstPointCurrentPolygon(), 20 );
            }

            // TODO: константа
            // нарисовать отрезок до мышки
            painter.drawLine( polygons.getLastPoint(), curPoint );
            update(); //TODO: нужно ли
        }
    }

    return false;
}
