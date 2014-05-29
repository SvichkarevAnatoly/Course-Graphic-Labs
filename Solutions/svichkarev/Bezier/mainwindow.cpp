#include "mainwindow.h"

#include <QGroupBox>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QVBoxLayout>

MainWindow::MainWindow( QWidget * parent ) :
    QMainWindow( parent ) // создали QT-шное окно в конструкторе родителя
{
    // создание группы для отрисовки
    QGroupBox* drawPanelBox = new QGroupBox( tr("Draw Panel") );
    QVBoxLayout* panelLayout = new QVBoxLayout( drawPanelBox );

    drawPanel = new DrawPanel( drawPanelBox );
    panelLayout->addWidget( drawPanel );

    // создаём виджет контейнер, который вложим в наш главный виджет QMainWindow
    QWidget * container = new QWidget;
    // располагаем вертикально область для рисования и контролов
    //и помещаем в контейнер
    QHBoxLayout * mainLayout = new QHBoxLayout( container );
    mainLayout->addWidget( drawPanelBox );

    // устанавливаем начинку главному виджету
    setCentralWidget(container);

    // заголовок изменяем
    setWindowTitle( tr("Bezier") );
}
