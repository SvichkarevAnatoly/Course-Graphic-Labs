#include <QGroupBox>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QVBoxLayout>
#include "mainwindow.h"
#include "sizecontroller.h"

// TODO:change hard coded constants !
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    int DEFAULT_R = 20;
    QGroupBox* drawPanelBox = new QGroupBox(tr("Draw Panel"));
    QVBoxLayout* panelLayout = new QVBoxLayout(drawPanelBox);
    drawPanel = new DrawPanel(199, 200, DEFAULT_R, drawPanelBox);
    panelLayout->addWidget(drawPanel);
    drawPanelBox->setLayout(panelLayout);

    QGroupBox* controllers = new QGroupBox(tr("Controllers"));
    QVBoxLayout* cLayout = new QVBoxLayout(controllers);

    SizeController* xC = new SizeController(this, "Position X", -10000, 10000, 0);
    SizeController* yC = new SizeController(this, "Position Y", -10000, 10000, 0);
    SizeController* rC = new SizeController(this, "Radius", 0, 10000, DEFAULT_R);

    cLayout->addWidget(xC);
    cLayout->addWidget(yC);
    cLayout->addWidget(rC);
    controllers->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    controllers->setLayout(cLayout);

    QWidget* container = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(container);
    mainLayout->addWidget(drawPanelBox);
    mainLayout->addWidget(controllers);
    container->setLayout(mainLayout);

    this->setCentralWidget(container);

    QObject::connect(xC, SIGNAL(valueChanged(int)), drawPanel->getCircle(), SLOT(setX(int)));
    QObject::connect(yC, SIGNAL(valueChanged(int)), drawPanel->getCircle(), SLOT(setY(int)));
    QObject::connect(rC, SIGNAL(valueChanged(int)), drawPanel->getCircle(), SLOT(setR(int)));

    QObject::connect(drawPanel->getCircle(), SIGNAL(changeX(int)), xC, SLOT(setValue(int)));
    QObject::connect(drawPanel->getCircle(), SIGNAL(changeY(int)), yC, SLOT(setValue(int)));
    QObject::connect(drawPanel->getCircle(), SIGNAL(changeR(int)), rC, SLOT(setValue(int)));

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu* menu = new QMenu(tr("File"), menuBar);
    QAction* openAction = menu->addAction(tr("Open"));
    QAction* saveAction = menu->addAction(tr("Save"));
    QObject::connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openClicked(bool)));
    QObject::connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(saveClicked(bool)));

    menuBar->addMenu(menu);

    this->setMenuBar(menuBar);
    this->setWindowTitle(tr("Circle"));
}

void MainWindow::openClicked(bool  )
{
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
        drawPanel->getCircle()->read(fileNames.at(0).toStdString());
    } catch(...) {
        // TODO:
    }
}
void MainWindow::saveClicked(bool  )
{
    // TODO:
    QFileDialog* fileDialog = new QFileDialog(this);
    fileDialog->setFileMode( QFileDialog::Directory);
    fileDialog->setNameFilter(tr("*.xml"));
    QString filename = QFileDialog::getSaveFileName(fileDialog,
                                                    tr("Save settings"),
                                                    QDir::currentPath(),
                                                    tr("Documents (*.xml)"));
    if( !filename.isNull() )
    {
        this->drawPanel->getCircle()->save(filename.toStdString());
    } else {
        qDebug("fileName is null");
    }

}
