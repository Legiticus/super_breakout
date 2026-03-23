#include <QApplication>
#include "breakout.h"

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    Breakout mainWidget;
    mainWidget.resize(300, 400);
    mainWidget.setWindowTitle("Breakout");
    mainWidget.show();
    return app.exec();

}