#include "mainwindow.h"
#include "fileWorker.h"

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

    // Создание меню и привязываем действия
    QMenuBar *menuBar = new QMenuBar( this );
    QMenu* menu = new QMenu(tr("File"), menuBar);
    QAction* openAction = menu->addAction( tr("Open") );
    QAction* saveAction = menu->addAction( tr("Save") );

    QObject::connect( openAction, SIGNAL( triggered() ), this, SLOT( openListener() ));
    QObject::connect( saveAction, SIGNAL( triggered() ), this, SLOT( saveListener() ));

    menuBar->addMenu( menu );

    // добавляем меню и заголовок изменяем
    setMenuBar( menuBar );
    setWindowTitle( tr("Polygon") );
}

void MainWindow::openListener(){
    // open dialog
    QFileDialog * fileDialog = new QFileDialog( this );
    fileDialog->setFileMode( QFileDialog::ExistingFile );
    QStringList fileNames;
    if( fileDialog->exec() )
        fileNames = fileDialog->selectedFiles();
    else {
        return;
    }

    // TODO:
    /*try {
        fileWorker::readFileSettings( fileNames.at(0).toStdString(), *(drawPanel->getCircle()) );
    } catch(...) {
    }*/
}

void MainWindow::saveListener(){
    QFileDialog* fileDialog = new QFileDialog( this );
    fileDialog->setFileMode( QFileDialog::Directory );
    fileDialog->setNameFilter( tr( "*.xml" ) );
    QString filename = QFileDialog::getSaveFileName(fileDialog,
                                                    tr( "Save settings" ),
                                                    QDir::currentPath(),
                                                    tr( "Documents (*.xml)" ) );

    // TODO:
    //fileWorker::writeFileSettings( filename.toStdString(), *(drawPanel->getCircle()) );
}
