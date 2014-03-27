#include "drawpanel.h"

#include <QDebug>  //TODO: убрать

const QColor DrawPanel::DEFAULT_COLOR( 100, 200, 120 );

DrawPanel::DrawPanel( int minW, int minH, QWidget *parent ) :
    QWidget( parent ), oldWidth( width() ), oldHeight( height() ),
    polygon( *(new Polygon()) ) // TODO: точно ли так
{
    // минимальные размеры устанавливаем
    setMinimumSize( minW, minH );
    setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );

    backBuffer = new QImage( oldWidth, oldHeight, QImage::Format_RGB888 );

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

    polygon.draw( backBuffer, DEFAULT_COLOR, painter );
    // TODO: поменять
    //painter.drawImage( 0, 0, *backBuffer );
}

// обработка нажатия на панеле
//всё действо через этот метод
void DrawPanel::mousePressEvent(QMouseEvent * event){
    static QPoint * curPoint;

    if( event->button() == Qt::LeftButton ){
        // преобразуем координаты в системе центра экрана
        curPoint = new QPoint( event->pos().x() - oldWidth/2, event->pos().y() - oldHeight/2 );
        // добавляем новую точку
        polygon.append( *curPoint );
        update();
        event->accept();
    }else if( event->button() == Qt::RightButton ){
        // удаляем последнюю точку
        polygon.removeLast();
        update();
        event->accept();
    }
}
