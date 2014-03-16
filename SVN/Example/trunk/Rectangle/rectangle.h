#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>

class Rectangle : public QObject
{
    Q_OBJECT
public:
    explicit Rectangle(QObject *parent = 0);

signals:

public slots:

public:
    void Draw(QImage* pBackBuffer);

};

#endif // RECTANGLE_H
