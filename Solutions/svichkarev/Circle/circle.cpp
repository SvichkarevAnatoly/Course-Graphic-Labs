#include "circle.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>

#include <cmath>
#include <QDebug>  //TODO: убрать

Circle::Circle( int x, int y, int r){
    setX(x);
    setY(y);
    setR(r);
}

// устанавливаем новые значения вызываем сигнал изменения
void Circle::setX( int x ){
    qDebug()  << x; //TODO: убрать
    centreX = x;
    emit changeX( x );
}

void Circle::setY( int y ){
    qDebug() << y; //TODO: убрать
    centreY = y;
    emit changeY( y );
}

void Circle::setR( int r ){
    qDebug()   << r; //TODO: убрать
    radius = r;
    emit changeR( r );
}

void Circle::draw(  ){

}

// Главный метод всей лабы - отрисовка круга
void Circle::draw( DrawPanel *canvas, const QColor& color ){
    if( !canvas ){ // TODO: надо кидать исключение
        return;
    }

    // TODO: why all with this?
    // TODO: по идее это константы, их не обязательно каждый раз высчитывать
    double X0 = centreX + canvas->width() *1.0/2;
    double Y0 = centreY + canvas->height()*1.0/2;
    int r = radius;

    double leftY = Y0 - r > 0 ? Y0 - r : 0;
    double rightY= Y0 + r < canvas->height() ? Y0 + r : canvas->height() - 1;

    double sq_r = pow(r,2); // FIXME: pow

    for( int y = leftY; y <= rightY; ++y ){
        double sq = sqrt(sq_r - pow((y-Y0),2));
        double xa = ( -1 * sq  + X0 );
        double xb = (      sq  + X0 );
        if (xa < 0) xa = 0;
        if (xb >= canvas->width()) xb = canvas->width()-1;

        for (int x = round(xa); x <= xb; ++x) { // FIXME: double -> int
            canvas->drawPixel( x, y , color );
        }
    }
}

// TODO: разобраться
// метод парсинга входного файла
void Circle::read(const std::string &fileName)
{ // todo check min max
     QFile *file = new QFile(fileName.c_str());
     if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
     {
         // TODO
     }
     QXmlStreamReader xml(file);
     while (!xml.atEnd()  )
     {
         QXmlStreamReader::TokenType token = xml.readNext();
         if (token == QXmlStreamReader::StartDocument)
             continue;
         if (token == QXmlStreamReader::StartElement)
         {
             if (xml.name() == "properties")
                continue;
             if (xml.name() == "entry"){
                 if (xml.attributes().hasAttribute("key")){
                    if ("PosX" == xml.attributes().value("key").toString())
                    {
                        this->setX(xml.readElementText().toInt());
                        continue;
                    }
                    if ("PosY" == xml.attributes().value("key").toString())
                    {
                       this->setY(xml.readElementText().toInt());
                       continue;
                    }
                    if ("R" == xml.attributes().value("key").toString())
                    {
                       this->setR(xml.readElementText().toInt());
                       continue;
                    }
                    /* Only in console mode */
                    if ("Width" == xml.attributes().value("key").toString())
                    {
                        // FIXME: надо этот момент переделать
                       //this->w = (xml.readElementText().toInt());
                       continue;
                    }
                    if ("Height" == xml.attributes().value("key").toString())
                    {
                        // FIXME: надо этот момент переделать
                       //this->h = (xml.readElementText().toInt());
                       continue;
                    }
                 }
             }
         }
         if (xml.hasError()) {
             //to do error handling
            break;
         }
     }
     file->close();
     delete file; // TODO: почему удаляет
}

// TODO: класс круга сам не должен открывать файл,
// по идее он должен спрашивать у класса утилиты для сохранения и загрузки
// нужные ему параметры, а тот должен искать в файле и возвращать...

// TODO: разобраться
// метод сохранения в файл круга
void Circle::save(const std::string &fileName){
    qDebug ( "save" );
    QFile *file = new QFile(fileName.c_str());
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // TODO
        qDebug ( "file failed" );
        return;
    }
    QXmlStreamWriter xmlWriter(file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(2);

    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("properties");

    xmlWriter.writeStartElement("comment");
    xmlWriter.writeCharacters ("Circle properties");
    xmlWriter.writeEndElement();


    xmlWriter.writeStartElement("entry");
    xmlWriter.writeAttribute("key","PosX");
    xmlWriter.writeCharacters (QString::number(this->centreX));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("entry");
    xmlWriter.writeAttribute("key","PosY");
    xmlWriter.writeCharacters (QString::number(this->centreY));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("entry");
    xmlWriter.writeAttribute("key","R");
    xmlWriter.writeCharacters (QString::number(this->radius));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file->close();
    delete file;
}
