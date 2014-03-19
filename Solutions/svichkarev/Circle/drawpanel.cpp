#include "drawpanel.h"
#include <QDebug>

// TODO: почему радиус передаём через DrawPanel?
DrawPanel::DrawPanel( int w, int h, int r, QWidget *parent ) :
    QWidget( parent ), Canvas( w, h )
{
    // TODO: где деструктор?
    pCircle = new Circle( 0, 0, r, this);
    // минимальные размеры устанавливаем
    setMinimumSize( w, h );
    // устанавливаем фактический размер
    Canvas::width = QWidget::width();
    Canvas::height = QWidget::height();

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    // устанавливаем обработчики на изменения
    // TODO: что за методы repaint()?
    QObject::connect(pCircle, SIGNAL(changeX(int)), this, SLOT(repaint()));
    QObject::connect(pCircle, SIGNAL(changeY(int)), this, SLOT(repaint()));
    QObject::connect(pCircle, SIGNAL(changeR(int)), this, SLOT(repaint()));

}

// отрисовка пикселя
void DrawPanel::drawPixel( int x, int y, const QColor& color ){
    // TODO: можно сделать массив статическим, тогда не нужно будет каждый раз вызывать
    //или лучше членов класса
    uchar* bytes = backBuffer.bits();
    bytes[ y * backBuffer.bytesPerLine() + x * 3    ] = color.red();
    bytes[ y * backBuffer.bytesPerLine() + x * 3 + 1] = color.green();
    bytes[ y * backBuffer.bytesPerLine() + x * 3 + 2] = color.blue();
}

void DrawPanel::paintEvent(QPaintEvent * ){
    QPainter painter(this);
    backBuffer = QImage(QWidget::width(), QWidget::height(), QImage::Format_RGB888);

    uchar* pubBuffer = backBuffer.bits();
    if (!pubBuffer)
    {
        return;
    }
    memset(pubBuffer, 0, backBuffer.byteCount());

    QColor color( 100, 200, 120 );

    backBuffer.fill(Qt::white);
    if (pCircle)
    {
        pCircle->draw(this, color) ;
    }
    //
    painter.drawImage(0,0, backBuffer);

}

// TODO: зачем нужен?
Circle* DrawPanel::getCircle() const {
    return this->pCircle;
}

// перерисовка при изменении размера окна
void DrawPanel::resizeEvent (QResizeEvent* event ){
    QWidget::resizeEvent( event );
    this->update();
}

// TODO: можно сделать inline и вообще поместить в заголовочный файл
int DrawPanel::getWidth() const {
    return QWidget::width();
}

int DrawPanel::getHeight() const {
    return QWidget::height();
}
