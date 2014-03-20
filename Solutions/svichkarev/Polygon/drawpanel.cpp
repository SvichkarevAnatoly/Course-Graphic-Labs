#include "drawpanel.h"

#include <QDebug>  //TODO: убрать

const QColor DrawPanel::DEFAULT_COLOR( 100, 200, 120 );

DrawPanel::DrawPanel( int minW, int minH, QWidget *parent ) :
    QWidget( parent ), oldWidth( width() ), oldHeight( height() )
{
    pCircle = new Circle( Circle::DEFAULT_CENTER_X, Circle::DEFAULT_CENTER_Y, Circle::DEFAULT_RADIUS );

    // минимальные размеры устанавливаем
    setMinimumSize( minW, minH );
    setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
    backBuffer = new QImage( oldWidth, oldHeight, QImage::Format_RGB888 );

    // устанавливаем обработчики на изменения, перерисовку qt вызовет
    QObject::connect( pCircle, SIGNAL( changeX(int) ), this, SLOT( repaint() ) );
    QObject::connect( pCircle, SIGNAL( changeY(int) ), this, SLOT( repaint() ) );
    QObject::connect( pCircle, SIGNAL( changeR(int) ), this, SLOT( repaint() ) );
}

DrawPanel::~DrawPanel(){
    delete pCircle;
    delete backBuffer;
}

// вызывается в repaint()
void DrawPanel::paintEvent( QPaintEvent * ){
    QPainter painter( this );
    /*// если изменились размеры - пересоздать
    if( !((oldHeight == height()) &&
            (oldWidth == width())) ){

        delete backBuffer;
        oldHeight = height();
        oldWidth = width();
        backBuffer = new QImage( oldWidth, oldHeight, QImage::Format_RGB888 );
        qDebug()   << "reee"; //TODO: убрать
    }

    if( pCircle ){
        pCircle->draw( backBuffer, DEFAULT_COLOR );
    }

    painter.drawImage( 0, 0, *backBuffer );
    */
    painter.setPen(Qt::green);
    if( pointsArr.size() >= 2 ){
        for(std::vector<QPoint>::size_type i = 0; i != pointsArr.size()-1; i++) {
            painter.drawLine( pointsArr[i], pointsArr[i+1] );
        }
    }
}

// обработка нажатия на панеле
//вся суть лабы в этом методе
void DrawPanel::mousePressEvent(QMouseEvent * event){
    if( event->button() == Qt::LeftButton ){
        // добавляем новую точку
        //pCircle->setR(100);
        pointsArr.push_back( event->pos() );
        event->accept();
        update();
    }else if( event->button() == Qt::RightButton ){
        // удаляем последнюю точку

    }


}

// для доставания из панели
Circle* DrawPanel::getCircle() const {
    return pCircle;
}
