#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QSpinBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    // наше поле
    QImage *img;

    // начальные значения центра и радиуса
    float x0, y0, R0;
    float curX, curY, curR;

    // размеры виджета
    int sizeXDrawPanel;
    int sizeYDrawPanel;

    // коэффициент приращения
    float dx;
    float dy;
    float dR;

    //QImage * img;

    // виджет под рисование
    QWidget *drawPanel;

    // спинеры
    QDoubleSpinBox *spinXPos;
    QDoubleSpinBox *spinYPos;
    QDoubleSpinBox *spinR;

    // слайдеры
    QSlider *sliderXPos;
    QSlider *sliderYPos;
    QSlider *sliderR;
protected:
    // метод перерисовки
    void paintEvent(QPaintEvent *event);

private slots:
    void changeSliderXPos(int val);
    void changeSliderYPos(int val);
    void changeSliderR(int val);

    void changeSpinXPos(double val);
    void changeSpinYPos(double val);
    void changeSpinR(double val);
};

#endif // MAINWINDOW_H
