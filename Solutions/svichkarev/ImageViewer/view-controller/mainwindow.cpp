#include "mainwindow.h"
#include "texture/square.h"

#include "sizecontroller.h"
#include <QObject>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QGroupBox>
#include <QButtonGroup>


MainWindow::MainWindow(int w, int h, QWidget *parent)
    : QMainWindow(parent)
{
    // создание панели для рисования и контроллеров
    drawPanel = new DrawPanel( w, h, this );
    SizeController* rotateContr = new SizeController(this, "ANGLE",  0, 360, 0);
    SizeController* scaleXContr= new SizeController(this, "SCALE X", 0.1, 10, 1);
    SizeController* scaleYContr= new SizeController(this, "SCALE Y", 0.1, 10, 1);
    QGroupBox* controllersBox = new QGroupBox(this);
    QGroupBox* drawPanelBox= new QGroupBox(this);

    // установка обработчиков различных событий изменения
    QObject::connect(&drawPanel->getSquare(), SIGNAL(angleChanged(double)), rotateContr, SLOT(setValue(double)));
    QObject::connect(rotateContr, SIGNAL(valueChanged(double)), &drawPanel->getSquare(), SLOT(rotate(double)));
    QObject::connect(&drawPanel->getSquare(), SIGNAL(scaleXChanged(double)), scaleXContr, SLOT(setValue(double)));
    QObject::connect(&drawPanel->getSquare(), SIGNAL(scaleYChanged(double)), scaleYContr, SLOT(setValue(double)));
    QObject::connect(scaleXContr,SIGNAL(valueChanged(double)), &drawPanel->getSquare(), SLOT(scaleX(double)));
    QObject::connect(scaleYContr,SIGNAL(valueChanged(double)), &drawPanel->getSquare(), SLOT(scaleY(double)));

    // сборка в единое целое и установление размеров
    QVBoxLayout* panelLayout = new QVBoxLayout();
    panelLayout->addWidget(drawPanel);
    drawPanelBox->setLayout(panelLayout);
    drawPanelBox->setFixedSize(w, h);
    drawPanelBox->setMinimumSize(w,h);
    panelLayout->setSizeConstraint(QLayout::SetFixedSize);
    drawPanelBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // сборка группы фильтров
    QVBoxLayout* cLayout = new QVBoxLayout();
    QButtonGroup* filterGroup = new QButtonGroup();
    QRadioButton* noFilter = new QRadioButton(tr("No filter"),this);
    QRadioButton* bilinearFilter = new QRadioButton(tr("Bilinear filter"),this);
    QRadioButton* mipMapFilter = new QRadioButton(tr("Mip mapping"), this);
    filterGroup->addButton(noFilter, 0);
    filterGroup->addButton(bilinearFilter, 1);
    filterGroup->addButton(mipMapFilter, 2);
    // обработчики переключателей фильтров
    connect(filterGroup, SIGNAL(buttonClicked(int)), &drawPanel->getTexture(), SLOT(setFilter(int)));
    connect(filterGroup, SIGNAL(buttonClicked(int)), drawPanel, SLOT(repaint_square()));

    // добавление радиоточек на виджеты
    QGroupBox* filterBox = new QGroupBox(tr("Choose fitler type:"),this);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(noFilter);
    vbox->addWidget(bilinearFilter);
    vbox->addWidget(mipMapFilter);
    filterBox->setLayout(vbox);
    noFilter->setChecked(true);

    // присоединение контроллеров к области управления
    cLayout->addWidget(rotateContr);
    cLayout->addWidget(scaleXContr);
    cLayout->addWidget(scaleYContr);
    cLayout->addWidget(filterBox);

    // настройка области управления
    controllersBox->setLayout(cLayout);
    cLayout->setSizeConstraint(QLayout::SetFixedSize);
    controllersBox->setMinimumSize(250, h);
    controllersBox->setFixedSize(250, h);
    controllersBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // глобальная сборка всего окна
    QWidget * center = new QWidget(this);
    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(drawPanelBox);
    hlayout->addWidget(controllersBox);
    hlayout->setSizeConstraint(QLayout::SetFixedSize);
    center->setMinimumSize(w+300, h);
    center->setFixedSize(w+300, h);
    center->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    center->setLayout(hlayout);

    // установка меню и события выбора файла
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu* menu = new QMenu(tr("File"), menuBar);
    QAction* openAction = menu->addAction(tr("Open"));
    QObject::connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openClicked(bool)));

    menuBar->addMenu(menu);
    this->setMenuBar(menuBar);

    setCentralWidget(center);
}

// обработчик события выбора пункта меню Открыть
void MainWindow::openClicked(bool){
    QFileDialog fileDialog(this);
    fileDialog.deleteLater();
    fileDialog.setFileMode( QFileDialog::ExistingFile);
    // отображать файлы только формата png
    fileDialog.setNameFilter(tr("*.png"));

    // запуск диалога выбора файла
    QStringList fileNames;
    if(fileDialog.exec())
        fileNames = fileDialog.selectedFiles();
    else {
        return;
    }

    try {
        drawPanel->open(fileNames.at(0).toStdString());
    } catch(...) {
        // TODO: обработка ошибки
    }

}
