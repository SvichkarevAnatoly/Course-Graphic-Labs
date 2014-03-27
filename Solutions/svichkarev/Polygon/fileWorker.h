#ifndef FILEWORKER_H
#define FILEWORKER_H

#include "circle.h"

class fileWorker{
public:
    static void saveImage( const std::string &fileName, Circle &circle, int PanelWidth, int PanelHeight, const QColor &color );
    static void readFileSettings( const std::string &fileName, Circle &circle );
    static void writeFileSettings( const std::string &fileName, Circle &circle );
};

#endif // FILEWORKER_H
