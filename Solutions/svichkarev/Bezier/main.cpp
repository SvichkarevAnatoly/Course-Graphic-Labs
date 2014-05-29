#include "mainwindow.h"

#include "fileWorker.h"

#include <QApplication>
#include <QCoreApplication>
#include <QTextStream>
#include <iostream>

int main( int argc, char** argv ){
    if( argc > 1 ){
        QCoreApplication app(argc, argv);
        QTextStream out(stdout);

        SetPolygons polygons;
        try{
            int PanelWidth = -1;
            int PanelHeight = -1;
            fileWorker::readFileSettings( argv[1], polygons, PanelWidth, PanelHeight );
            std::string filename( "output.png" );

            // если нет размеров полотна в командной строке, то взять из файла
            if( argc == 2 ){
                if( ( PanelWidth > 0 ) && ( PanelHeight > 0 ) ){
                    fileWorker::saveImage( filename, polygons, PanelWidth, PanelHeight );
                } else{
                    out << "Error: usage: polygons file.xml PanelWidth PanelHeight or specify in .xml" << endl;
                }
            } else{
                if( argc == 4 ){
                    fileWorker::saveImage( filename, polygons, atoi( argv[2] ), atoi( argv[3] ) );
                }
            }
        } catch(...){
            out << "Reading polygons settings  error" << endl;
        }

        app.exit();
    } else {
        QApplication app(argc, argv);
        MainWindow window;
        window.show();
        return app.exec();
    }
    return 0;
}
