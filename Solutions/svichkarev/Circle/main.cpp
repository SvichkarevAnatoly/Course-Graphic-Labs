#include <QApplication>
#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include "field.h"
#include "circle.h"
#include "mainwindow.h"

int main( int argc, char** argv ){
    if( argc > 1 ){ // if there are arguments
        QCoreApplication app( argc, argv ); // TODO: why?
        QTextStream out( stdout );
        if( argc == 2 ){
            Circle circle( 0, 0, 20 );

            try{
                // read file
                circle.read( argv[ 1 ] );
            }catch(...){
                out << "Reading circle settings  error" << endl;
            }

            const QColor color( 100, 250, 200 );

            Field field(circle.getW(), circle.getH()); // TODO:
            circle.draw( &field, color ); // TODO:
            try {
                field.save("output.png");
            } catch(...) {
                // TODO :
                out << "error "  << endl;
            }
        } else {
            // Error
             out << "Error " <<  endl;

        }

        app.exit(); // TODO:
    } else {
        QApplication app(argc, argv);
        MainWindow window;
        window.show();
        return app.exec();
    }
    return 0;
}
