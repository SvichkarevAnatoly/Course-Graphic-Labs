#ifndef FILEWORKER_H
#define FILEWORKER_H

#include "setpolygons.h"

class fileWorker{
public:
    static void saveImage( const std::string &fileName, SetPolygons &polygons, int PanelWidth, int PanelHeight );
    static void readFileSettings( const std::string &fileName, SetPolygons &polygons, int & PanelWidth, int & PanelHeight );
    static void writeFileSettings( const std::string &fileName, SetPolygons &polygons, int PanelWidth, int PanelHeight );
};

#endif // FILEWORKER_H
