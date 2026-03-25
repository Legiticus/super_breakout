#include "ball.h"
#include <iostream>

Ball::Ball() {
    xdir = 1;
    ydir = -1;
    x = 0;
    y = 0;
    image.load(":/images/ball.png");

    if (image.isNull()) {
       std::cout << "Failed to load image: ball.png" << std::endl;

    }
    
    rect = image.rect();
    resetState();
}

Ball::~Ball() {
    std::cout << "Ball deleted\n";
}

void Ball::resetState() {
    speed = 1;
}

void Ball::autoMove() {
    x += xdir * speed;
    y += ydir * speed;
    rect.moveTo(x, y);

    if (rect.left() <= 0 || rect.right() >= 300) {
        xdir = -xdir;
    }
    if (rect.top() <= 0) {
        ydir = -ydir;
    }
}

void Ball::setXDir(int x) { xdir = x; }
void Ball::setYDir(int y) { ydir = y; }
int Ball::getXDir() const { return xdir; }
int Ball::getYDir() const { return ydir; }

void Ball::setPos(qreal x, qreal y) {
    this->x = x;
    this->y = y;
    rect.moveTo(x, y);
}

void Ball::setSpeed(qreal speed) {this->speed = speed; std::cout << "Speed: " << speed << std::endl;}
qreal Ball::getSpeed() const {return speed;}

QRect Ball::getRect() const { return rect; }
QImage &Ball::getImage() { return image; }