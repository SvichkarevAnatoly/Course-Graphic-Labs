#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    drawWidget = new DrawWidget();
    setCentralWidget(drawWidget);
}

MainWindow::~MainWindow()
{    
}
