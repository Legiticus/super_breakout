#include "breakout.h"
#include <QPainter>
#include <QApplication>

Breakout::Breakout(QWidget *parent) : QWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
    gameOver = false;
    gameWon = false;
    paused = false;
    gameStarted = false;
    ball = new Ball();
    paddle = new Paddle();

    int k = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 6; ++j) {
            bricks[k] = new Brick(j * 40 + 30, i * 10 + 50);
            k++;
        }
    }
}   

Breakout::~Breakout() {
    delete ball;
    delete paddle;
    for (int i = 0; i < 30; ++i) {
        delete bricks[i];
    }
}

void Breakout::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    if (gameOver) {
        QFont font("Courier", 15, QFont::DemiBold);
        QFontMetrics fm(font);
        int textWidth = fm.horizontalAdvance("Game Over");
        painter.setFont(font);
        painter.translate(QPoint(width() / 2, height() / 2));
        painter.drawText(-textWidth / 2, 0, "Game Over");
    } else if (gameWon) {
        QFont font("Courier", 15, QFont::DemiBold);
        QFontMetrics fm(font);
        int textWidth = fm.horizontalAdvance("Victory");
        painter.setFont(font);
        painter.translate(QPoint(width() / 2, height() / 2));
        painter.drawText(-textWidth / 2, 0, "Victory");
    } else {
        painter.drawImage(ball->getRect(), ball->getImage());
        painter.drawImage(paddle->getRect(), paddle->getImage());
        for (int i = 0; i < 30; ++i) {
            if (!bricks[i]->isDestroyed()) {
                painter.drawImage(bricks[i]->getRect(), bricks[i]->getImage());
            }
        }
    }
}

void Breakout::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);
    moveObjects();
    checkCollision();
    repaint();
}

void Breakout::moveObjects() {
    ball->autoMove();
    paddle->move();
}

void Breakout::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        paddle->setDx(-1);
        break;
    case Qt::Key_Right:
        paddle->setDx(1);
        break;
    case Qt::Key_P:
        pauseGame();
        break;
    case Qt::Key_Space:
        startGame();
        break;
    case Qt::Key_Escape:
        qApp->exit();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void Breakout::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
        paddle->setDx(0);
        break;
    default:
        QWidget::keyReleaseEvent(event);
    }
}

void Breakout::startGame() {
    if (!gameStarted) {
        ball->resetState();
        paddle->resetState();
        for (int i = 0; i < 30; ++i) {
            bricks[i]->setDestroyed(false);
        }
        gameOver = false;
        gameWon = false;
        gameStarted = true;
        timerId = startTimer(10);
    }
}

void Breakout::pauseGame() {
    if (paused) {
        timerId = startTimer(10);
        paused = false;
    } else {
        paused = true;
        killTimer(timerId);
    }
}

void Breakout::stopGame() {
    killTimer(timerId);
    gameOver = true;
    gameStarted = false;
}

void Breakout::victory() {
    killTimer(timerId);
    gameWon = true;
    gameStarted = false;
}

void Breakout::checkCollision() {
    if (ball->getRect().bottom() > 400) {
        stopGame();
    }

    int destroyedCount = 0;
    for (int i = 0; i < 30; ++i) {
        if (bricks[i]->isDestroyed()) {
            destroyedCount++;
        }
    }

    if (destroyedCount == 30) {
        victory();
    }

    //Check if ball intersectss paddle
    if (ball->getRect().intersects(paddle->getRect())) {
        int paddleLeft = paddle->getRect().left();
        int ballLeft = ball->getRect().left();
        int first = paddleLeft + 8, second = paddleLeft + 16, third = paddleLeft + 24, fourth = paddleLeft + 32;

        if (ballLeft < first) {
            ball->setXDir(-1);
            ball->setYDir(UP_DIR);
        } else if (ballLeft < second) {
            ball->setXDir(-1);
            ball->setYDir(UP_DIR * ball->getYDir());
        } else if (ballLeft < third) {
            ball->setXDir(0);
            ball->setYDir(UP_DIR);
        } else if (ballLeft < fourth) {
            ball->setXDir(1);
            ball->setYDir(UP_DIR * ball->getYDir());
        } else {
            ball->setXDir(1);
            ball->setYDir(UP_DIR);
        }
    }

    //Check if ball has collided with any of the blocks
    for (int i = 0; i < 30; ++i) {
        if (ball->getRect().intersects(bricks[i]->getRect()) && !bricks[i]->isDestroyed()) {
            int ballLeft = ball->getRect().left();
            int ballTop = ball->getRect().top();
            QPoint right(ballLeft + ball->getRect().width(), ballTop);
            QPoint left(ballLeft - 1, ballTop);
            QPoint top(ballLeft, ballTop - 1);
            QPoint bottom(ballLeft, ballTop + ball->getRect().height());

            if (bricks[i]->getRect().contains(right)) ball->setXDir(-1);
            else if (bricks[i]->getRect().contains(left)) ball->setXDir(1);

            if (bricks[i]->getRect().contains(top)) ball->setYDir(DOWN_DIR);
            else if (bricks[i]->getRect().contains(bottom)) ball->setYDir(UP_DIR);

            bricks[i]->setDestroyed(true);
        }
    }
}   