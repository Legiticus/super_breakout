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
    QRect getRect() const;
    QImage& getImage();

private:
    int xdir, ydir;
    QImage image;
    QRect rect;
    static const int INITIAL_X = 230;
    static const int INITIAL_Y = 355;
    static const int RIGHT_EDGE = 300;

};