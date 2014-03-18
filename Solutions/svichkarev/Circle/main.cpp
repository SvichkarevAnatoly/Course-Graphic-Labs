#include <QApplication>
#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include "field.h"
#include "circle.h"
#include "mainwindow.h"

int main(int argc, char** argv)
{
    if (argc > 1) {
        QCoreApplication app(argc, argv);
        QTextStream out(stdout);
        if (argc == 2) {
            Circle circle(0, 0, 20);

            try {
                // read file
                circle.read(argv[1]);
            }
            catch (...) {
                out << "Reading circle settings  error" << endl;
            }
            RGBColor color;
            color.R = 100;
            color.G = 250;
            color.B = 200;

            Field field(circle.getW(), circle.getH());
            circle.draw(&field, color);
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

        app.exit();
    } else {
        QApplication app(argc, argv);
        MainWindow window;
        window.show();
        return app.exec();
    }
    return 0;
}
