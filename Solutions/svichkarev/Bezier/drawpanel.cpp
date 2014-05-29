#include "drawpanel.h"

#include "mqpainter.h"

#include <QMainWindow>
#include <math.h>

const QColor DrawPanel::DEFAULT_BACKGROUND_COLOR( Qt::black );
const QColor DrawPanel::DEFAULT_WARNING_COLOR( Qt::red );
const QColor DrawPanel::DEFAULT_MAIN_COLOR( Qt::gray );

DrawPanel::DrawPanel( QWidget *parent ) :
    QWidget( parent ), flagMagnet( false ), mouseCurPoint( 0, 0 )
{
    // минимальные размеры устанавливаем
    setMinimumSize( DEFAULT_WIDTH, DEFAULT_HEIGHT );
    setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );

    imgBuffer = new QImage( DEFAULT_WIDTH, DEFAULT_HEIGHT, QImage::Format_RGB888 );

    // инициализация опорных точек
    QPoint p1(0, 0);
    QPoint p2(0, 100);
    QPoint p3(200, 200);
    QPoint p4(200, 0);

    anchors[ 0 ] = p1;
    anchors[ 1 ] = p2;
    anchors[ 2 ] = p3;
    anchors[ 3 ] = p4;

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

    painter.setColor( DEFAULT_MAIN_COLOR );
    painter.drawLine( anchors[0], anchors[1] );
    painter.drawLine( anchors[1], anchors[2] );
    painter.drawLine( anchors[2], anchors[3] );

    painter.setColor( DEFAULT_WARNING_COLOR );
    painter.drawBezier( anchors[0], anchors[1], anchors[2], anchors[3] );

    painter.drawImage( this );

    imgBuffer->fill( DEFAULT_BACKGROUND_COLOR );
}

// обработка нажатия на панеле
//всё действо через этот метод
// отмагничиваем ближайшую точку первым нажатием, второе нажатие - замораживаем
void DrawPanel::mousePressEvent(QMouseEvent * event){
    if( event->button() == Qt::LeftButton ){
        if( ! flagMagnet ){
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>( event );

            // преобразуем координаты в систему центра экрана
            int xCoord = mouseEvent->pos().x() - width() / 2;
            int yCoord = mouseEvent->pos().y() - height() / 2;
            mouseCurPoint.setX( xCoord );
            mouseCurPoint.setY( yCoord );

            // определяем ближайшую и размагничиваем
            findNearest();
            flagMagnet = true;

            anchors[ indexUnmagnedPoint ] = mouseCurPoint;

            // вызвать отрисовку
            update();
        } else{
            // просто замагничиваем
            flagMagnet = false;
        }
    }

    update();
    event->accept();
}

// для протягивания прямой за мышкой
bool DrawPanel::eventFilter(QObject *, QEvent * event){
    if( event->type() == QEvent::MouseMove ){
        if( flagMagnet ){
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>( event );

            // преобразуем координаты в систему центра экрана
            int xCoord = mouseEvent->pos().x() - width() / 2;
            int yCoord = mouseEvent->pos().y() - height() / 2;
            mouseCurPoint.setX( xCoord );
            mouseCurPoint.setY( yCoord );

            anchors[ indexUnmagnedPoint ] = mouseCurPoint;

            // вызвать отрисовку
            update();
        }


    }

    return false;
}

void DrawPanel::findNearest(){
    double minLength = 1.79769e+308;
    double tmpLength = 0;

    for( int i = 0; i < 4; i++ ){
        tmpLength = sqrt( pow(mouseCurPoint.x() - anchors[i].x(), 2) +
                          pow(mouseCurPoint.y() - anchors[i].y(), 2) );
        if( tmpLength < minLength ){
            minLength = tmpLength;
            indexUnmagnedPoint = i;
        }
    }
}
