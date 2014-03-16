#include "drawwidget.h"
#include <QPainter>
#include <QImage>

DrawWidget::DrawWidget(QWidget *parent) :
    QWidget(parent)
{
    m_pRectangle = new Rectangle();
}

DrawWidget::~DrawWidget()
{

}

void DrawWidget::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    QImage backBuffer(width(), height(), QImage::Format_RGB888);

    uchar* pubBuffer = backBuffer.bits();
    if (!pubBuffer)
    {
        return;
    }
    memset(pubBuffer, 0, backBuffer.byteCount());
    //
    if (m_pRectangle)
    {
        m_pRectangle->Draw(&backBuffer);
    }
    //
    painter.drawImage(0,0, backBuffer);
}
