#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>

#include "drawpanel.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
    DrawPanel* drawPanel;
public:
    explicit MainWindow(QWidget *parent = 0);

signals:
public slots:
    void openClicked(bool checked );
    void saveClicked(bool checked );
};

#endif // MAINWINDOW_H
