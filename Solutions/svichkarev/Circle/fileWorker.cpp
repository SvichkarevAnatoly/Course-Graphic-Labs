#include "fileWorker.h"

#include <QDebug>

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

void fileWorker::readFileSettings( const std::string &fileName, Circle &circle ){
    QFile *file = new QFile( fileName.c_str() );
    if ( !file->open(QIODevice::ReadOnly | QIODevice::Text) ){
        return;
    }

    QXmlStreamReader xml( file );
    while ( ! xml.atEnd() ){
        QXmlStreamReader::TokenType token = xml.readNext();
        if( token == QXmlStreamReader::StartDocument ){
            continue;
        }
        if( token == QXmlStreamReader::StartElement ){
            if( xml.name() == "properties" ){
               continue;
            }

            if( xml.name() == "entry" ){
                if( xml.attributes().hasAttribute("key") ){
                    if( "PosX" == xml.attributes().value("key").toString() ){
                        circle.setX( xml.readElementText().toInt() );
                        continue;
                    }

                    if( "PosY" == xml.attributes().value("key").toString() ){
                        circle.setY(xml.readElementText().toInt());
                        continue;
                    }
                    if( "R" == xml.attributes().value("key").toString() ){
                        circle.setR(xml.readElementText().toInt());
                        continue;
                    }
                }
            }
        }

        if( xml.hasError() ){
           break;
        }
    }

    file->close();
    delete file;
}

void fileWorker::writeFileSettings( const std::string &fileName, Circle &circle ){
    qDebug ( "save" );
    QFile *file = new QFile( fileName.c_str() );
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug ( "file open failed" );
        return;
    }

    QXmlStreamWriter xmlWriter( file );
    xmlWriter.setAutoFormatting( true );
    xmlWriter.setAutoFormattingIndent( 2 );

    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("properties");

    xmlWriter.writeStartElement("comment");
    xmlWriter.writeCharacters ("Circle properties");
    xmlWriter.writeEndElement();


    xmlWriter.writeStartElement("entry");
    xmlWriter.writeAttribute("key","PosX");
    xmlWriter.writeCharacters( QString::number( circle.getX() ) );
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("entry");
    xmlWriter.writeAttribute("key","PosY");
    xmlWriter.writeCharacters( QString::number( circle.getY() ) );
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("entry");
    xmlWriter.writeAttribute("key","R");
    xmlWriter.writeCharacters( QString::number( circle.getR() ) );
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file->close();
    delete file;
}

void fileWorker::saveImage( const std::string &fileName, Circle &circle, int PanelWidth, int PanelHeight, const QColor &color ){
    QImage image( PanelWidth, PanelHeight, QImage::Format_RGB888 );
    circle.draw( &image, color );

    try{
        image.save( QString( fileName.c_str() ), "png" );
    } catch(...){
        qDebug() << "error save PNG";
    }
}
