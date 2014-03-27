#include "polygon.h"
#include "mainwindow.h"

#include "fileWorker.h"

#include <QApplication>
#include <QCoreApplication>
#include <QTextStream>
#include <QDebug> //TODO
#include <iostream>

int main( int argc, char** argv ){
    if( argc > 1 ){
        /*
        QCoreApplication app(argc, argv);
        QTextStream out(stdout);

        if( argc == 4 ){
            Circle circle(0, 0, 20);
            const QColor color( 100, 200, 120 );
            try{
                fileWorker::readFileSettings( argv[1], circle );
                std::string filename("output.png");
                fileWorker::saveImage( filename, circle, atoi( argv[2] ), atoi( argv[3] ), color );
            } catch(...){
                out << "Reading circle settings  error" << endl;
            }
        } else{
            out << "Error: usage: circle file.xml PanelWidth PanelHeight" << endl;
        }

        app.exit();
        */
    } else {
        QApplication app(argc, argv);
        MainWindow window;
        window.show();
        return app.exec();
    }
    return 0;
}
