#include "mainwindow.h"
#include "sizecontroller.h"

#include <QGroupBox>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QVBoxLayout>

// TODO:change hard coded constants !
MainWindow::MainWindow( QWidget * parent ) :
    QMainWindow( parent ) // создали QT-шное окно в конструкторе родителя
{
    // создание группы для отрисовки
    QGroupBox* drawPanelBox = new QGroupBox( tr("Draw Panel") );
    QVBoxLayout* panelLayout = new QVBoxLayout( drawPanelBox );

    drawPanel = new DrawPanel( DrawPanel::DEFAULT_WIDTH, DrawPanel::DEFAULT_HEIGHT, drawPanelBox );

    // TODO: надо ресурсы где-то освобождать

    panelLayout->addWidget( drawPanel );

    // создание группы для контролов
    QGroupBox* controllers = new QGroupBox( tr("Controllers") );
    QVBoxLayout* cLayout = new QVBoxLayout( controllers );

    // TODO: нужно оставить для числового значения, но для слайдера поменять
    // TODO: почему константы именно такие
    SizeController* xC = new SizeController( this, "Position X", -10000, 10000, Circle::DEFAULT_CENTER_X);
    SizeController* yC = new SizeController( this, "Position Y", -10000, 10000, Circle::DEFAULT_CENTER_Y);
    SizeController* rC = new SizeController( this, "Radius", 0, 10000, Circle::DEFAULT_RADIUS);

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
    this->setCentralWidget(container);

    // изменили значения контролов, нужно вызвать отрисовку и установить новые значения параметров
    // TODO: вызвать команду перерисовки только у панели, она сама отрисует всех
    QObject::connect( xC, SIGNAL( valueChanged(int) ), drawPanel->getCircle(), SLOT( setX(int) ));
    QObject::connect( yC, SIGNAL( valueChanged(int) ), drawPanel->getCircle(), SLOT( setY(int) ));
    QObject::connect( rC, SIGNAL( valueChanged(int) ), drawPanel->getCircle(), SLOT( setR(int) ));

    //TODO:
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
    // TODO: зачем меню передавать bool?
    // TODO: можно вызывать слоты сразу у полотна, оно само разберётся( вызовет у класса утилиты сохранение )
    QObject::connect( openAction, SIGNAL( triggered() ), this, SLOT( openClicked() ));
    QObject::connect( saveAction, SIGNAL( triggered() ), this, SLOT( saveClicked() ));

    menuBar->addMenu( menu );

    // добавляем меню и заголовок изменяем
    this->setMenuBar( menuBar );
    this->setWindowTitle( tr("Circle") );
}


// TODO: ещё непонятно как это работает
void MainWindow::openClicked(){
    // TODO:
    // open dialog
    QFileDialog* fileDialog = new QFileDialog(this);
    fileDialog->setFileMode( QFileDialog::ExistingFile);
    fileDialog->setNameFilter(tr("*.xml"));
    QStringList fileNames;
    if (fileDialog->exec())
        fileNames = fileDialog->selectedFiles();
    else {
        return;
    }
    try {
        // TODO: здесь надо что-то типо создать объект круга и добавить его в панель, в идеале фабрику даже
        drawPanel->getCircle()->read(fileNames.at(0).toStdString());
    } catch(...) {
        // TODO:
    }
}

// TODO: ещё непонятно как это работает
void MainWindow::saveClicked(){
    // TODO:
    QFileDialog* fileDialog = new QFileDialog(this);
    fileDialog->setFileMode( QFileDialog::Directory);
    fileDialog->setNameFilter(tr("*.xml"));
    QString filename = QFileDialog::getSaveFileName(fileDialog,
                                                    tr("Save settings"),
                                                    QDir::currentPath(),
                                                    tr("Documents (*.xml)"));
    if( !filename.isNull() ){
        this->drawPanel->getCircle()->save(filename.toStdString());
    }else{
        qDebug("fileName is null");
    }

}
