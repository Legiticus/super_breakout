#include "ball.h"
#include <iostream>

Ball::Ball() {
    xdir = 1;
    ydir = -1;
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
    rect.moveTo(230, 355);
}

void Ball::autoMove() {
    rect.translate(xdir, ydir);
    if (rect.left() == 0 || rect.right() == 300) {
        xdir = -xdir;
    }
    if (rect.top() == 0) {
        ydir = -ydir;
    }
}

void Ball::setXDir(int x) { xdir = x; }
void Ball::setYDir(int y) { ydir = y; }
int Ball::getXDir() const { return xdir; }
int Ball::getYDir() const { return ydir; }
QRect Ball::getRect() const { return rect; }
QImage &Ball::getImage() { return image; }