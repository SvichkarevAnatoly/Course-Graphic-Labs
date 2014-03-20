#include "mainwindow.h"
#include "sizecontroller.h"

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

    drawPanel = new DrawPanel( DrawPanel::DEFAULT_WIDTH, DrawPanel::DEFAULT_HEIGHT, drawPanelBox );

    panelLayout->addWidget( drawPanel );

    // создание группы для контролов
    QGroupBox* controllers = new QGroupBox( tr("Controllers") );
    QVBoxLayout* cLayout = new QVBoxLayout( controllers );

    SizeController* xC = new SizeController( this, "Position X", -SizeController::DEFAULT_MAX_VALUE, SizeController::DEFAULT_MAX_VALUE, Circle::DEFAULT_CENTER_X);
    SizeController* yC = new SizeController( this, "Position Y", -SizeController::DEFAULT_MAX_VALUE, SizeController::DEFAULT_MAX_VALUE, Circle::DEFAULT_CENTER_Y);
    SizeController* rC = new SizeController( this, "Radius", 0, SizeController::DEFAULT_MAX_VALUE, Circle::DEFAULT_RADIUS);

    cLayout->addWidget( xC );
    cLayout->addWidget( yC );
    cLayout->addWidget( rC );
    // фиксируем растяжение по горизонтали контролов
    controllers->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Expanding );

    // создаём виджет контейнер, который вложим в наш главный виджет QMainWindow
    QWidget * container = new QWidget;
    // располагаем вертикально область для рисования и контролов
    //и помещаем в контейнер
    QHBoxLayout * mainLayout = new QHBoxLayout( container );
    mainLayout->addWidget( drawPanelBox );
    mainLayout->addWidget( controllers );

    // устанавливаем начинку главному виджету
    setCentralWidget(container);

    // изменили значения контролов, нужно вызвать отрисовку и установить новые значения параметров
    QObject::connect( xC, SIGNAL( valueChanged(int) ), drawPanel->getCircle(), SLOT( setX(int) ));
    QObject::connect( yC, SIGNAL( valueChanged(int) ), drawPanel->getCircle(), SLOT( setY(int) ));
    QObject::connect( rC, SIGNAL( valueChanged(int) ), drawPanel->getCircle(), SLOT( setR(int) ));

    /*По идее архитектура должна быть построена так:
        Вызывается сигнал, мы у области рисования вызываем слот перерисовки.
        В области рисования у нас есть разные объекты для отрисовки.
        В перерисовки мы независимо у каждого вызываем функцию перерисовки.
        Картинка отрисовывается как сумма отображений каждого объекта
        Остальные контролы сразу меняют своё состояние, не дожидаясь отрисовки,
        потому что отрисовка может занимать значительное время, а параметры должны быть
        действительными на данный момент
    */

    // Создание меню и привязываем действия
    QMenuBar *menuBar = new QMenuBar( this );
    QMenu* menu = new QMenu(tr("File"), menuBar);
    QAction* openAction = menu->addAction( tr("Open") );
    QAction* saveAction = menu->addAction( tr("Save") );

    QObject::connect( openAction, SIGNAL( triggered() ), this, SLOT( openClicked() ));
    QObject::connect( saveAction, SIGNAL( triggered() ), this, SLOT( saveClicked() ));

    menuBar->addMenu( menu );

    // добавляем меню и заголовок изменяем
    this->setMenuBar( menuBar );
    this->setWindowTitle( tr("Circle") );
}


// TODO: ещё непонятно как это работает
void MainWindow::openClicked(){}

// TODO: ещё непонятно как это работает
void MainWindow::saveClicked(){}
