#pragma once
#include <QWidget>
#include <QKeyEvent>
#include "ball.h"
#include "paddle.h"
#include "brick.h"

#define UP_DIR -1
#define DOWN_DIR 1

class Breakout : public QWidget {
    Q_OBJECT

public:
    Breakout(QWidget *parent = nullptr);
    ~Breakout();

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void startGame();
    void pauseGame();
    void stopGame();
    void victory();

private:
    void moveObjects();
    void checkCollision();
    void drawObjects(QPainter *painter);
    void finishGame(QPainter *painter, QString message);

    int timerId;
    bool gameStarted = false;
    bool paused = false;
    bool gameOver = false;
    bool gameWon = false;

    Ball *ball;
    Paddle *paddle;
    Brick *bricks[30]; // 5 rows × 6 columns
};