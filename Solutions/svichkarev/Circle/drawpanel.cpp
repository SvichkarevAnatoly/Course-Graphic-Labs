#include "drawpanel.h"

DrawPanel::DrawPanel( int minW, int minH, QWidget *parent ) :
    QWidget( parent )
{
    // TODO: где деструктор?
    pCircle = new Circle( Circle::DEFAULT_CENTER_X, Circle::DEFAULT_CENTER_Y, Circle::DEFAULT_RADIUS );

    // минимальные размеры устанавливаем
    setMinimumSize( minW, minH );
    setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );

    // устанавливаем обработчики на изменения, перерисовку qt вызовет
    QObject::connect( pCircle, SIGNAL( changeX(int) ), this, SLOT( repaint() ) );
    QObject::connect( pCircle, SIGNAL( changeY(int) ), this, SLOT( repaint() ) );
    QObject::connect( pCircle, SIGNAL( changeR(int) ), this, SLOT( repaint() ) );
}

// отрисовка пикселя
void DrawPanel::drawPixel( int x, int y, const QColor & color ){
    // TODO: можно сделать массив статическим, тогда не нужно будет каждый раз вызывать
    //или лучше членов класса
    uchar* bytes = backBuffer.bits();
    bytes[ y * backBuffer.bytesPerLine() + x * 3     ] = color.red();
    bytes[ y * backBuffer.bytesPerLine() + x * 3 + 1 ] = color.green();
    bytes[ y * backBuffer.bytesPerLine() + x * 3 + 2 ] = color.blue();
}

void DrawPanel::paintEvent( QPaintEvent * ){
    QPainter painter( this ); // TODO: ?
    backBuffer = QImage( width(), height(), QImage::Format_RGB888 );

    uchar * pubBuffer = backBuffer.bits();
    if( !pubBuffer ){ // TODO: ?
        return;
    }
    // TODO: ?
    memset( pubBuffer, 0, backBuffer.byteCount() );

    QColor color( 100, 200, 120 ); // TODO: ?

    backBuffer.fill( Qt::white ); // TODO: ?
    if( pCircle ){
        pCircle->draw( this, color );
    }

    // TODO: ?
    painter.drawImage( 0, 0, backBuffer );
}

// для доставания из панели
Circle* DrawPanel::getCircle() const {
    return pCircle;
}

// перерисовка при изменении размера окна
// TODO: нужна ли вообще?
void DrawPanel::resizeEvent (QResizeEvent* event ){
    QWidget::resizeEvent( event );
    this->update();
}
