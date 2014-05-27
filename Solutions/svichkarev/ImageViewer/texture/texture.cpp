#include "texture.h"
#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QDebug>


Filter Texture::simpleFilter;
Bilinear Texture::bilinearFilter;
Mipmapper Texture::mipmapper;

Texture::Texture(int max_size) : filter(0), loaded (false), max_size(max_size)
{
    filter = &simpleFilter;
    this->max_size= find2(max_size);
    scaleX = scaleY = 1;
}


Texture::~Texture() {
    // RAII
    std::vector<QImage*>::iterator iter = LODs.begin();

    while (iter != LODs.end()){
        delete *iter;
        ++iter;
    }
}

int Texture::find2(int a){
    int m = 1;
    while ((a & (a + 1)) != 0)
        a = a | (a >> m);
    a = a - (a >> 1);
    return a;
}

void Texture::setScaleX(double scaleX){
    this->scaleX = scaleX;
}


void Texture::setScaleY(double scaleY){
    this->scaleY = scaleY;
}

double Texture::getScaleX() const {
    return scaleX;
}

double Texture::getScaleY() const {
    return scaleY;
}

void Texture::buildLODs(){
    if (!isLoaded()){
        return;
    }
    std::vector<QImage*>::iterator iter = LODs.begin();

    while (iter != LODs.end()){
        QImage* img = *iter;
        delete img;
        iter = LODs.erase(iter);
    }

    int size = image->width();
    LODs.push_back(image);

    for (int i = size/2; i >= 1; i/=2){
        int cur_size = i;

        const QImage* prev_lod = LODs.back();
        QImage* cur_lod = new QImage(cur_size, cur_size, QImage::Format_RGB888);

        for(int u = 0; u < cur_lod->width(); ++u)
        for(int v = 0; v < cur_lod->height(); ++v)
        {
            QColor a = prev_lod->pixel(2*u,   2*v);
            QColor b = prev_lod->pixel(2*u+1, 2*v);
            QColor c = prev_lod->pixel(2*u,   2*v+1);
            QColor d = prev_lod->pixel(2*u+1, 2*v+1);

            int red = (a.red() + b.red() + c.red() + d.red())*1.0 / 4.0;
            int green = (a.green() + b.green() + c.green() + d.green())*1.0 / 4.0;
            int blue = (a.blue() + b.blue() + c.blue() + d.blue())*1.0 / 4.0;

            cur_lod->bits()[v*cur_lod->bytesPerLine() + u * 3] = red;
            cur_lod->bits()[v*cur_lod->bytesPerLine() + u * 3+1] = green;
            cur_lod->bits()[v*cur_lod->bytesPerLine() + u * 3+2] = blue;
        }

        LODs.push_back(cur_lod);
    }
    qDebug()<<LODs.size();
}



void Texture::setFilter(const int filterType)
{
    if (filter->getType() == filterType) return;

    if (filterType == simpleFilter.getType()) {
        qDebug() << "simple!";
        filter = &simpleFilter;
    }
    else if (filterType == bilinearFilter.getType()) {
        filter = &bilinearFilter;
    } else {
        // TODO
        qDebug() << "MIP";
        filter = &mipmapper;
    }
}

void Texture::load(const std::string &image_src) {

    qDebug() << "LOAD";
    QPixmap pixmap;
    pixmap.load(QObject::tr((image_src.c_str())));

    int width = pixmap.width();
    int height = pixmap.height();
    int size = width < height ? width : height;


    size = find2(size);

    if (size > max_size) size = max_size;
    texel_size = 1.0/size;
    QImage raw_image = pixmap.toImage();

    image = new QImage(raw_image.copy(0, 0, size, size));
    qDebug() << size << max_size;

    loaded = true;
    buildLODs();
}

QColor Texture::get_color(const TexturedPoint &point) {
    if (!loaded) {
        return Qt::black; // TODO:
    }

    return filter->filter(this, point);
}
