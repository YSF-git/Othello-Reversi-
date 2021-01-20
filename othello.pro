QT += widgets
QT += multimedia
QT += sql
QT += printsupport

SOURCES = src/main.cpp \
    src/ClickButton.cpp \
    src/GameWindow.cpp \
    src/HighScoreWindow.cpp \
    src/OthelloGame.cpp \
    src/PlayerNamesWindow.cpp
TRANSLATIONS = languages/test_en.ts  languages/test_de.ts

HEADERS += \
    src/ClickButton.h \
    src/FixedAspectRatioWidget.h \
    src/GameWindow.h \
    src/HighScoreWindow.h \
    src/OthelloGame.h \
    src/PlayerNamesWindow.h \
    src/box_square.h \
    src/create_highscore.h \
    src/direction.h \
    src/highScoreWindowColumns.h \
    src/stone.h \
    src/utility.h

RESOURCES += \
    images/images.qrc \
    images/images.qrc

DISTFILES += \
    images/black.png \
    images/black_light.png \
    images/empty.png \
    images/white.png \
    images/white_light.png
