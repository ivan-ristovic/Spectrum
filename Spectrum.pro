#-------------------------------------------------
#
# Project created by QtCreator 2017-03-31T14:42:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Spectrum
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/player.cpp \
    src/game.cpp \
    src/level.cpp \
    src/entity.cpp \
    src/dynamicentity.cpp \
    src/block.cpp \
    src/cube.cpp \
    src/colors.cpp \
    src/key.cpp \
    src/door.cpp \
    src/levelloader.cpp \
    src/wall.cpp \
    src/ladder.cpp \
    src/colorchanger.cpp \
    src/colorunlocker.cpp \
    src/colorchooser.cpp \
    src/gameloader.cpp \
    src/sprite.cpp \
    src/laser.cpp \
    src/spike.cpp \
    src/gravityswitcher.cpp

HEADERS  += \
    include/mainwindow.h \
    include/player.h \
    include/game.h \
    include/level.h \
    include/entity.h \
    include/dynamicentity.h \
    include/block.h \
    include/cube.h \
    include/colors.h \
    include/key.h \
    include/door.h \
    include/levelloader.h \
    include/wall.h \
    include/ladder.h \
    include/colorchanger.h \
    include/colorunlocker.h \
    include/colorchooser.h \
    include/gameloader.h \
    include/sprite.h \
    include/laser.h \
    include/spike.h \
    include/gravityswitcher.h

FORMS    += \
    ui/mainwindow.ui

RESOURCES += \
    res/levels/levels.qrc \
    res/sprites/sprites.qrc \
    res/gui/gui.qrc

DISTFILES +=

