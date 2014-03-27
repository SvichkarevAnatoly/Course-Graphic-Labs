#include "drawpanel.h"

#include <QDebug>  //TODO: убрать

#include <QMainWindow>
#include <qmath.h>

const QColor DrawPanel::DEFAULT_CONTOUR_COLOR( 100, 200, 120 );
const QColor DrawPanel::DEFAULT_INNER_COLOR( 100, 200, 120 ); //TODO: поменять

DrawPanel::DrawPanel( int minW, int minH, QWidget *parent ) :
    QWidget( parent ), oldWidth( width() ), oldHeight( height() ),
    polygon( *(new Polygon()) ), flagNearClose( false ) // TODO: точно ли так
{
    // минимальные размеры устанавливаем
    setMinimumSize( minW, minH );
    setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );

    backBuffer = new QImage( oldWidth, oldHeight, QImage::Format_RGB888 );

    // для отслеживания положения мыши
    setMouseTracking( true );
    installEventFilter( this );

    // TODO:
    /*// устанавливаем обработчики на изменения, перерисовку qt вызовет
    QObject::connect( pCircle, SIGNAL( changeX(int) ), this, SLOT( repaint() ) );
    QObject::connect( pCircle, SIGNAL( changeY(int) ), this, SLOT( repaint() ) );
    QObject::connect( pCircle, SIGNAL( changeR(int) ), this, SLOT( repaint() ) );
    */
}

DrawPanel::~DrawPanel(){
    delete backBuffer;
    delete &polygon;
}

// вызывается в repaint()
//отвечает так же за перерисовку при изменении окна
void DrawPanel::paintEvent( QPaintEvent * ){
    QPainter painter( this );
    // если изменились размеры - пересоздать
    if( !((oldHeight == height()) &&
            (oldWidth == width())) ){

        delete backBuffer;
        oldHeight = height();
        oldWidth = width();
        backBuffer = new QImage( oldWidth, oldHeight, QImage::Format_RGB888 );
        qDebug()   << "recreate bg"; //TODO: убрать
    }

    // TODO: цвет
    polygon.draw( backBuffer, DEFAULT_CONTOUR_COLOR, painter );
    // TODO: поменять
    //painter.drawImage( 0, 0, *backBuffer );
}

// обработка нажатия на панеле
//всё действо через этот метод
void DrawPanel::mousePressEvent(QMouseEvent * event){
    if( event->button() == Qt::LeftButton ){
        // преобразуем координаты в системе центра экрана
        QPoint curPoint( event->pos().x() - oldWidth/2, event->pos().y() - oldHeight/2 );
        // добавляем новую точку
        if( flagNearClose ){
            // если можно замкнуть, то замыкаем
            polygon.closePolygon();
        } else{
            polygon.append( curPoint );
        }
        update();
        event->accept();
    }else if( event->button() == Qt::RightButton ){
        // удаляем последнюю точку
        polygon.removeLast();
        update();
        event->accept();
    }
}

// для определения замыкания
bool DrawPanel::eventFilter(QObject *, QEvent * event){
    if( event->type() == QEvent::MouseMove ){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>( event );

        QPoint curPoint( mouseEvent->pos().x() - oldWidth/2, mouseEvent->pos().y() - oldHeight/2 );
        checkNearClose( curPoint );
    }

    return false;
}

// TODO: усложнится структура
void DrawPanel::checkNearClose( const QPoint & checkPoint ){
    if( polygon.getNumberPoints() > 2 ){
        const QPoint nearVec = polygon.getFirstPointCurrentPolygon() - checkPoint;
        double trueLength = sqrt(pow(nearVec.x(), 2) + pow(nearVec.y(), 2));
        if( trueLength < CLOSE_DISTANCE ){ // внутри окрестности
            flagNearClose = true;
            qDebug() << "Near"; //TODO
        } else{
            flagNearClose = false;
        }
    }
}
