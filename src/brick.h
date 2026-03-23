#pragma once
#include <QImage>
#include <QRect>

class Brick {
public:
    Brick(int x, int y);
    ~Brick();

    bool isDestroyed() const;
    void setDestroyed(bool destroyed);
    QRect getRect() const;
    QImage & getImage();

private:
    QImage image;
    QRect rect;
    bool destroyed;
};