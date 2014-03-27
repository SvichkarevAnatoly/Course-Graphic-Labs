#ifndef FILEWORKER_H
#define FILEWORKER_H

#include "polygon.h"

class fileWorker{
public:
    static void saveImage( const std::string &fileName, Polygon &polygon, int PanelWidth, int PanelHeight, const QColor &color );
    static void readFileSettings( const std::string &fileName, Polygon &polygon );
    static void writeFileSettings( const std::string &fileName, Polygon &polygon );
};

#endif // FILEWORKER_H
