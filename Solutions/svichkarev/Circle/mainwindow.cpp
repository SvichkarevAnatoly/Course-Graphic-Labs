#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawPanel = ui->drawPanel;

    // берём размеры виджета
    sizeXDrawPanel = drawPanel->size().width();
    sizeYDrawPanel = drawPanel->size().height();

    // создание круга
    img = new QImage( sizeXDrawPanel, sizeYDrawPanel, QImage::Format_RGB888 );

    dx = (float)sizeXDrawPanel/100;
    dy = (float)sizeYDrawPanel/100;
    dR = (float)sizeYDrawPanel/250;

    // квадрат радиуса круга
    // чтобы на 100 делений хватило
    R0 = (float)sizeYDrawPanel / 5;
    // центр круга
    x0 = (float)sizeXDrawPanel / 2;
    y0 = (float)sizeYDrawPanel / 2;

    // текущие значения - значения по умолчанию
    curR = R0;
    curX = x0;
    curY = y0;

    sliderXPos = ui->sliderXPos;
    sliderYPos = ui->sliderYPos;
    sliderR = ui->sliderR;

    spinXPos = ui->spinXPos;
    spinYPos = ui->spinYPos;
    spinR = ui->spinR;

    // устанавливаем обработчики
    QObject::connect( sliderXPos, SIGNAL(valueChanged(int)), this, SLOT(changeSliderXPos(int)) );
    QObject::connect( sliderYPos, SIGNAL(valueChanged(int)), this, SLOT(changeSliderYPos(int)) );
    QObject::connect( sliderR,    SIGNAL(valueChanged(int)), this, SLOT(changeSliderR(int)) );

    QObject::connect( spinXPos, SIGNAL(valueChanged(double)), this, SLOT(changeSpinXPos(double)) );
    QObject::connect( spinYPos, SIGNAL(valueChanged(double)), this, SLOT(changeSpinYPos(double)) );
    QObject::connect( spinR,    SIGNAL(valueChanged(double)), this, SLOT(changeSpinR(double)) );

    //? устанавливаем главный менеджер компоновки
    //setLayout(ui->mainformLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeSliderXPos( int val ){
    int shift = -(50 - val);
    spinXPos->setValue( val );
    curX = x0 + dx*shift;
    update();
}

void MainWindow::changeSliderYPos( int val ){
    int shift = 50 - val;
    spinYPos->setValue( val );
    curY = y0 + dy*shift;
    update();
}

void MainWindow::changeSliderR( int val ){
    int shift = -(50 - val);
    spinR->setValue( val );
    curR = R0 + dR*shift;
    update();
}

void MainWindow::changeSpinXPos( double val ){
    double shift = -(50.0 - val);
    sliderXPos->setValue((int)val);
    curX = x0 + dx*shift;
    update();
}

void MainWindow::changeSpinYPos( double val ){
    double shift = 50.0 - val;
    sliderYPos->setValue((int)val);
    curY = y0 + dy*shift;
    update();
}

void MainWindow::changeSpinR( double val ){
    double shift = -(50.0 - val);
    sliderR->setValue((int)val);
    curR = R0 + dR*shift;
    update();
}

// после update сюда заходим
void MainWindow::paintEvent(QPaintEvent * /* event */)
{
    static const uchar colors[2][3] = { { 0  , 168, 107}, // цвет круга
                                        { 255, 255, 255} }; // цвет фона

    // считали массив, чтоб каждый раз не вызывать функцию
    static uchar *field = img->bits();
    // число байтов в строке для отступа
    static int bPL = img->bytesPerLine();

    // квадрат радиуса
    //? можно ещё пооптимизировать!
    float rr = curR * curR;
    for( int y = 0; y < sizeYDrawPanel; y++ ){
        for( int x = 0; x < sizeXDrawPanel; x++ ){
            if( ((float)x-curX)*((float)x-curX)+((float)y-curY)*((float)y-curY) <= rr ){
                memcpy( field + y*bPL + x*3, colors[0], 3 );
            } else{
                memcpy( field + y*bPL + x*3, colors[1], 3 );
            }
        }
     }

    QPainter painter(this);

    painter.drawImage( 0, 0, *img );
}
