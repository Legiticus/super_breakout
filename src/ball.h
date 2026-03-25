#pragma once
#include <QImage>
#include <QObject>

class Ball {

public:
    Ball();
    ~Ball();

    void resetState();
    void autoMove();
    void setXDir(int x);
    void setYDir(int y);
    int getXDir() const;
    int getYDir() const;

    void setPos(qreal x, qreal y);

    void setSpeed(qreal speed);
    qreal getSpeed() const;

    QRect getRect() const;
    QImage& getImage();

private:
    qreal x, y, xdir, ydir;
    QImage image;
    QRect rect;
    qreal speed = 1;
    static const int INITIAL_X = 230;
    static const int INITIAL_Y = 350;
    static const int RIGHT_EDGE = 300;

};