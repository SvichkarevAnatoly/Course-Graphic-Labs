#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include <QWidget>
#include <QPoint>
#include "texture/square.h"
#include "canvas/canvas.h"

class DrawPanel : public QWidget, public Canvas
{
    Q_OBJECT
    Square square;
    Texture texture;
public:
    explicit DrawPanel( int w, int h,   QWidget *parent = 0);
    const Square& getSquare() const {
        return square;
    }
    const Texture& getTexture() const{
        return texture;
    }

    void open(const std::string& filename);
protected:
    void paintEvent(QPaintEvent *event);
public slots:
    void repaint_square();
};

#endif // DRAWPANEL_H
