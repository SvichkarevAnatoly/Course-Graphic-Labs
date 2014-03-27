#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawpanel.h"

#include <QWidget>
#include <QMainWindow>

class MainWindow : public QMainWindow{
    Q_OBJECT
    DrawPanel * drawPanel;
public:
    // если не указываем, то нет родительского виджета
    MainWindow( QWidget *parent = 0 );
public slots:
    void openListener();
    void saveListener();
};

#endif // MAINWINDOW_H
