#include "drawpanel.h"
#include <QPainter>
#include <QDebug>

DrawPanel::DrawPanel(int w, int h,   QWidget *parent) :
    QWidget(parent),Canvas(w,h),square(w,w/2,h/2), texture(w)
{
    setFixedSize(w, h);

    square.setSize(texture.get_size());
    square.setMax(w,h);

    // установка обработчиков событий на изменения квадрата
    QObject::connect(&square, SIGNAL(scaleXChanged(double)), &texture, SLOT(setScaleX(double)));
    QObject::connect(&square, SIGNAL(scaleYChanged(double)), &texture, SLOT(setScaleY(double)));

    QObject::connect(&square, SIGNAL(angleChanged(double)), this, SLOT(repaint_square()));
    QObject::connect(&square, SIGNAL(scaleXChanged(double)), this, SLOT(repaint_square()));
    QObject::connect(&square, SIGNAL(scaleYChanged(double)), this, SLOT(repaint_square()));

    // первая отрисовка
    square.draw(*this, &texture);
}

// системный обработчик отрисовки графической области
void DrawPanel::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(0,0, image);
}

// функция загрузки текстуры из файла
void DrawPanel::open(const std::string& filename){
    texture.load(filename);
    square.setSize(texture.get_size());
    square.setDefault();

    // отрисовка
    repaint_square();
}

// предобработчик перерисовки
void DrawPanel::repaint_square(){
    // отрисовка квадрата
    square.draw(*this, &texture);
    repaint();
}

