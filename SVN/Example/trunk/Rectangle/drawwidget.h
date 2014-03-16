#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include "rectangle.h"

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = 0);
    ~DrawWidget();

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);

private:
    Rectangle*  m_pRectangle;

};

#endif // DRAWWIDGET_H
