#include "drawpanel.h"
#include <QDebug>
DrawPanel::DrawPanel(int w, int h, int r, QWidget *parent) :
    QWidget(parent), Canvas(w, h)
{
    pCircle = new Circle(0,0,r, this);
    setMinimumSize(w,h);
    Canvas::width = QWidget::width();
    Canvas::height = QWidget::height();

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    QObject::connect(pCircle, SIGNAL(changeX(int)), this, SLOT(repaint()));
    QObject::connect(pCircle, SIGNAL(changeY(int)), this, SLOT(repaint()));
    QObject::connect(pCircle, SIGNAL(changeR(int)), this, SLOT(repaint()));

}

void DrawPanel::drawPixel(int x, int y, const RGBColor& color)
{
    uchar* bytes = backBuffer.bits();
    bytes[ y * backBuffer.bytesPerLine() + x * 3    ] = color.R;
    bytes[ y * backBuffer.bytesPerLine() + x * 3 + 1] = color.G;
    bytes[ y * backBuffer.bytesPerLine() + x * 3 + 2] = color.B;

}

void DrawPanel::paintEvent(QPaintEvent * )
{
    QPainter painter(this);
    backBuffer = QImage(QWidget::width(), QWidget::height(), QImage::Format_RGB888);

    uchar* pubBuffer = backBuffer.bits();
    if (!pubBuffer)
    {
        return;
    }
    memset(pubBuffer, 0, backBuffer.byteCount());
    //
    RGBColor color;
    color.R = 100;
    color.G = 200;
    color.B = 120;

    backBuffer.fill(Qt::white);
    if (pCircle)
    {
        pCircle->draw(this, color) ;
    }
    //
    painter.drawImage(0,0, backBuffer);

}

Circle* DrawPanel::getCircle() const {
    return this->pCircle;
}
void DrawPanel::resizeEvent (QResizeEvent* event )
{

    QWidget::resizeEvent(event);
    this->update();
}

int DrawPanel::getWidth() const {
    return QWidget::width();
}

int DrawPanel::getHeight() const {
    return QWidget::height();
}
