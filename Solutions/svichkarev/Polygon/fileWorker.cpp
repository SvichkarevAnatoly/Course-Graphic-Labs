#include "fileWorker.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>

void fileWorker::readFileSettings( const std::string &fileName, SetPolygons &polygons, int & PanelWidth, int & PanelHeight ){
    QFile *file = new QFile( fileName.c_str() );
    if ( !file->open(QIODevice::ReadOnly | QIODevice::Text) ){
        return;
    }

    QXmlStreamReader xml( file );
    while ( !xml.atEnd() &&
            !xml.hasError() ){

        QXmlStreamReader::TokenType token = xml.readNext();

        if( token == QXmlStreamReader::StartDocument ){
            continue;
        }

        if( token == QXmlStreamReader::StartElement ){
            if( xml.name() == "properties" ){
               continue;
            }

            if( xml.name() == "Polygon" ){
                xml.readNext();

                // пока не встретим конца читаем точки
                while( !(xml.tokenType() == QXmlStreamReader::EndElement &&
                            xml.name() == "Polygon") ){

                    if( xml.tokenType() == QXmlStreamReader::StartElement ) {
                        if( xml.name() == "Point" ) {
                            QPoint curPoint;
                            // считываем координаты
                            if( xml.attributes().hasAttribute("x") ){
                                curPoint.setX( xml.attributes().value("x").toString().toInt() );
                            }

                            if( xml.attributes().hasAttribute("y") ){
                                curPoint.setY( xml.attributes().value("y").toString().toInt() );
                            }
                            polygons.addPoint( curPoint );
                        }
                    }
                    /* ...and next... */
                    xml.readNext();
                }
            }

            // считывание размеров окна
            if( xml.name() == "entry" ){
                if( xml.attributes().hasAttribute("key") ){
                    if( "PanelWidth" == xml.attributes().value("key").toString() ){
                        PanelWidth = xml.readElementText().toInt();
                        continue;
                    }

                    if( "PanelHeight" == xml.attributes().value("key").toString() ){
                        PanelHeight = xml.readElementText().toInt();
                        continue;
                    }
                }
            }
        }
    }

    xml.clear();
    file->close();
    delete file;
}

void fileWorker::writeFileSettings( const std::string &fileName, SetPolygons &polygons, int PanelWidth, int PanelHeight ){
    QFile *file = new QFile( fileName.c_str() );
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }

    QXmlStreamWriter xmlWriter( file );
    xmlWriter.setAutoFormatting( true );
    xmlWriter.setAutoFormattingIndent( 2 );

    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("properties");

    xmlWriter.writeStartElement("comment");
    xmlWriter.writeCharacters ("Polygon properties");
    xmlWriter.writeEndElement();


    xmlWriter.writeStartElement("Polygon");

    QList< QPoint > points = polygons.getListCurrentPoints();
    foreach( const QPoint point, points ){
        xmlWriter.writeStartElement("Point");
        xmlWriter.writeAttribute("x", QString::number( point.x() ) );
        xmlWriter.writeAttribute("y", QString::number( point.y() ) );
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("entry");
    xmlWriter.writeAttribute("key","PanelWidth");
    xmlWriter.writeCharacters( QString::number( PanelWidth ) );
    xmlWriter.writeEndElement();


    xmlWriter.writeStartElement("entry");
    xmlWriter.writeAttribute("key","PanelHeight");
    xmlWriter.writeCharacters( QString::number( PanelHeight ) );
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file->close();
    delete file;
}

void fileWorker::saveImage( const std::string &fileName, SetPolygons &polygons, int PanelWidth, int PanelHeight ){
    QImage image( PanelWidth, PanelHeight, QImage::Format_RGB888 );

    MQPainter painter;
    painter.refreshImageBuffer( &image );
    image.fill( Qt::white );
    polygons.draw( painter );

    try{
        image.save( QString( fileName.c_str() ), "png" );
    } catch(...){
    }
}
