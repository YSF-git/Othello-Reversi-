#include <QApplication>

#include "./GameWindow.h"
#include "./create_highscore.h"


int main(int argc, char **argv) {
    QApplication app(argc, argv);

    app.setApplicationName("Othello Game");


    if (!CreateHighscore())
        return 1;

    GameWindow main_window;
    main_window.show();
    return app.exec();
}
