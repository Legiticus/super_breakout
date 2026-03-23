#include "paddle.h"
#include <iostream>

Paddle::Paddle() {
    dx = 0;
    image.load(":/images/paddle.png");

    if (image.isNull()) {
        std::cout << "Failed to load image: paddle.png" << std::endl;
    }
    
    rect = image.rect();
    resetState();
}

Paddle::~Paddle() {
    std::cout << "Paddle deleted\n";
}

void Paddle::resetState() {
    rect.moveTo(200, 360);
}

void Paddle::setDx(int x) { dx = x; }
void Paddle::move() {
    int x = rect.x() + dx;
    if (x > 0 && x < 260) {
        rect.moveTo(x, 360);
    }
}
QRect Paddle::getRect() const { return rect; }
QImage &Paddle::getImage() { return image; }   