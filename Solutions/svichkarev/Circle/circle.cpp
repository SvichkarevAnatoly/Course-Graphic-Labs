#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <cmath>
#include <QDebug>
#include "circle.h"

Circle::Circle(int x, int y, int r, QObject *parent) :
    QObject(parent)
{
    // todo : harcode =/
    this->w = 100;
    this->h = 100;
    this->setX(x);
    this->setY(y);
    this->setR(r);
}

void Circle::setX(int x)
{

    qDebug()  << x ;
    this->centreX = x;
    emit changeX(x);
}
void Circle::setY(int y)
{

    qDebug() << y ;
    this->centreY = y;
    emit changeY(y);
}

void Circle::setR(int r)
{

    qDebug()   << r;
    this->radius = r;
    emit changeR(r);
}

int Circle::getW() const
{
    return w;
}

int Circle::getH() const
{
    return h;
}

void Circle::draw( Canvas *c, const QColor& color ){
    if( !c ){ // TODO:
        return;
    }

    // TODO: why all with this?
    double X0 = this->centreX +c->getWidth()*1.0/2;
    double Y0 = this->centreY +c->getHeight()*1.0/2;
    int r = this->radius;

    double leftY = Y0 - r > 0 ? Y0 - r : 0;
    double rightY= Y0 + r < c->getHeight() ? Y0 + r : c->getHeight() - 1;

    double sq_r = pow(r,2); // FIXME: pow

    for (int y = leftY; y <= rightY; ++y) {
        double sq = sqrt(sq_r - pow((y-Y0),2));
        double xa = ( -1 * sq  + X0 );
        double xb = (      sq  + X0 );
        if (xa < 0) xa = 0;
        if (xb >= c->getWidth()) xb = c->getWidth()-1;

        for (int x = round(xa); x <= xb; ++x) { // FIXME: double -> int
            c->drawPixel( x, y , color );
        }
    }
}

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
                       this->w = (xml.readElementText().toInt());
                       continue;
                    }
                    if ("Height" == xml.attributes().value("key").toString())
                    {
                       this->h = (xml.readElementText().toInt());
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
     delete file;
}

void Circle::save(const std::string &fileName)
{ //
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
