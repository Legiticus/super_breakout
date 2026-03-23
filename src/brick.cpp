#include "brick.h"
#include <iostream>

Brick::Brick(int x, int y) {
    image.load(":/images/brick.png");

    if (image.isNull()) {
       std::cout << "Failed to load image: brick.png" << std::endl;

    }
    
    rect = image.rect();
    rect.moveTo(x, y);
    destroyed = false;
}

Brick::~Brick() {}

bool Brick::isDestroyed() const { return destroyed; }
void Brick::setDestroyed(bool d) { destroyed = d; }
QRect Brick::getRect() const { return rect; }
QImage &Brick::getImage() { return image; }   