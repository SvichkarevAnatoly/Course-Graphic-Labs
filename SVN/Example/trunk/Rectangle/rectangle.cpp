#include "rectangle.h"
#include <QImage>

Rectangle::Rectangle(QObject *parent) :
    QObject(parent)
{
}

void Rectangle::Draw(QImage* pBackBuffer)
{
    if (!pBackBuffer)
    {
        return;
    }
    uchar* pubBuffer = pBackBuffer->bits();
    if (pBackBuffer->width() < 100 ||
        pBackBuffer->height() < 100)
    {
        return;
    }
    for (int line = 0; line < 100; line++)
    {
        memset(
            pubBuffer + (line*pBackBuffer->bytesPerLine()),
            255,
            sizeof(uchar) * 3 * 100);
    }
}
