#ifndef TEXTURE_H
#define TEXTURE_H

#include "texturedpoint.h"
#include "filter/filter.h"
#include "filter/bilinear.h"
#include "filter/mipmapper.h"
#include <QObject>
#include <QImage>
#include <QColor>
#include <QPoint>

class Texture : public QObject
{
    Q_OBJECT
private:
    static Filter simpleFilter;
    static Bilinear bilinearFilter;
    static Mipmapper mipmapper;
private:
    std::vector<QImage*> LODs;
    Filter* filter;
    QImage* image;
    bool loaded;
    int max_size;
    double texel_size;

    double scaleX;
    double scaleY;
private:
    static int find2(int a);
    void buildLODs();
public slots:
    void setFilter(int filterType);
    void setScaleX(double scaleX);
    void setScaleY(double scaleY);

public:
    Texture(int max_size);
    ~Texture();

    void load(const std::string& image_src);

    QColor get_color(const TexturedPoint& point);

    double get_texel_size() const {
        return texel_size;
    }
    const QImage& get_LOD(int level) const {
        return *LODs.at(level);
    }

    double getScaleX() const;
    double getScaleY() const;

    bool isLoaded() const {
        return loaded;
    }
    int get_LODs_count() const{
        return LODs.size();
    }

    int get_size() const {
        if (!loaded)
            return -1;
        return image->width();
    }

    QColor get_color(const QPoint& point) const {
        return image->pixel(point);
    }
};

#endif // TEXTURE_H
